# A trivial OPC-UA client-server application

This lab will guide you through the implementation of a OPC UA weather application to illustrate client-server communications. This lab implements Node-OPCUA's Weather Station tutorial to aggregate data from different weather station on the server and then the client will pull data for it's particular interests. Both ends will run locally:
* Server: pulls data from a REST API call and aggregates the data in a OPC UA server framework Upon request reads and returns temperature, pressure, or humidity
* Client: reads weather data from the server and prints it

The original tutorial can be located here:
 http://node-opcua.github.io/tutorial/2015/07/05/weather-station.html

In OPC UA, servers may provide data as variables, like e.g. a measurement of a physical magnitude. Some variables may also be built-in.

This will just scratch the surface of OPC-UA communications.

Server and client implementation are split in a set of small steps to illustrate every concept independently. The complete files are also provided for reference as [client.c](./client.c) and [weather.js](./weather.js). Other source code files are included verbatim from the [open62541](https://github.com/open62541/open62541) [Tutorials](https://open62541.org/doc/0.2/tutorials.html) and distributed under the same terms: Public Somain (Creative Commons CC0).

A working [Makefile](./Makefile) is also provided.


# Server


## Accessing Weather Data through API

You will need to register to [worldweatheronline](https://developer.worldweatheronline.com/auth/register) to obtain your API key.
![](./images/WeatherSignUp.png)

Once registered add a trial key for Local Weather API.  Copy the key and paste it into a file named [worldweatheronline.key](./worldweatheronline.key)

Let's test the key by accessing the REST API.  In your browser open a new tab and enter
http://api.worldweatheronline.com/free/v2/weather.ashx?q=London&format=json&key=YOUR_API_KEY

Let's start with a simple Javascript that request weather data from London and print out the JSON message. The code would be

``` javascript
/*global require,console,setInterval */
Error.stackTraceLimit = Infinity;

/*global require,setInterval,console */
var cities = [ 'London','Paris','New York','Moscow','Ho chi min','Benjing','Reykjavik' ,'Nouakchott','Ushuaia' ,'Longyearbyen'];
// read the World Weather Online API key.
var fs = require("fs");
var key = fs.readFileSync("worldweatheronline.key");
function getCityWeather(city,callback) {
    var api_url="http://api.worldweatheronline.com/premium/v1/weather.ashx?q="+city+"+&format=json&key="+ key;
    var options = {
        url: api_url,
        "content-type": "application-json",
        json: ""
    };
    var request = require("request");
    request(options, function (error, response, body) {
      if (!error && response.statusCode === 200) {
        var data  = perform_read(city,body);
        callback(null,data);
      } else {
        callback(error);
      }
    });
}
function perform_read(city,body) {
    var obj = JSON.parse(body);
    var current_condition = obj.data.current_condition[0];
    var request = obj.data.request[0];
    return  {
        city:               request.query,
        date:               new Date(),
        observation_time:   current_condition.observation_time,
        temperature:        parseFloat(current_condition.temp_C),
        humidity:           parseFloat(current_condition.humidity),
        pressure:           parseFloat(current_condition.pressure),
        weather:            current_condition.weatherDesc.value
    };
}
getCityWeather("London",function(err,data) {
         if (!err) {
            console.log("London",JSON.stringify(data, null," "));
         }  else {
            console.log("error city","London" , err);
         }
     });

```
Now lets query more than one city in our array and put a timer on it for 10 seconds
```Javascript
var city_data_map = { };
// a infinite round-robin iterator over the city array
var next_city = function(arr) {
   var counter = arr.length;
   return function() {
      counter += 1;
      if (counter>=arr.length) {
        counter = 0;
      }
      return arr[counter];
   };
}(cities);
function update_city_data(city) {
    getCityWeather(city,function(err,data) {
         if (!err) {
            city_data_map[city] = data;
            console.log(city,JSON.stringify(data, null," "));
         }  else {
            console.log("error city",city , err);
         }
     });
}
// make a API call every 10 seconds
var interval = 10* 1000;
setInterval(function() {
     var city = next_city();
     update_city_data(city);
}, interval);

```
Great! Now that we are pulling data at a interval.  Let's put it somewhere. Using the OPC UA server framework lets organize the data.

```Javascript
var opcua = require("node-opcua");

var server = new opcua.OPCUAServer({
   port: 16664 // the port of the listening socket of the server
});

server.buildInfo.productName = "WeatherStation";
server.buildInfo.buildNumber = "7658";
server.buildInfo.buildDate = new Date(2014,5,2);
function post_initialize() {
    console.log("initialized");
    function construct_my_address_space(server) {
       // declare some folders
       var citiesNode  = server.engine.addressSpace.addFolder("ObjectsFolder",{ browseName: "Cities"});
       function create_CityNode(city_name) {
           // declare the city node
           var cityNode = server.engine.addressSpace.addFolder(citiesNode,{ browseName: city_name });
           server.engine.addressSpace.addVariable({
               componentOf: cityNode,
               browseName: "Temperature",
               dataType: "Double",
               value: {  get: function () { return extract_value(city_name,"temperature"); } }
           });
           server.engine.addressSpace.addVariable({
               componentOf: cityNode,
               browseName: "Humidity",
               dataType: "Double",
               value: {  get: function () { return extract_value(city_name,"humidity"); } }
           });
           server.engine.addressSpace.addVariable({
               componentOf: cityNode,
               browseName: "Pressure",
               dataType: "Double",
               value: {  get: function () { return extract_value(city_name,"pressure"); } }
           });
       }
       cities.forEach(function(city) {
           create_CityNode(city);
       });
       function extract_value(city_name,property) {
           var city = city_data_map[city_name];
           if (!city) {
               return opcua.StatusCodes.BadDataUnavailable
           }
           var value = city[property];
           return new opcua.Variant({dataType: opcua.DataType.Double, value: value });
       }
    }
    construct_my_address_space(server);
    server.start(function() {
        console.log("Server is now listening ... ( press CTRL+C to stop)");
        console.log("port ", server.endpoints[0].port);
        var endpointUrl = server.endpoints[0].endpointDescriptions()[0].endpointUrl;
        console.log(" the primary server endpoint url is ", endpointUrl );        
    });
}
server.initialize(post_initialize);

```
We now have a functioning server in OPC UA javascript collecting and aggregating data for consuming by the client/gateway.  Let's build a Client on the edge in C++ to interface with the data.

First lets get a tool to help write the Client. Register and download UaExpert at https://www.unified-automation.com/downloads/opc-ua-clients/file/download/details/uaexpert-v140.html

Once installed, open UaExpert and add a new server.  Use the url
opc.tcp://nucuser-desktop:16664

Click the connect button.

We can now see the data on the server and how it is organized.

In the Client window open a file named client.c

```c
#include <signal.h>

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

We compile and test this example:
```shell
# Alternatively, you can use the Makefile to handle compilation.
$ gcc trivial_server.c open62541.c -o server
$ ./server
<Press Ctrl-C>
^C[09/26/2017 12:26:24.599] info/userland	received ctrl-c
$
```

As you can see, when our process receives SIGINT or SIGTERM, the handler is run, a message is printed by UA_LOG_INFO, and the process exits.



## Minimal skeleton

Let's implement the actual server. First we need to add the corresponding header:
```c
#include "open62541.h"
```
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
    UA_ServerNetworkLayer nl =
        UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, 4840);
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
    nl.deleteMembers(&nl);
```

The full example should look like:
```c
#include <signal.h>
#include "open62541.h"

UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_ServerConfig config = UA_ServerConfig_standard;
    UA_ServerNetworkLayer nl =
        UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, 4840);
    config.networkLayers = &nl;
    config.networkLayersSize = 1;
    UA_Server *server = UA_Server_new(config);

    UA_Server_run(server, &running);

    UA_Server_delete(server);
    nl.deleteMembers(&nl);
    return 0;
}
```

Now let's compile again:
```shell
# Alternatively, you can use the Makefile to handle compilation.
$ gcc trivial_server.c open62541.c -o server
```

Our server is ready! Now we just need a client to read from it...


# Client

### A client that connects

Now let's implement the client side. The minimal client would look like this:
```c
int main(void) {

    UA_Client *client = UA_Client_new(UA_ClientConfig_standard);
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }


    // Further client code would go here


    UA_Client_delete(client); /* Disconnects the client internally */
    return UA_STATUSCODE_GOOD;
}
```

The first block creates a client with the same configuration as the server, and then tries to connect to it. Then it checks for the connection, and if an error occurs, it exits.

We will include our client code immediately after the connection is established.

A second block of code that will take care of freeing up the resources and returning the error code is also introduced.

This unfinished example can already be compiled by running:
```shell
# Alternatively, you can use the Makefile to handle compilation.
$ gcc trivial_server.c open62541.c -o server
```


## A client holding a variable

Information in OPC UA is modeled as a hierarchy of nodes. The value for each node can be read and stored in a variable.

[open62541](https://github.com/open62541/open62541) uses a variant type to store variables. This type is able to store scalar values and arrays regardless of their type.

Variables must be initialized and released. In our server, we will do it by writing:
```c
    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&value);


    // Here the code to read and handle the variable


    UA_Variant_deleteMembers(&value);
```

## Minimal skeleton

After implementing the connection and variable handling pieces, we just need to point to the node in the information model, and read it.

This is the minimal code to read the variable:

```c
    /* NodeId of the variable holding the current time */
    const UA_NodeId nodeId =
        UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME);

    UA_Client_readValueAttribute(client, nodeId, &value);
```

First we identify the node by its id. In this case, the server will return UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME, a predefined "server status" value holding the current date and time.

Reading the attribute's value requires us to provide the client, node to read, and a variable to store the value.

However, the code above is lacking any kind of error checking or actual use of the value read. We will fix it with some checks and printing the date:
```c
    retval = UA_Client_readValueAttribute(client, nodeId, &value);
    if(retval == UA_STATUSCODE_GOOD &&
       UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DATETIME])) {

        UA_DateTime raw_date = *(UA_DateTime*)value.data;
        UA_String string_date = UA_DateTime_toString(raw_date);
        printf("string date is: %.*s\n", (int)string_date.length, string_date.data);
        UA_String_deleteMembers(&string_date);

    }
```

The function reading the value returns an status code that we use to identify any problems retrieving it. We also check for the correctness of the type returned.


# Putting it all together

Open a terminal and run the server:
```shell
$ ./server
[09/26/2017 09:25:25.515] info/network	TCP network layer listening on opc.tcp://garlic:4840
```

Now open another terminal and run the client:
```shell
$ ./client
string date is: 09/26/2017 09:28:23.617.556.000
```

Congratulations! You just made your trivial client-server application work.
