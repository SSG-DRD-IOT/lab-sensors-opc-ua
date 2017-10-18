# OPC-UA Lab

This lab will guide you through the implementation of a simple OPC UA
application to illustrate client-server communications. Both ends will run
locally:
* Server: upon request reads and returns the date and time from the local clock
* Client: reads a timestamp from the server and prints it


## Dependencies

We are going to use an open source OPC UA stack: [open62541](https://github.com/open62541/open62541)

open62541 can be compiled to generate a single header and source code file, than can
then be integrated in your project. This is enabled by the option:

```shell
UA_ENABLE_AMALGAMATION
```

Follow the next steps to generate the open62541 header and code:
```shell
mkdir -p ${HOME}/intel/workshop
cd ${HOME}/intel/workshop
git clone https://github.com/open62541/open62541.git
cd open62541
mkdir build
cd build
cmake .. -DUA_ENABLE_AMALGAMATION:BOOL=ON
make
```

You should be able to see the open62541.c and open62541.h files now. Copy both to your working directory in order to include and link them.


## Labs

* [A trivial OPC-UA client-server application](./trivial_client_server/README.md)
