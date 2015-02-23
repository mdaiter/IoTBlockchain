#include "blockchain.h"
#include "hashcash.h"
#include <stdio.h>
#include <string.h>
#include "../merkle_tree_transmit/merkle_tree_transmit.h"
#include <stdlib.h>

int verify_id_owns_data_log(char* in_id, char* data_id ){
	FILE* fp;
	int has_found = 0;
	
	char* data_id_temp;
	char* in_id_temp;
	char* out_id_temp;
	char* verify_hash_temp;

	fp = fopen("buildtree.txt", "r");
	
	//Scan buildtree for transactions into the tree. 1 should mean positive return; 0, doesn't own data; -1, corrupted data somewhere
	while(!feof(fp)){
		if (fscanf(fp, "%s %s %s %s", data_id_temp, in_id_temp, out_id_temp, verify_hash_temp) != 4){
			break;
		}
		if (strcmp(data_id_temp, data_id)){
			if (strcmp(out_id_temp, in_id)){
				has_found++;
			}
			if (strcmp(in_id_temp, in_id)){
				has_found--;
			}
		}
	}
	fclose(fp);
	return has_found;
}

void shout(char* solution, char* data_id, char* sender_id){
	FILE* peeps_fp;
	
	peeps_fp = fopen("peeps.txt", "r");
	
	char* ip_peep;
	//32 for solved str length, 1 for space, length for data_id, 1 for space, length for sender_id, 1 for null_terminating character
	char* message_to_send = (char*)malloc(sizeof(char) * (32 + 3 + strlen(sender_id) + strlen(data_id)));
	
	strcat(message_to_send, solution);
	strcat(message_to_send, " ");
	strcat(message_to_send, data_id);
	strcat(message_to_send, " ");
	strcat(message_to_send, sender_id);
	strcat(message_to_send, '\0');
	
	while(!feof(peeps_fp)){
		if (fscanf(peeps_fp, "%s", ip_peep) != 1){
			break;
		}
		
		merkle_transmit_send(message_to_send, ip_peep);
	}

	fclose(peeps_fp);
	free(message_to_send);
}

void validate_transaction(char* in_id, char* data_id){
	char* solved_hash = solvehashcash(diff_problem_sample, 10);
	int did_verify = verify_id_owns_data(in_id, data_id);

	if (did_verify){
		//Shout out to all the peeps I HAZ STR
		shout(solved_hash, data_id, in_id);
	}
}
