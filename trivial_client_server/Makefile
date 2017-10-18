all : client server


client : trivial_client.c open62541.c open62541.h
	gcc trivial_client.c open62541.c -o client


server : trivial_server.c open62541.c open62541.h
	gcc trivial_server.c open62541.c -o server


.PHONY : clean
clean :
	-rm -f client server
