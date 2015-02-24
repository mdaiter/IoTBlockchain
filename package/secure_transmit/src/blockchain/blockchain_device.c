#include "blockchain_device.h"
#include <stdio.h>
#include <stdlib.h>

void blockchain_device_init(blockchain_device_t* blockchain_device, char* id, char* value, int date){
	blockchain_device = (blockchain_device_t*)malloc(sizeof(blockchain_device_t));
	blockchain_device->id = id;
	blockchain_device->value = value;
	blockchain_device->date = date;
}
