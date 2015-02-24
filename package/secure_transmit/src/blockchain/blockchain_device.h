#ifndef BLOCKCHAIN_DEVICE_H
#define BLOCKCHAIN_DEVICE_H

typedef struct {
	char* id;
	char* value;
	int date;
} blockchain_device_t;

void blockchain_device_init(blockchain_device_t*, char*, char*, int);

#endif
