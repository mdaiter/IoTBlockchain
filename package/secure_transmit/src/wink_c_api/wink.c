#include "wink.h"
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>
#include <stdlib.h>

typedef struct url_s {
    size_t size;
    char* data;
} url_t;

size_t write_data(void *ptr, size_t size, size_t nmemb, url_t *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size += (size * nmemb);

#ifdef DEBUG
    fprintf(stderr, "data at %p size=%ld nmemb=%ld\n", ptr, size, nmemb);
#endif
    tmp = realloc(data->data, data->size + 1); /* +1 for '\0' */

    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}


int wink_init(){
	int curl_err = curl_global_init(CURL_GLOBAL_ALL);
	if (curl_err){
		//Break
		return -1;
	}
	return 0;
}



int wink_login(wink_user_t* wink_user, char client_id[], char client_secret[], char username[], char password[]){
	
	//Make the json struct
	json_t* root = json_object();
	json_object_set_new(root, "client_id", json_string(client_id));
	json_object_set_new(root, "client_secret", json_string(client_secret));
	json_object_set_new(root, "username", json_string(username));
	json_object_set_new(root, "password", json_string(password));
	json_object_set_new(root, "grant_type", json_string("password"));
	

	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, "https://winkapi.quirky.com/oauth2/token");

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");

	url_t url;
	url.size = 0;
	url.data = (char*)malloc(4096);
	url.data[0] = '\0';

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_dumps(root,0));
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &url);
	
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	json_decref(root);
	printf("%s\n", url.data);

	//Parse data, return into string
	json_t* returned_data = json_loads(url.data, 0, NULL);
	json_t* data = json_object_get(returned_data, "data");
	json_t* access_token = json_object_get(data, "access_token");
	if (!json_is_string(access_token)){
		json_decref(returned_data);
        	return 1;
	}
	
	const char* access_token_str = json_string_value(access_token);
	
	strcpy(wink_user->access_token, access_token_str);
	strcpy(wink_user->client_id, client_id);
	strcpy(wink_user->client_secret, client_secret);

	return 0;
}

int wink_update(wink_user_t* wink_user, char device_type[], char device_id[]){

	//Make the header. Just assume the header is 80 chars long
	char url_base[80] = "https://winkapi.quirky.com/";
	strcat(url_base, device_type);
	strcat(url_base, "/");
	strcat(url_base, device_id);

	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url_base);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");
	
	char authorization_header_str[51] = "Authorization: Bearer ";	
	strcat(authorization_header_str, wink_user->access_token);
	
	headers = curl_slist_append(headers, authorization_header_str);
	
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_PUT, 1);

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	
	return 0;
}

int wink_cleanup(wink_user_t* wink_user){
	free(wink_user);
	curl_global_cleanup();
}
/*
int main(){
	wink_user_t* wink_user;
	wink_user = (wink_user_t*) malloc(sizeof(wink_user));
	wink_init();
	wink_login(wink_user, "2ec4f93efd4390a33f6b8dcb12875377", "d7d606469be78ac2a3fce4e5419ab4f1", "mdaiter8121@gmail.com", "matthew8");
	wink_update(wink_user, "air_conditioner", "sadffaglieuf291089");
	
}*/
