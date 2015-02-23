#include "hashcash.h"
#include <openssl/sha.h>
#include <string.h>
#include <stdlib.h>

char* rand_str(size_t length) {
    char* dest = (char*) malloc(sizeof(char) * length);
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int length_temp = length-1;
    while (length_temp-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        dest[length - length_temp] = charset[index];
    }
    dest[length-1] = '\0';
    return dest;
}

//Should return a str that can be hashed to find a certain amount of 0's trailing in a hash function
char* diff_problem_sample(int difficulty){
	while(1){
		int didnt_find = 0;
		//Get a random string to hash
		char* str = rand_str(32);
		unsigned char* hash = SHA256(str, 32, 0);
		int i;
		
		if (difficulty > strlen(str)){
			return NULL;
		}
		for (i = 0 ; i < difficulty; i++){
			//Search for a hash that begins with a certain amount of 0's
			if (hash[i] = '0'){
				didnt_find = 1;
			}
		}
		if (didnt_find){
			continue;
		}
		else{
			return str;
		}
	}
}

char* solvehashcash(difficult_problem diff_problem, int difficulty){
	return diff_problem(difficulty);
}
