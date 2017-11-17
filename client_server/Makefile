all : client server


client : client.c open62541.c open62541.h
	gcc client.c open62541.c -o client


server : server.c open62541.c open62541.h
	gcc server.c open62541.c -o server


.PHONY : clean
clean :
	-rm -f client server
