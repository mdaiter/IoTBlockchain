CC=gcc
LDFLAGS=-ljansson -lsocket -lcurl -lssl
LIBFLAGS=-fPIC -shared
OUTPUT_NAME=libsecuretransmit.so

main: merkle_tree.o md5.o wink.o merkle_tree_transmit.o lead.o scout.o blockchain.o blockchain_node.o hashcash.o blockchain_device.o
	$(CC) $(LDFLAGS) merkle_tree.o wink.o md5.o merkle_tree_transmit.o lead.o scout.o blockchain.o blockchain_node.o hashcash.o blockchain_device.o $(LIBFLAGS) -o $(OUTPUT_NAME)
merkle_tree.o: merkle-tree/merkle_tree.c
	$(CC) $(CFLAGS) -c merkle-tree/merkle_tree.c $(LIBFLAGS)
md5.o: merkle-tree/md5.c merkle-tree/md5.h
	$(CC) $(CFLAGS) -c merkle-tree/md5.c $(LIBFLAGS)
wink.o: wink_c_api/wink.c
	$(CC) $(CFLAGS) -c wink_c_api/wink.c $(LIBFLAGS)
merkle_tree_transmit.o: merkle_tree_transmit/merkle_tree_transmit.c
	$(CC) $(CFLAGS) -c merkle_tree_transmit/merkle_tree_transmit.c $(LIBFLAGS)
lead.o: router_type/lead.c
	$(CC) $(CFLAGS) -c router_type/lead.c $(LIBFLAGS)
scout.o: router_type/scout.c
	$(CC) $(CFLAGS) -c router_type/scout.c $(LIBFLAGS)
blockchain.o: blockchain/blockchain.c
	$(CC) $(CFLAGS) -c blockchain/blockchain.c $(LIBFLAGS)
blockchain_node.o: blockchain/blockchain_node.c
	$(CC) $(CFLAGS) -c blockchain/blockchain_node.c $(LIBFLAGS)
blockchain_device.o: blockchain/blockchain_device.c
	$(CC) $(CFLAGS) -c blockchain/blockchain_device.c $(LIBFLAGS)
hashcash.o: blockchain/hashcash.c
	$(CC) $(CFLAGS) -c blockchain/hashcash.c $(LIBFLAGS)
clean:
	rm *.o $(OUTPUT_NAME)
