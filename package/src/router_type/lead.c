#include "lead.h"
#include <stdio.h>
#include "../merkle_tree_transmit/merkle_tree_transmit.h"
#include <jansson.h>

void add_host(char* ip){
	//We'll store the list of approved hosts in a text file. I know it's kind of shitty, but don't really have time to store it in a more secure manner
	FILE* f = fopen("host.txt", "w");
	if (f == NULL){
		printf("Error opening file\n");
		exit(1);
	}
	fprintf(f, "%s\n", ip);
	fclose(f);
}

void listen(){
	char* data = merkle_transmit_receive();
	//Check if first time. If so, shout out to rest of routers. If not, then hashcash
	json_t* root = json_loads(data, 0, NULL);
	json_t* is_first = json_object_get(root, "first_time");
	if (is_first == json_true()){
		shout_out_new_send(data);
	}
	else{
		shout_out_verify_send(data);
	}
}

//Shout out to all other peers that we've received something new. Others start to hashcash. SEND THIS IN JSON
void shout_out_new_send(char* data){

	char buff[13];
	FILE* f = fopen("host.txt", "r");
	if (f == NULL){
		printf("Error opening file\n");
		exit(1);
	}
	while( buff != NULL ){
		fscanf(f, "%s", buff);
		merkle_transmit_send(data, buff);
	}
	
}

//Shout out to verify the transaction would be complete
void shout_out_verify_send(char* data){
	
}
