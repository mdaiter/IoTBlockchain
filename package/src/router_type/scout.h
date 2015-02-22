#ifndef SCOUT_H
#define SCOUT_H

typedef struct {
	char* name;
	char* ip_addr;
	char* host_addr;
} scout_t;


void init_scout(scout_t*, char*, char[], char[]);
int init_data(scout_t*, char*, char[]);
int send_data(scout_t*, char[], char[], char[]);

#endif
