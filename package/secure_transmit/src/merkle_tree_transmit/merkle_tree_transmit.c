#include "merkle_tree_transmit.h"
#include <unistd.h>
#include <stdlib.h>
#include <libsocket/libinetsocket.h>
#include "../merkle_tree/merkle_tree.h"
#include "../merkle_tree/md5.h"
#include <string.h>

#define TREE_HEIGHT 4
#define BLOCK_SIZE 16
#define DATA_BLOCKS 4
#define DATA_SIZE 128

int merkle_transmit_send(char* transmit_data, char* transmit_receiver){
	merkle_tree mt = {0, TREE_HEIGHT, MD5_DIGEST_LENGTH, BLOCK_SIZE, DATA_BLOCKS, MD5One, NULL};
	
	char* data[DATA_BLOCKS];
	int i;
	for (i = 0; i < DATA_BLOCKS; i++){
		data[i] = (char*)malloc(sizeof(char) * BLOCK_SIZE);
		memcpy(data[i], transmit_data, BLOCK_SIZE);
	}

	build_tree(&mt, data);
	int ret, sfd;
	ret = sfd = create_inet_stream_socket(transmit_receiver, "55000", LIBSOCKET_IPv6, 0);
	if (ret < 0){
		perror(0);
		exit(1);
	}
	
	ret = write(sfd, transmit_data, strlen(transmit_data));
	ret = write(sfd, mt.nodes[0].hash, strlen(mt.nodes[0].hash));
	//Add in stuff to wait for responses, see if we need to compare more merkle nodes down the stack. For now, just leave it out

	//Free merkle tree
	freeMerkleTree(&mt);
}

char* merkle_transmit_receive(){
	merkle_tree mt = {0, TREE_HEIGHT, MD5_DIGEST_LENGTH, BLOCK_SIZE, DATA_BLOCKS, MD5One, NULL};

	int cfd, sfd, ret;
	char* buf = calloc(DATA_SIZE, 1);
	ret = sfd = create_inet_server_socket("::","55000",LIBSOCKET_TCP,LIBSOCKET_IPv6,0);
	if ( ret < 0 )
	{
		perror(0);
		exit(1);
	}
	ret = cfd = accept_inet_stream_socket(sfd,0,0,0,0,0,0);	
	
	if ( ret < 0 )
	{
		perror(0);
		exit(1);
	}
	ret = read(cfd,buf,DATA_SIZE - 1);
	
	char* data[DATA_BLOCKS];
	int i;
	for (i = 0; i < DATA_BLOCKS; i++){
		data[i] = (char*)malloc(sizeof(char) * BLOCK_SIZE);
		memcpy(data[i],buf, BLOCK_SIZE);
	}
	free(buf);
	build_tree(&mt, data);
	
	//33 for the MD5 hash sum
	char* merkle_buf = calloc(33, 1);
	
	ret = sfd = create_inet_server_socket("::","55000",LIBSOCKET_TCP,LIBSOCKET_IPv6,0);
	if ( ret < 0 )
	{
		perror(0);
		exit(1);
	}
	ret = cfd = accept_inet_stream_socket(sfd,0,0,0,0,0,0);	
	
	if ( ret < 0 )
	{
		perror(0);
		exit(1);
	}
	ret = read(cfd,merkle_buf,DATA_SIZE - 1);

	//If top node isn't right, then transmit more data
	if (!strcmp(merkle_buf, mt.nodes[0].hash)){
		//Too lazy to implement this now. Just return NULL to symbolize that our system failed
		return NULL;
	}
	free(merkle_buf);
	freeMerkleTree(&mt);
	return buf;
	
}
