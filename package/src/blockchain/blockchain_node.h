#ifndef BLOCKCHAIN_NODE_H
#define BLOCKCHAIN_NODE_H
#include "blockchain_device.h"

typedef struct {
	char* hash;
	blockchain_device_t* in;
	blockchain_device_t* out;
} blockchain_node_t;

void blockchain_node_init(blockchain_node_t*, blockchain_device_t*, blockchain_device_t*);
void blockchain_node_new_conn(blockchain_node_t*, blockchain_device_t*);
void store_blockchain_node(blockchain_node_t*);
char* blockchain_node_pretty_print(blockchain_node_t*);

#endif
