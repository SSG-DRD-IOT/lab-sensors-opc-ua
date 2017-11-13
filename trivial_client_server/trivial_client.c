/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */
#define UA_ENABLE_SUBSCRIPTIONS
#ifdef UA_NO_AMALGAMATION
# include "ua_types.h"
# include "ua_client.h"
# include "ua_client_highlevel.h"
# include "ua_nodeids.h"
# include "ua_network_tcp.h"
# include "ua_config_standard.h"
#else
# include "open62541.h"
# include <string.h>
# include <stdlib.h>
#endif

#include <string.h>
#include <stdio.h>

static void
handler_TheAnswerChanged(UA_UInt32 monId, UA_DataValue *value, void *context) {
    printf("The Answer has changed!\n");
}

static UA_StatusCode
nodeIter(UA_NodeId childId, UA_Boolean isInverse, UA_NodeId referenceTypeId, void *handle) {

    UA_Client *client = UA_Client_new(UA_ClientConfig_standard);

    /* Listing endpoints */
    UA_EndpointDescription* endpointArray = NULL;
    size_t endpointArraySize = 0;
    UA_StatusCode retval = UA_Client_getEndpoints(client, "opc.tcp://nucuser-desktop:16664",
                                                  &endpointArraySize, &endpointArray);
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Array_delete(endpointArray, endpointArraySize, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
        UA_Client_delete(client);
        return (int)retval;
    }
    
    if(isInverse)
        return UA_STATUSCODE_GOOD;
    UA_NodeId *parent = (UA_NodeId *)handle;
    printf("%d, %d --- %d ---> NodeId %d, %d\n",
           parent->namespaceIndex, parent->identifier.numeric,
           referenceTypeId.identifier.numeric, childId.namespaceIndex,
           childId.identifier.numeric);

        /* Same thing, this time using the node iterator... */
    UA_NodeId *child = UA_NodeId_new();
    *child = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_Client_forEachChildNodeCall(client, UA_NODEID_NUMERIC(1, 1013),
                                   nodeIter, (void *) child);

    UA_NodeId_delete(child);
    return UA_STATUSCODE_GOOD;
}

int main(int argc, char *argv[]) {

  char cityTemperature[4];
  int node;

  node = 1022;

  if(argv[1] != NULL) {
  strcpy(cityTemperature, argv[1]);
   node = atoi(cityTemperature);
  };
  
  UA_Client *client = UA_Client_new(UA_ClientConfig_standard);

    /* Listing endpoints */
    UA_EndpointDescription* endpointArray = NULL;
    size_t endpointArraySize = 0;
    UA_StatusCode retval = UA_Client_getEndpoints(client, "opc.tcp://nucuser-desktop:16664",
                                                  &endpointArraySize, &endpointArray);
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Array_delete(endpointArray, endpointArraySize, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
        UA_Client_delete(client);
        return (int)retval;
    }
    printf("%i endpoints found\n", (int)endpointArraySize);
    for(size_t i=0;i<endpointArraySize;i++){
        printf("URL of endpoint %i is %.*s\n", (int)i,
               (int)endpointArray[i].endpointUrl.length,
               endpointArray[i].endpointUrl.data);
    }
    UA_Array_delete(endpointArray,endpointArraySize, &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);

    /* Connect to a server */
    /* anonymous connect would be: retval = UA_Client_connect(client, "opc.tcp://localhost:16664"); */
    retval = UA_Client_connect(client, "opc.tcp://nucuser-desktop:16664");
    //retval = UA_Client_connect_username(client, "opc.tcp://localhost:16664", "user1", "password");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }

    /* Browse some objects */
    printf("Browsing nodes in objects folder:\n");
    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();
    bReq.nodesToBrowseSize = 1;
    bReq.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER); /* browse objects folder */
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
    UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);
    printf("%-9s %-16s %-16s %-16s\n", "NAMESPACE", "NODEID", "BROWSE NAME", "DISPLAY NAME");
    for (size_t i = 0; i < bResp.resultsSize; ++i) {
        for (size_t j = 0; j < bResp.results[i].referencesSize; ++j) {
            UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
            if(ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC) {
                printf("%-9d %-16d %-16.*s %-16.*s\n", ref->nodeId.nodeId.namespaceIndex,
                       ref->nodeId.nodeId.identifier.numeric, (int)ref->browseName.name.length,
                       ref->browseName.name.data, (int)ref->displayName.text.length,
                       ref->displayName.text.data);
            } else if(ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING) {
                printf("%-9d %-16.*s %-16.*s %-16.*s\n", ref->nodeId.nodeId.namespaceIndex,
                       (int)ref->nodeId.nodeId.identifier.string.length,
                       ref->nodeId.nodeId.identifier.string.data,
                       (int)ref->browseName.name.length, ref->browseName.name.data,
                       (int)ref->displayName.text.length, ref->displayName.text.data);
            }
            /* TODO: distinguish further types */
        }
    }
    UA_BrowseRequest_deleteMembers(&bReq);
    UA_BrowseResponse_deleteMembers(&bResp);

    /* Same thing, this time using the node iterator... */
    UA_NodeId *parent = UA_NodeId_new();
    *parent = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_Client_forEachChildNodeCall(client, UA_NODEID_NUMERIC(1, 1000),
                                   nodeIter, (void *) parent);
   
    UA_NodeId_delete(parent);

#ifdef UA_ENABLE_SUBSCRIPTIONS
    /* Create a subscription */
    UA_UInt32 subId = 0;
    UA_Client_Subscriptions_new(client, UA_SubscriptionSettings_standard, &subId);
    if(subId)
        printf("Create subscription succeeded, id %u\n", subId);
    /* Add a MonitoredItem */
    UA_NodeId monitorThis = UA_NODEID_NUMERIC(1, node);
    UA_UInt32 monId = 0;
    UA_Client_Subscriptions_addMonitoredItem(client, subId, monitorThis, UA_ATTRIBUTEID_VALUE,
                                             &handler_TheAnswerChanged, NULL, &monId);
    if (monId)
        printf("Monitoring 'Benjing', id %u\n", subId);
    /* The first publish request should return the initial value of the variable */
    UA_Client_Subscriptions_manuallySendPublishRequest(client);
#endif
    
    /* Read attribute */
    UA_Double value = 0.0;
    printf("\nReading the value of node (1022, \"Temperature\"):\n");
    UA_Variant *val = UA_Variant_new();
 
    retval = UA_Client_readValueAttribute(client, UA_NODEID_NUMERIC(1, node), val);
 
    if(retval == UA_STATUSCODE_GOOD) {
      value = *(UA_Double*)val->data;
            printf("the value is: %f\n", value);
    }
    UA_Variant_delete(val);

    UA_Client_disconnect(client);
    UA_Client_delete(client);
    return (int) UA_STATUSCODE_GOOD;
}
