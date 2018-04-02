/*
 * Copyright (c) 2017 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
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
	
  UA_ServerConfig *config = UA_ServerConfig_new_default();

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
