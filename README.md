# OPC-UA Lab

This lab will guide you through the implementation of a simple OPC UA
application to illustrate client-server communications. Both ends will run
locally:
* Server: upon request reads and returns the date and time from the local clock
* Client: reads a timestamp from the server and prints it

## What is OPC-UA
OPC is the interoperability standard for the secure and reliable exchange of data in the industrial automation space and in other industries. It is platform independent and ensures the seamless flow of information among devices from multiple vendors. The OPC Foundation is responsible for the development and maintenance of this standard.

The OPC standard is a series of specifications developed by industry vendors, end-users and software developers. These specifications define the interface between Clients and Servers, as well as Servers and Servers, including access to real-time data, monitoring of alarms and events, access to historical data and other applications.

When the standard was first released in 1996, its purpose was to abstract PLC specific protocols (such as Modbus, Profibus, etc.) into a standardized interface allowing HMI/SCADA systems to interface with a “middle-man” who would convert generic-OPC read/write requests into device-specific requests and vice-versa. As a result, an entire cottage industry of products emerged allowing end-users to implement systems using best-of-breed products all seamlessly interacting via OPC.

Initially, the OPC standard was restricted to the Windows operating system. As such, the acronym OPC was borne from OLE (object linking and embedding) for Process Control. These specifications, which are now known as OPC Classic, have enjoyed widespread adoption across multiple industries, including manufacturing, building automation, oil and gas, renewable energy and utilities, among others.

With the introduction of service-oriented architectures in manufacturing systems came new challenges in security and data modeling. The OPC Foundation developed the OPC UA specifications to address these needs and at the same time provided a feature-rich technology open-platform architecture that was future-proof, scalable and extensible.
Today the acronym OPC stands for Open Platform Communications.

These are just some of the reasons why so many members and other technology organizations (collaborations) are turning to OPC UA for their interoperability platform

See [What is OPC?](https://opcfoundation.org/about/what-is-opc/)
## Dependencies

We are going to use an open source OPC UA stack: [open62541](https://github.com/open62541/open62541)

open62541 can be compiled to generate a single header and source code file, than can
then be integrated in your project. This is enabled by the option in the subsequent steps:

```shell
UA_ENABLE_AMALGAMATION
```
## SET ENV Variables
LAB_DIR is a shell environmental variable that should be set to the directory that you are creating your labs in. For example, $HOME/labs.

```bash
export LAB_DIR=$HOME/labs
```

## Download and Compile open62541

Follow the next steps to generate the open62541 header and code:
```bash
mkdir -p ${LAB_DIR}
cd ${LAB_DIR}
git clone https://github.com/open62541/open62541.git
cd open62541
mkdir build
cd build
sudo apt install cmake
cmake .. -DUA_ENABLE_AMALGAMATION:BOOL=ON
make
```

## Create a directory for this lab and copy open62541.c to it

You should be able to see the open62541.c and open62541.h files now. Copy both to your working directory in order to include and link them.


```bash
cd ${LAB_DIR}
mkdir opcua-lab
cd opcua-lab
cp ${LAB_DIR}/open62541/build/open62541.c ${LAB_DIR}/opcua-lab/
```

## Lab

* [An OPC-UA client-server application](./client_server/README.md)
