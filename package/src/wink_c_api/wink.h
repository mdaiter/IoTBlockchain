#ifndef WINK_H
#define WINK_H

#include <curl/curl.h>

typedef struct {
	//Necessary for storing client id, secret, token, curl
	char client_id[33];
	char client_secret[33];
	//Didn't know the size of the access token...fix this in API
	char access_token[33];
	//Need access to the internet
} wink_user_t;


//To init the api
int wink_init();

//To login to the server
int wink_login(wink_user_t*, char*, char*, char*, char*);

#endif
