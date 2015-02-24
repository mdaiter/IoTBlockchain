#include "blockchain_node.h"
#include <stdlib.h>
#include <jansson.h>
#include <string.h>
#include "../merkle_tree/md5.h"

void blockchain_node_init(blockchain_node_t* blockchain_node, blockchain_device_t* in, blockchain_device_t* out){
	blockchain_node = (blockchain_node_t*) malloc(sizeof(blockchain_node_t));
	//Need to have an in block. Assume already initialized
	blockchain_node->in = in;
	if (out != NULL){
		blockchain_node->out = out;
	}
	char* digest;
	MD5One(
						blockchain_node_pretty_print(blockchain_node),
						strlen(blockchain_node_pretty_print(blockchain_node)),
						digest
						);
	blockchain_node->hash = digest;
	
}

void blockchain_node_new_conn(blockchain_node_t* blockchain_node, blockchain_device_t* out){
	blockchain_node->out = out;
	char* digest;
	MD5One(
						blockchain_node_pretty_print(blockchain_node),
						strlen(blockchain_node_pretty_print(blockchain_node)),
						digest
						);
	blockchain_node->hash = digest;
	store_blockchain_node(blockchain_node);
}

void store_blockchain_node(blockchain_node_t* blockchain_node){
	FILE *fp;
	fp = fopen("blockchain.txt", "w");
	fprintf(fp, blockchain_node_pretty_print(blockchain_node));
	fclose(fp);
}

char* blockchain_node_pretty_print(blockchain_node_t* blockchain_node){
	json_t* root = json_object();
	json_t* out = json_object();
	json_t* in = json_object();
	
	json_object_set_new(in, "id", json_string(blockchain_node->in->id));
	json_object_set_new(in, "value", json_string(blockchain_node->in->value));
	json_object_set_new(in, "date", json_integer(blockchain_node->in->date));
	
	
	//You *could* have this be the last node in the block
	if (blockchain_node->out != NULL){
		json_object_set_new(out, "id", json_string(blockchain_node->out->id));
		json_object_set_new(out, "value", json_string(blockchain_node->out->value));
		json_object_set_new(out, "date", json_integer(blockchain_node->out->date));	
	}
	json_object_set_new(root, "in", in);
	json_object_set_new(root, "out", out);
	
	char* return_val = json_dumps(root, 0);
	json_decref(root);
	json_decref(in);
	json_decref(out);
	
	return return_val;
}
