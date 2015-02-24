#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

/*
	Steps in validating transactions:
		1. Hashcash
		2. Lookup whether person owns piece of data or not
		3. If they do, then shout out to local router '1' for valid in JSON
		4. Else, shout out '0' for invalid to local router

	These are things that should be run by scouts, NOT NOT NOT NOT leads
*/
void validate_transaction();

#endif
