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
#include <stdio.h>
/* Include the OPC-UA open62541 header file */ 
#include "open62541.h"

int main(void) {

    UA_Client *client = UA_Client_new(UA_ClientConfig_standard);

    /* List the endpoints that are found */
    
    UA_EndpointDescription* endpointArray = NULL;

    size_t endpointArraySize = 0;

    UA_StatusCode retval = UA_Client_getEndpoints(client,
						  "opc.tcp://localhost:16664",
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
    
    retval = UA_Client_connect(client, "opc.tcp://localhost:16664"); 

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
