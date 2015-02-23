#include "scout.h"
#include <stdlib.h>
#include <jansson.h>
#include "../merkle_tree_transmit/merkle_tree_transmit.h"

void init_scout(scout_t* scout, char* name, char ip_addr[], char host_addr[]){
	scout = (scout_t*)malloc(sizeof(scout_t));
	scout->name = name;
	scout->ip_addr = ip_addr;
	scout->host_addr = host_addr;
}

int init_data(scout_t* scout, char* data, char data_id[]){
	//All a scout should have to do is fire off this data to the host and see what the reply is. Should block.
	//Send me data in terms of raw data and data_id. I'll take care of JSON
	json_t* root = json_object();
	json_object_set_new(root, "first_time", json_true());
	json_object_set_new(root, "data", json_string(data));
	json_object_set_new(root, "data_id", json_string(data_id));

	
	
	int err = merkle_tree_send(json_dumps(root, 0), scout->host_addr);
	if (err){
		return -1;
	}
	return 0;
}

int send_data(scout_t* scout, char data[], char data_id[], char receiver_id[]){
	json_t* root = json_object();
	json_object_set_new(root, "first_time", json_false());
	json_object_set_new(root, "data", json_string(data));
	json_object_set_new(root, "data_id", json_string(data_id));

	
	
	int err = merkle_tree_send(json_dumps(root, 0), scout->host_addr);
	if (err){
		return -1;
	}
	return 0;

}

int main(){
	
}
