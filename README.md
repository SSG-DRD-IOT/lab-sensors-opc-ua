# OPC-UA Lab

**Please Note: This lab can be accomplished either through the Arduino Create web environment or by downloading open62541, an open source OPC-UA libary and compiling it and your application locally on the Up2 board. If you use the Arduino Create environment then it is not necessary to download and install the open62541 library on the Up2 board. You can skip to the next step via the link at the bottom of this document.**

This lab will guide you through the implementation of a simple OPC UA application to illustrate client-server communications. Both ends will run locally:
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

# A OPC-UA client-server application

**Open Platform Communications - Unified Architecture**


This lab will guide you through the implementation of a OPC UA application to illustrate client-server communications. Both ends will run locally:
* Server: contains information about certain robots at factories that perform a certain task
* Client: queries the server for robots to see if there is a robot available for certain task

In OPC UA, servers may provide information as object nodes and variable nodes.  Object nodes can contain other object and variables nodes known as children. Variable nodes can contain other variable nodes.

We are going to implement a server and then a client gathering the built-in information for robots in a factory. This will just scratch the surface of OPC-UA communications.

Server and client implementation are split in a set of small steps to illustrate every concept independently. The complete files are also provided for reference as [client.c](./client.c) and [server.c](./server.c). The example is an extension of the tutorials and source from [open62541](https://github.com/open62541/open62541) [Tutorials](https://open62541.org/doc/0.2/tutorials.html) and distributed under the same terms: Public Domain (Creative Commons CC0).

A working [Makefile](./Makefile) is also provided.


# Server


## Interruptable process

Let's start with a minimal OPC-UA process that we can interrupt with Ctrl-C. The code would be:

```c
#include <signal.h>
/* Include the OPC-UA open62541 header file */
#include "open62541.h"

UA_Boolean running = true;

static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

int main (void) {

    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    // Our OPC UA server code will replace the loop below
    while (running) {
    }

    return 0;

}
```
When you deploy this code, you can see, when our process receives SIGINT or SIGTERM, the handler is run, a message is printed by UA_LOG_INFO, and the process exits.


## Minimal skeleton

Let's implement the actual server.

Now we will replace the loop:
```c
// Our OPC UA server code will replace the loop below
while (running) {
}
```
by the actual server code.

The first step is setting up the configuration for the server, and then creating it. The server is going to use the binary protocol over TCP, and listen on port 4840.

```c
  UA_ServerConfig config = UA_ServerConfig_standard;
  UA_ServerNetworkLayer nl = UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, 4840);
  config.networkLayers = &nl;
  config.networkLayersSize = 1;
  UA_Server *server = UA_Server_new(config);
```
At this point, the server is created but it is not yet running. This is achieved by:
```c
  UA_Server_run(server, &running);
```
The above code will stop the server whenever running becomes false. As we have seen above, the signal handler will update running.

Finally, we need to clean-up the resources:
```c
UA_Server_delete(server);
```

The full example should look like:
```c
#include <signal.h>
/* Include the OPC-UA open62541 header file */
#include "open62541.h"

UA_Boolean running = true;

static void stopHandler(int sig) {

  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");

  running = false;

  return;
};

int main (void) {
  signal(SIGINT, stopHandler);
  signal(SIGTERM, stopHandler);

  UA_ServerConfig config = UA_ServerConfig_standard;
  UA_ServerNetworkLayer nl = UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, 4840);
  config.networkLayers = &nl;
  config.networkLayersSize = 1;
  UA_Server *server = UA_Server_new(config);

  UA_Server_run(server, &running);

  UA_Server_delete(server);

  return 0;
  };
```

## Adding Factory Robots

We now have a simple OPC-UA factory server running.  Let's add some robots to our server as Object Nodes. Let's do this using object orientation so if there are other machines or stuff that we want to add to this factory server later it will be easier.

First lets add an a function for a Generic Object Node called objectType

```c

UA_NodeId robotTypeId0 = {1, UA_NODEIDTYPE_NUMERIC, {1001}};

static void defineObjectTypes(UA_Server *server) {

  /* Define the object type for "Object" */

  UA_NodeId objectTypeId;

  /* Set the Attributes for the Object */

  UA_ObjectTypeAttributes objectAttributes;

  UA_ObjectTypeAttributes_init(&objectAttributes);
  objectAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "ObjectType");

  UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
			      UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
			      UA_QUALIFIEDNAME(1, "ObjectType"), objectAttributes,
			      NULL, &objectTypeId);
```
Now lets add some Object Nodes to the Object Node for various different objects in our factory.

```c
/* Define the object type for "Robot 0" */

UA_ObjectTypeAttributes robotAttribute;

UA_ObjectTypeAttributes_init(&robotAttribute);
robotAttribute.displayName = UA_LOCALIZEDTEXT("en_US", "RobotType");

UA_Server_addObjectTypeNode(server, robotTypeId0,
                            objectTypeId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                            UA_QUALIFIEDNAME(1, "RobotType"),
                            robotAttribute,
                            NULL, NULL);


```
Let's add 2 Variable Nodes to our first Robot Object. One Variable will be the status (boolean) of the robot.
The second Variable Node will represent some value associated with the robot, i.e. location or workload.

```c
/* Define a variable type for "Robot 0" */

UA_VariableAttributes statusAttribute;

UA_VariableAttributes_init(&statusAttribute);
statusAttribute.displayName = UA_LOCALIZEDTEXT("en_US", "Status");
statusAttribute.valueRank = -1;

UA_NodeId statusId;

UA_Server_addVariableNode(server, UA_NODEID_NULL, robotTypeId0,
                          UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                          UA_QUALIFIEDNAME(1, "Status"),
                          UA_NODEID_NULL, statusAttribute, NULL, &statusId);

/* Make the status variable mandatory */

UA_Server_addReference(server, statusId,
                       UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                       UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY),
                       true);

/* Define another variable type for "Robot 0" */

UA_VariableAttributes workloadAttribute;

UA_VariableAttributes_init(&workloadAttribute);
workloadAttribute.displayName = UA_LOCALIZEDTEXT("en_US", "Workload");
workloadAttribute.valueRank = -1;

UA_NodeId workloadId;

UA_Server_addVariableNode(server, UA_NODEID_NULL,  robotTypeId0,
                          UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                          UA_QUALIFIEDNAME(1, "Workload"),
                          UA_NODEID_NULL, workloadAttribute,
                          NULL, &workloadId);

/* Make the workload variable mandatory */

UA_Server_addReference(server, workloadId,    
                       UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
                       UA_EXPANDEDNODEID_NUMERIC(0,UA_NS0ID_MODELLINGRULE_MANDATORY),
                       true);

}
```
Now lets add a function to build the derived robot object node.

```c
static void addRobotObject(UA_Server *server, char *name) {

  UA_ObjectAttributes objectAttribute;

  UA_ObjectAttributes_init(&objectAttribute);
  objectAttribute.displayName = UA_LOCALIZEDTEXT("en_US", name);

  UA_Server_addObjectNode(server, UA_NODEID_NULL,
			  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
			  UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
			  UA_QUALIFIEDNAME(1, name),
			  robotTypeId0, /* this refers to the object type identifier */
			  objectAttribute, NULL, NULL);

    return;
};
```

In the main function lets create some robots.

```c

int main (void) {

  signal(SIGINT, stopHandler);
  signal(SIGTERM, stopHandler);

  UA_ServerConfig config = UA_ServerConfig_standard;
  UA_ServerNetworkLayer nl = UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, 4840);
  config.networkLayers = &nl;
  config.networkLayersSize = 1;
  UA_Server *server = UA_Server_new(config);

  defineObjectTypes(server);

  addRobotObject(server, "robot 0");
  addRobotObject(server, "robot 1");
  addRobotObject(server, "robot 2");
  addRobotObject(server, "robot 3");
  addRobotObject(server, "robot 4");
  addRobotObject(server, "robot 5");

  UA_Server_run(server, &running);

  UA_Server_delete(server);

  return 0;
}

```

The final code should look like this
```c
#include <signal.h>
/* Include the OPC-UA open62541 header file */
#include "open62541.h"

UA_NodeId robotTypeId0 = {1, UA_NODEIDTYPE_NUMERIC, {1001}};

static void defineObjectTypes(UA_Server *server) {

  /* Define the object type for "Object" */

  UA_NodeId objectTypeId;

  /* Set the Attributes for the Object */

  UA_ObjectTypeAttributes objectAttributes;

  UA_ObjectTypeAttributes_init(&objectAttributes);
  objectAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "ObjectType");

  UA_Server_addObjectTypeNode(server, UA_NODEID_NULL,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
			      UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
			      UA_QUALIFIEDNAME(1, "ObjectType"), objectAttributes,
			      NULL, &objectTypeId);


  /* Define the object type for "Robot 0" */

  UA_ObjectTypeAttributes robotAttribute;

  UA_ObjectTypeAttributes_init(&robotAttribute);
  robotAttribute.displayName = UA_LOCALIZEDTEXT("en_US", "RobotType");

  UA_Server_addObjectTypeNode(server, robotTypeId0,
                              objectTypeId,
			      UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
			      UA_QUALIFIEDNAME(1, "RobotType"),
			      robotAttribute,
			      NULL, NULL);

  /* Define a variable type for "Robot 0" */

  UA_VariableAttributes statusAttribute;

  UA_VariableAttributes_init(&statusAttribute);
  statusAttribute.displayName = UA_LOCALIZEDTEXT("en_US", "Status");
  statusAttribute.valueRank = -1;

  UA_NodeId statusId;

  UA_Server_addVariableNode(server, UA_NODEID_NULL, robotTypeId0,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
			    UA_QUALIFIEDNAME(1, "Status"),
			    UA_NODEID_NULL, statusAttribute, NULL, &statusId);

  /* Make the status variable mandatory */

  UA_Server_addReference(server, statusId,
                         UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
			 UA_EXPANDEDNODEID_NUMERIC(0, UA_NS0ID_MODELLINGRULE_MANDATORY),
			 true);

  /* Define another variable type for "Robot 0" */

  UA_VariableAttributes workloadAttribute;

  UA_VariableAttributes_init(&workloadAttribute);
  workloadAttribute.displayName = UA_LOCALIZEDTEXT("en_US", "Workload");
  workloadAttribute.valueRank = -1;

  UA_NodeId workloadId;

  UA_Server_addVariableNode(server, UA_NODEID_NULL, robotTypeId0,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
			    UA_QUALIFIEDNAME(1, "Workload"),
			    UA_NODEID_NULL, workloadAttribute,
			    NULL, &workloadId);

  /* Make the workload variable mandatory */

  UA_Server_addReference(server, workloadId,    
                         UA_NODEID_NUMERIC(0, UA_NS0ID_HASMODELLINGRULE),
			 UA_EXPANDEDNODEID_NUMERIC(0,UA_NS0ID_MODELLINGRULE_MANDATORY),
			 true);
  return;
};

static void addRobotObject(UA_Server *server, char *name) {

  UA_ObjectAttributes objectAttribute;

  UA_ObjectAttributes_init(&objectAttribute);
  objectAttribute.displayName = UA_LOCALIZEDTEXT("en_US", name);

  UA_Server_addObjectNode(server, UA_NODEID_NULL,
			  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
			  UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
			  UA_QUALIFIEDNAME(1, name),
			  robotTypeId0, /* this refers to the object type identifier */
			  objectAttribute, NULL, NULL);

    return;
};

UA_Boolean running = true;

static void stopHandler(int sig) {

  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");

  running = false;

  return;
};

int main (void) {

  signal(SIGINT, stopHandler);
  signal(SIGTERM, stopHandler);

  UA_ServerConfig config = UA_ServerConfig_standard;
  UA_ServerNetworkLayer nl = UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, 4840);
  config.networkLayers = &nl;
  config.networkLayersSize = 1;
  UA_Server *server = UA_Server_new(config);

  defineObjectTypes(server);

  addRobotObject(server, "robot 0");
  addRobotObject(server, "robot 1");
  addRobotObject(server, "robot 2");
  addRobotObject(server, "robot 3");
  addRobotObject(server, "robot 4");
  addRobotObject(server, "robot 5");

  UA_Server_run(server, &running);

  UA_Server_delete(server);

  return 0;
};


```
Now that we have a server running with some information in some nodes.  Let's build a client to query the server.

## Client to Find OPC-UA Endpoints

Now let's implement the client side. A minimal client to see if there are any endpoints to query would look like this:
```c
#include <stdio.h>
/* Include the OPC-UA open62541 header file */
#include "open62541.h"

int main(void) {

    UA_Client *client = UA_Client_new(UA_ClientConfig_standard);

    /* List the endpoints that are found */

    UA_EndpointDescription* endpointArray = NULL;

    size_t endpointArraySize = 0;

    UA_StatusCode retval = UA_Client_getEndpoints(client,
						  "opc.tcp://localhost:4840",
						  &endpointArraySize,
						  &endpointArray);

    /* If the connection fails delete the client and return */
    if(retval != UA_STATUSCODE_GOOD) {

        UA_Array_delete(endpointArray,
			endpointArraySize,
			&UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);

	UA_Client_delete(client);

	return (int)retval;

    };

    /* Print out the endpoints found in the connection */

    printf("%i endpoints found\n", (int)endpointArraySize);

    for(size_t i=0;i<endpointArraySize;i++){

      printf("URL of endpoint %i is %.*s\n", (int)i,
               (int)endpointArray[i].endpointUrl.length,
               endpointArray[i].endpointUrl.data);
    };

    /* Delete the endpoints after they have been discovered */

    UA_Array_delete(endpointArray,
		    endpointArraySize,
		    &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);


    /* Disconnects the client internally */

    UA_Client_delete(client);

    return UA_STATUSCODE_GOOD;
}
```

The first block creates a client with the same configuration as the server, and then tries to connect to it. Then it checks for the endpoints, and if an error occurs, it exits.

We will include our client code immediately after the connection is established.

A second block of code that will take care of freeing up the resources and returning the error code is also introduced.

This  example can already be compiled by running:
```shell
# Alternatively, you can use the Makefile to handle compilation.
$ gcc client.c open62541.c -o client
```


## A client browsing nodes

Information in OPC-UA is modeled as a hierarchy of nodes. Let's write some code to browse the nodes on the server we just wrote.

```c
/* Connect to the local server */

retval = UA_Client_connect(client, "opc.tcp://localhost:4840");

/* If the connection fails delete the client and return */

if(retval != UA_STATUSCODE_GOOD) {

    UA_Client_delete(client);

    return (int)retval;
};

/* Browse for some objects */

printf("Browsing nodes in objects folder:\n");

UA_BrowseRequest browseRequest;
UA_BrowseRequest_init(&browseRequest);

browseRequest.requestedMaxReferencesPerNode = 0;
browseRequest.nodesToBrowse = UA_BrowseDescription_new();
browseRequest.nodesToBrowseSize = 1;
browseRequest.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);

/* Ask to return all nodes */

browseRequest.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL;

UA_BrowseResponse browseResponse = UA_Client_Service_browse(client, browseRequest);

/* Print out the results */

printf("%-9s %-16s %-16s %-16s\n", "NAMESPACE", "NODEID", "BROWSE NAME", "DISPLAY NAME");

for(size_t i = 0; i < browseResponse.resultsSize; ++i) {

  for(size_t j = 0; j < browseResponse.results[i].referencesSize; ++j) {

UA_ReferenceDescription *reference = &(browseResponse.results[i].references[j]);

if(reference->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC) {

printf("%-9d %-16d %-16.*s %-16.*s\n",
 reference->nodeId.nodeId.namespaceIndex,
 reference->nodeId.nodeId.identifier.numeric, (int)reference->browseName.name.length,
 reference->browseName.name.data, (int)reference->displayName.text.length,
 reference->displayName.text.data);

} else if(reference->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING) {

printf("%-9d %-16.*s %-16.*s %-16.*s\n",
 reference->nodeId.nodeId.namespaceIndex,
 (int)reference->nodeId.nodeId.identifier.string.length,
 reference->nodeId.nodeId.identifier.string.data,
 (int)reference->browseName.name.length, reference->browseName.name.data,
 (int)reference->displayName.text.length, reference->displayName.text.data);

};


  };

};

/* Clean up */

UA_BrowseRequest_deleteMembers(&browseRequest);

UA_BrowseResponse_deleteMembers(&browseResponse);

```
The final program should look like this
```c

#include <stdio.h>
/* Include the OPC-UA open62541 header file */
#include "open62541.h"

int main(void) {

    UA_Client *client = UA_Client_new(UA_ClientConfig_standard);

    /* List the endpoints that are found */

    UA_EndpointDescription* endpointArray = NULL;

    size_t endpointArraySize = 0;

    UA_StatusCode retval = UA_Client_getEndpoints(client,
						  "opc.tcp://localhost:4840",
						  &endpointArraySize,
						  &endpointArray);

    /* If the connection fails delete the client and return */
    if(retval != UA_STATUSCODE_GOOD) {

        UA_Array_delete(endpointArray,
			endpointArraySize,
			&UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);

	UA_Client_delete(client);

	return (int)retval;

    };

    /* Print out the endpoints found in the connection */

    printf("%i endpoints found\n", (int)endpointArraySize);

    for(size_t i=0;i<endpointArraySize;i++){

      printf("URL of endpoint %i is %.*s\n", (int)i,
               (int)endpointArray[i].endpointUrl.length,
               endpointArray[i].endpointUrl.data);
    };

    /* Delete the endpoints after they have been discovered */

    UA_Array_delete(endpointArray,
		    endpointArraySize,
		    &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);

    /* Connect to the local server */

    retval = UA_Client_connect(client, "opc.tcp://localhost:4840");

    /* If the connection fails delete the client and return */

    if(retval != UA_STATUSCODE_GOOD) {

        UA_Client_delete(client);

        return (int)retval;
    };

    /* Browse for some objects */

    printf("Browsing nodes in objects folder:\n");

    UA_BrowseRequest browseRequest;
    UA_BrowseRequest_init(&browseRequest);

    browseRequest.requestedMaxReferencesPerNode = 0;
    browseRequest.nodesToBrowse = UA_BrowseDescription_new();
    browseRequest.nodesToBrowseSize = 1;
    browseRequest.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);

    /* Ask to return all nodes */

    browseRequest.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL;

    UA_BrowseResponse browseResponse = UA_Client_Service_browse(client, browseRequest);

    /* Print out the results */

    printf("%-9s %-16s %-16s %-16s\n", "NAMESPACE", "NODEID", "BROWSE NAME", "DISPLAY NAME");

    for(size_t i = 0; i < browseResponse.resultsSize; ++i) {

      for(size_t j = 0; j < browseResponse.results[i].referencesSize; ++j) {

	UA_ReferenceDescription *reference = &(browseResponse.results[i].references[j]);

	if(reference->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC) {

	  printf("%-9d %-16d %-16.*s %-16.*s\n",
		 reference->nodeId.nodeId.namespaceIndex,
		 reference->nodeId.nodeId.identifier.numeric, (int)reference->browseName.name.length,
		 reference->browseName.name.data, (int)reference->displayName.text.length,
		 reference->displayName.text.data);

	} else if(reference->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING) {

	  printf("%-9d %-16.*s %-16.*s %-16.*s\n",
		 reference->nodeId.nodeId.namespaceIndex,
		 (int)reference->nodeId.nodeId.identifier.string.length,
		 reference->nodeId.nodeId.identifier.string.data,
		 (int)reference->browseName.name.length, reference->browseName.name.data,
		 (int)reference->displayName.text.length, reference->displayName.text.data);

	};


      };

    };

    /* Clean up */

    UA_BrowseRequest_deleteMembers(&browseRequest);

    UA_BrowseResponse_deleteMembers(&browseResponse);

    /* Disconnects the client internally */

    UA_Client_delete(client);

    return UA_STATUSCODE_GOOD;
}

```
# Putting it all together

Open a terminal and run the server:
```shell
$ ./server
[11/16/2017 23:54:17.588] info/network	TCP network layer listening on opc.tcp://nucuser-desktop:4840
```

Now open another terminal and run the client:
```shell
$ ./client
1 endpoints found
URL of endpoint 0 is opc.tcp://localhost:4840
Browsing nodes in objects folder:
NAMESPACE NODEID           BROWSE NAME      DISPLAY NAME    
0         61               FolderType       FolderType      
0         2253             Server           Server          
1         118              robot 0          robot 0         
1         121              robot 1          robot 1         
1         124              robot 2          robot 2         
1         127              robot 3          robot 3         
1         130              robot 4          robot 4         
1         133              robot 5          robot 5
```

Congratulations! You just made your client-server application work.

## Solutions
*   [OPC-UA Server ](https://create.arduino.cc/editor/inteliottestacc1/62288320-7ac6-4ac8-aad1-b0b2ebcdd356/preview)
*   [OPC-UA Client ](https://create.arduino.cc/editor/inteliottestacc1/62288320-7ac6-4ac8-aad1-b0b2ebcdd356/preview)


## Additional Information
* [OPC Foundation](https://opcfoundation.org/about/opc-technologies/opc-ua/) - The official OPC Foundation group
* [OPC Unified Architecture - Wikipedia](https://en.wikipedia.org/wiki/OPC_Unified_Architecture)
* [What is OPC? UA in a Minute - YouTube](https://www.youtube.com/watch?v=-tDGzwsBokY)
