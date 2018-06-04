CFLAGS = -Wall -I./open62541/src_generated -I./open62541/include -I./open62541/plugins

LDLIBS = -L./open62541 -lopen62541
LDFLAGS = -static

PROGS  = opc-ua-multiple-client opc-ua-multiple-server

all: $(PROGS)

opc-ua-multiple-client: opc-ua-multiple-client.o

opc-ua-multiple-server: opc-ua-multiple-server.o

clean:
	$(RM) *~ $(addsuffix .o,$(PROGS)) $(PROGS)
