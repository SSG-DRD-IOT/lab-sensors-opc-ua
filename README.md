#  OPC-UA client-server application runtime tunning 

This lab will guide you through the synchonizing network clock domains for OPC UA application to illustrate multiple client-server communications.

## PTP time-synchronization
The Precision Time Protocol (PTP) is a protocol used to synchronize clocks throughout a computer network. On a local area network, it achieves clock accuracy in the sub-microsecond range, making it suitable for measurement and control systems.
https://www.nist.gov/el/intelligent-systems-division-73500/ieee-1588 

 IEEE standard 1588 Precision Time Protocol (PTP) support is provide in every linux distribution including http://manpages.ubuntu.com/manpages/bionic/man8/ptp4l.8.html 
```shell
$ sudo apt-get install ethtool linuxptp tshark
git clone https://github.com/SSG-DRD-IOT/lab-sensors-opc-ua.git -b milano-workshop
mv lab-sensors-opc-ua lab-timing-opc-ua
cd lab-timing-opc-ua
```

At start we need to discover what time-synchonization feature our machine Network Interface Controller(NIC) are capable of : 
```shell
$ sudo ethtool -T enp2s0
$ sudo ethtool -T enp3s0
```

For UP2, unfortunatly RT8186G NIC doesn't provide any HW time-synchonization features, unlike most intel NICs : i210, i211, e1000, i350,... (.e.g. expose /dev/ptp0 device providing L2/UPDv4/UPDv6 HW-offload of Announce/Sync/Follow_Up/Delay_Req/Delay_Resp/... messages communication, extenal HW-timestamping from an Free Running Timer, Pulse-Per-Second on External Pins,...).

So software PTP time-synchronization is our only option here.

PTP configuration file are provided as examples to build : 
*ONE _master-clock_ broadcasting _Announce/Sync/Delay_Req_ packets 
```shell
sudo ptp4l -i enp2s0 -f ptp4l_1.conf -m
```
*SEVERAL _slave-clock_ (-s) responding with _Delay_Resp/...__ packets
```shell
sudo ptp4l -i enp2s0 -f ptp4l_2.conf -m -s
```

To report the time differnce on any NIC acting as PTP time-synchronized slave-clock ptp4l provide provide handy tools:    
```shell
sudo pmc -u -b 0 'GET TIME_STATUS_NP'
sudo pmc -u -b 0 'GET CURRENT_DATA_SET'
sudo pmc -u -b 0 'GET PORT_DATA_SET'
```

Adjust RTC and System clocks :  
```shell
$ sudo hwclock --rtc /dev/rtc0 && sudo hwclock --utc
Tue 05 Jun 2018 09:22:42 AM PDT  .045091 seconds
Tue 05 Jun 2018 09:23:07 AM PDT  .697110 seconds

$ chmod +x ./adjtimex
$ sudo ./adjtimex --adjust

$ sudo hwclock --rtc /dev/rtc0 && sudo hwclock --utc
Tue 05 Jun 2018 09:26:50 AM PDT  .201350 seconds
Tue 05 Jun 2018 09:26:51 AM PDT  .013758 seconds
```

Finally, we link the specific NIC PTP time-synchronized clock to the always-runnning RTC clock with _phc2sys_ as followed:

```shell
$ sudo phc2sys -s CLOCK_REALTIME -w -m

$ sudo pmc -u -b 0 'GET TIME_STATUS_NP' | awk '/ingress_time/ { printf("%s.%s\n", substr($2, 1, 10), substr($2, 11, 18))}' && ./adjtimex -p | awk '/raw time:/ { print  $6 }'
```

To better understand how Ethernet traffic introduce PTP Master and Slave clock jitter we capture port 319 and 320 traffic and build statistics over significantly large number PTP packets (NB: TAI vs UTC time diff is 36s today e.q 3600000000.0 in epoch time) 

```shell
sudo tcpdump -i enp2s0 -w ptptmp.pcap -j adapter_unsynced -tt --time-stamp-precision=nano port 319 or port 320 -c 100 && tshark -r ptptmp.pcap -t e -E separator=, -E header=n -2 -R ptp.v2.control==3 -Tfields \
-e frame.number \
-e frame.time_epoch \
-e ptp.v2.fu.preciseorigintimestamp.seconds \
-e ptp.v2.fu.preciseorigintimestamp.nanoseconds > ptptmp.out && python ./ptp-ts_offset.py -i ptptmp.out -o 3600000000.0 > ptptmp.out.gp && head ptptmp.out.gp && ./stats.sh -c 1 -f ptptmp.out.gp
149.0
216.0
304.0
309.0
299.0
304.0
200.0
299.0
300.0
min:    +1.490000e+02
max:    +3.090000e+02
pk-pk:  +1.600000e+02
mean:   +2.644444e+02
stddev: +5.978526e+01
count:   9

```

IEEE1588v2 PTP Traffic can be easily analyzed using [Wireshark PTP Filters](./tshark_ptp-filters_fields.md)  
```shell
sudo tcpdump -i enp2s0 -w ptptmp.pcap -j adapter_unsynced -tt --time-stamp-precision=nano port 319 or port 320 -c 100 && tshark -r ptptmp.pcap -t e -E separator=, -E header=n -2 -R ptp.v2.control==3 -Tfields \
-e frame.number \
-e frame.time_epoch \
-e ptp.v2.dr.receivetimestamp.seconds \
-e ptp.v2.dr.receivetimestamp.nanoseconds > ptptmp.out && python ./ptp-ts_offset.py -i ptptmp.out -o 3600000000.0 > ptptmp.out.gp && head ptptmp.out.gp && ./stats.sh -c 1 -f ptptmp.out.gp
```

Congratulations! You just made and measured your board time-synchronized between the master and slave device.

## Open Platform Communications - Unified Architecture

Here our objectives are touch some concepts of Industrial Network Traffic determinism that all Industrial Protocol MUST provide. 

Industrial infrastructure usually instanciate multiple compute nodes (ex: OPC-UA client-server) over the OT network :
* OPC-UA server: instance object node and UA_String variable that read RTC time-stamp object nodes on every Read Request.
* OPC-UA client: Queries _Time Stamp_ object node accross one or several  server to be able to estimate the RTC time between each clients and servers accross PTP time-synchronized networks.

In OPC UA, servers may provide information as object nodes and variable nodes, and _sourceTimestamp_.

opc-ua-multi-server and opc-ua-multi-client implementation are split in a set of small steps to illustrate Network PTP, System and Realtime (RTC) clock-domains independently. The complete files are also provided for reference as [opc-ua-multi-server.c](./opc-ua-multi-server.c) and [opc-ua-multi-client.c](./opc-ua-multi-client.c). 

The example is an extension of the tutorials and source from [open62541](https://github.com/open62541/open62541) [Tutorials](https://open62541.org/doc/0.2/tutorials.html) and distributed under the same terms: Public Domain (Creative Commons CC0).

A working [Makefile](./Makefile) is also provided.

IMPORTANT!! This example is based of sligthly older library open62541 release 0.2 (commit: 24604543cd071ad04b6a19ad07b8456cd0c91340). 
To avoid compile errors, please make sure you clone & checkout exacly this commit or use makefile that link with prebuilt static libraries are availables under this repo.

### Multiple OPC-UA Server 

OPC-UA process that we can interrupt with Ctrl-C. We add the capability to select Real-Time clock device (e.g /dev/rtc0) that OPC-UA server read from on

When a value changes continuously, such as the system time, updating the value in a tight loop would take up a lot of resources. Value callbacks allow to synchronize a variable value with an external representation. They attach callbacks to the variable that are executed before every read and after every write operation.

_read_ets_ callbacks function on node variable for every _ReadRequest_ could be:
```c
#ifdef USE_OPEN62541
static UA_StatusCode read_ets(void *handle, const UA_NodeId nodeId,
                  UA_Boolean sourceTimeStamp,
                  const UA_NumericRange *range,
                  UA_DataValue *value)
#else /* ndef USE_OPEN62541 */
  static int read_ets(int fd)
#endif /* ndef USE_OPEN62541 */
{

  struct tm tm;
  unsigned long n, *epoch_p;
  int rc=-1;
  char buf[32];
#ifdef USE_OPEN62541
  int fd = *(int *)handle;
  
  if (range) {
    value->hasStatus = true;
    value->status = UA_STATUSCODE_BADINDEXRANGEINVALID;
    return UA_STATUSCODE_GOOD;
  }
#endif /* def USE_OPEN62541 */

  rc = ioctl (fd, RTC_RD_TIME, &tm);
  /* RTC_RD_TIME can fail when the device driver detects
     that the RTC isn't running or contains invalid data.
     Such failure has been detected earlier, unless: We used
     noint_fallback=1 to get busywait_uip_fall() as fallback.
     Or: UIE interrupts do beat, but RTC is invalid. */
  if (rc == -1) {
    fprintf(stderr, "RTC_RD_TIME failed\n");
#ifdef USE_OPEN62541
    value->hasValue = false;
    return UA_STATUSCODE_GOOD;
#else
    return 0;
#endif    
  }
  
  LOG("event at %4d/%.2d/%.2d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  
  snprintf(buf, sizeof(buf), "%4d/%.2d/%.2d-%02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour , tm.tm_min, tm.tm_sec);

  #ifdef USE_OPEN62541
  UA_String string = UA_String_fromChars(buf);

  UA_Variant_setScalarCopy(&value->value, &string, &UA_TYPES[UA_TYPES_STRING]);
  value->hasValue = true;
  if (sourceTimeStamp) {
    value->hasSourceTimestamp = true;
    value->sourceTimestamp = UA_DateTime_now();
  }

  return UA_STATUSCODE_GOOD;
#else /* ndef USE_OPEN62541 */
  return 0;
#endif /* ndef USE_OPEN62541 */
}
```

As a starting point, assume that a variable for a value of type DateTime has been created in the server with the identifier “Time stamp”. Assuming that our applications gets triggered when a new value arrives from the underlying process, we can just write into the variable. 

```c
static int get_ets(int fd, int index)
{

  struct tm tm;
  int rc=-1;

#ifdef USE_OPEN62541
  /* Init the server. */
  UA_ServerNetworkLayer nl = UA_ServerNetworkLayerTCP(
                              UA_ConnectionConfig_standard, DEFAULT_OPC_UA_PORT);
  UA_ServerConfig config = UA_ServerConfig_standard;

  config.networkLayers = &nl;
  config.networkLayersSize = 1;
  UA_Server *server = UA_Server_new(config);

  /* Add a variable node. */
  /* 1) Set the variable attributes. */
  UA_VariableAttributes attr;

  UA_VariableAttributes_init(&attr);
  attr.description = UA_LOCALIZEDTEXT("en_US", "Time stamp");
  attr.displayName = UA_LOCALIZEDTEXT("en_US", "Time stamp");

  /* 2) Define where the variable shall be added with which browse name. */
  UA_NodeId new_node_id = UA_NODEID_STRING(1, "time.stamp");
  UA_NodeId parent_node_id = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
  UA_NodeId parent_ref_node_id = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
  UA_NodeId variable_type = UA_NODEID_NULL; /* No variable type defined. */
  UA_QualifiedName browse_name = UA_QUALIFIEDNAME(1, "Time stamp");

  UA_DataSource data_source = (UA_DataSource) {
    .handle = &fd,
    .read = read_ets,
    .write = NULL
  };
  UA_NodeId data_source_id;

  /* 3) Add the variable with data source. */
  UA_Server_addDataSourceVariableNode(server, new_node_id,
                      parent_node_id, parent_ref_node_id,
                      browse_name, variable_type, attr,
                      data_source, &data_source_id);
#endif /* def USE_OPEN62541 */

  rc = ioctl (fd, RTC_RD_TIME, &tm);
  /* RTC_RD_TIME can fail when the device driver detects
     that the RTC isn't running or contains invalid data.
     Such failure has been detected earlier, unless: We used
     noint_fallback=1 to get busywait_uip_fall() as fallback.
     Or: UIE interrupts do beat, but RTC is invalid. */
  if (rc == -1)
  {
    perror("RTC_RD_TIME ");
#ifdef USE_OPEN62541
    UA_Server_delete(server);
    nl.deleteMembers(&nl);
#endif /* def USE_OPEN62541 */
    return -1;
  }  

  LOG("RTC_RD_TIME event at %4d/%.2d/%.2d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  
#ifdef USE_OPEN62541
  /* Run the server loop. */
  UA_Server_run(server, &running);
#else  /* ndef USE_OPEN62541 */
  while (running)
    read_ets(fd);
#endif /* ndef USE_OPEN62541 */

  /* Disable the external time stamp feature. */
#ifdef USE_OPEN62541
  UA_Server_delete(server);
  nl.deleteMembers(&nl);
#endif /* def USE_OPEN62541 */

  return 0;
}
```

It follows the main server code, making use of the above definitions 
```c
static void sig_handler(int sig)
{
  /* Reset signal. */
  signal(sig, sig_handler);
  LOG("Received signal %d\n", sig);
  running = 0;
}

static void usage(char *prog_name)
{
  fprintf(stderr,
      "Usage: %s [options]\n"
      "Options:\n"
      "  -d name     RTC device to open.\n"
      "     Default: %s\n"
      "  -h          Print this message and exit.\n"
      "  -v          Verbose output\n"
      "",
      prog_name,
      RTC_DEVICE);
}

int main(int argc, char *argv[])
{
  char *prog_name, *rtc_dev;
  clockid_t clk_id;
  int c_ets, i_ets;
  int fd, opt;

  /* Installing signal handlers. */
  signal(SIGHUP, sig_handler);
  signal(SIGINT, sig_handler);
  signal(SIGQUIT, sig_handler);

  c_ets = DEFAULT_ETS_CHAN;
  i_ets = DEFAULT_ETS_INDEX;

  /* Parse command line arguments. */
  while ((opt = getopt(argc, argv, "d:hv")) != EOF) {
    switch (opt) {
    case 'd':
      rtc_dev = optarg;
      break;
    case 'h':
      usage(prog_name);
      return 0;
    case 'v':
      verbose++;
      break;
    default: /* '?' */
      usage(prog_name);
      return -1;
    }
  }

  LOG("Hello from %s!\n", prog_name);

  fd = open(rtc_dev, O_RDWR);
  if (fd < 0) {
    fprintf(stderr, "Failed to open %s: %d (%s)\n", rtc_dev, errno, strerror(errno));
    return -1;
  }
  LOG("RTC device: %s\n", rtc_dev);

  /* These macros are defined in linux/posix-timers.h, but not able to
   * include the file.
   */
  #define CPUCLOCK_MAX            3
  #define CLOCKFD                 CPUCLOCK_MAX
  #define FD_TO_CLOCKID(fd)       ((~(clockid_t) (fd) << 3) | CLOCKFD)
  /* end */
  clk_id = FD_TO_CLOCKID(fd);
  if (clk_id == -1) {
    fprintf(stderr, "Failed to get clock id from %d\n", fd);
    close(fd);
    return -1;
  }

  if (get_ets(fd, i_ets)) {
    fprintf(stderr, "Cannot get external time stamps \n", i_ets);
    /* Fall through for cleanup. */
  }

  close(fd);
  LOG("Bye from %s!\n", prog_name);

  return 0;
}
```

### Multiple OPC-UA Clients 

Open62541 provides both a server and client side API, so creating a client is as easy as creating a server.

Here the clients sent _UA_ReadRequest_ within a user-defined cycle-time and  server list to get Time-stamp node value, then store into a log file.     
```c
static char *get_name(char *base)
{
    char *name;

    /* Extract the name from base. */
    name = strrchr(base, '/');
    name = name ? name + 1 : base;

    return name;
}

static void sig_handler(int sig)
{
    /* Reset signal. */
    signal(sig, sig_handler);
    LOG("Received signal %d\n", sig);
    running = 0;
}

static void usage(char *prog_name)
{
    fprintf(stderr,
            "Usage: %s servers [options]\n"
            "Servers:\n"
            "  List of OPC UA servers, separated by space\n"
            "  e.g. opc.tcp://<IPv4 server address>:4840\n"
            "Options:\n"
            "  -d value    Delay in usec between every read request.\n"
            "     Default: %d\n"
            "  -l name     Log file name.\n"
            "     Default: %s\n"
            "  -h          Print this message and exit.\n"
            "  -v          Verbose output\n"
            "",
            prog_name,
            DELAY_USEC,
            DEFAULT_LOG);
}

int main(int argc, char *argv[])
{
    int delay_s, delay_us, fd, i, m, n;
    struct timeval tv;
    char buf[MAX_BUF_LINE];
    char *log_fn, *prog_name;
    char *endpoint[MAX_SERVERS];
    UA_Client *client[MAX_SERVERS];
    UA_StatusCode retval;
    UA_String value;
    UA_ReadResponse read_resp;
    UA_ReadRequest read_req;

    /* Installing signal handlers. */
    signal(SIGHUP, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);

    delay_s = 0;
    delay_us = DELAY_USEC;
    log_fn = DEFAULT_LOG;
    prog_name = get_name(argv[0]);
    for (i = 0; i < MAX_SERVERS; i++) {
        endpoint[i] = NULL;
        client[i] = NULL;
    }

    /* Connect to servers (client) if the URL is valid. */
    for (m = n = 0, i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
            case 'd':
                if (++i < argc) {
                    delay_us = strtol(argv[i], NULL, 0);
                    LOG("%d: Set delay to %d usec\n", i, delay_us);
                    break;
                }
                usage(prog_name);
                return -1;
            case 'l':
                if (++i < argc) {
                    log_fn = argv[i];
                    LOG("%d: Save the log to '%s'\n", i, log_fn);
                    break;
                }
                usage(prog_name);
                return -1;
            case 'v':
                verbose++;
                break;
            default:
                usage(prog_name);
                return -1;
            }
        } else if (strncmp("opc.tcp://", argv[i], 10) == 0) {
            if (n < MAX_SERVERS) {
                LOG("Saving server#%d: %s\n", n, argv[i]);
                endpoint[n] = argv[i];
                m = ++n;
            } else {
                if (m == n) {
                    fprintf(stderr, "Not enough buffer to store servers.\n"
                                    "Please consider increase the buffer size (%d).\n",
                            m);
                    fprintf(stderr, "The following servers are not connected:\n");
                }
                fprintf(stderr, "%d: Ignoring server#%d: %s\n", i, m, argv[i]);
                ++m;
            }
        } else {
            fprintf(stderr, "%d: Ignoring server not start with \"opc.tcp://\": %s\n",
                    i, argv[i]);
        }
    }
    if (n == 0) {
        fprintf(stderr, "No server is specified!\nExit now.\n");
        usage(prog_name);
        return 0;
    }

    LOG("Number of servers to connect: %d\n", n);
    for (m = i = 0; i < n; i++) {
        LOG("Connecting server#%d: %s\n", i, endpoint[i]);

        /* Create a client and connect. */
        client[m] = UA_Client_new(UA_ClientConfig_standard);

        /* Connect with username would be:
         * retval = UA_Client_connect_username(client, "opc.tcp://localhost:4840", "user1", "password");
         */
        retval = UA_Client_connect(client[m], endpoint[i]);
        if (retval != UA_STATUSCODE_GOOD) {
            fprintf(stderr, "Unable to connect to server#%d: %s\n", i, endpoint[i]);
            UA_Client_delete(client[m]);
            client[m] = NULL;
            endpoint[i] = NULL;
            continue;
        }

        LOG("Server#%d connected: %s\n", m, endpoint[i]);
        ++m;
    }
    n = m;
    LOG("Number of servers connected: %d\n", n);

    /* Create a ReadRequest with one entry. */
    UA_ReadRequest_init(&read_req);
    read_req.nodesToRead = UA_Array_new(1, &UA_TYPES[UA_TYPES_READVALUEID]);
    read_req.nodesToReadSize = 1;
    /* Define the node and attribute to be read. */
    read_req.nodesToRead[0].nodeId = UA_NODEID_STRING_ALLOC(1, "time.stamp");
    read_req.nodesToRead[0].attributeId = UA_ATTRIBUTEID_VALUE;

    fd = open(log_fn, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd < 0)
        fprintf(stderr, "Fail to open log file '%s'\n", log_fn);
    else
        LOG("Writing log to '%s'\n", log_fn);

    delay_s = delay_us / 1000000;
    delay_us = delay_us % 1000000;
    while (running) {
        for (i = 0; i < n; i++) {
            read_resp = UA_Client_Service_read(client[i], read_req);
            if ((read_resp.responseHeader.serviceResult == UA_STATUSCODE_GOOD) &&
                (read_resp.resultsSize > 0) &&
                (read_resp.results[0].hasValue) &&
                (read_resp.results[0].value.type == &UA_TYPES[UA_TYPES_STRING])) {
                value = *(UA_String *)read_resp.results[0].value.data;
                value.data[value.length] = 0;
                LOG("server#%d: %s\n", i, value.data);
                if (fd >= 0) {
                    snprintf(buf, sizeof(buf), "server#%d: %s\n", i, value.data);
                    write(fd, buf, strlen(buf));
                }
            }
            UA_ReadResponse_deleteMembers(&read_resp);
        }

        /* Delay some time before next read. */
        tv.tv_sec = delay_s;
        tv.tv_usec = delay_us;
        select(1, NULL, NULL, NULL, &tv);
    }

    if (fd >= 0)
        close(fd);

    UA_ReadRequest_deleteMembers(&read_req);

    /* Disconnect from servers. */
    for (i = n - 1; i >= 0; i--) {
        UA_Client_disconnect(client[i]);
        UA_Client_delete(client[i]);
    }

    return 0;
}
```

In this example you can use the Makefile to handle compilation :
```shell
$ cd open62541
$ cmake -DBUILD_SHARED_LIBS=OFF && make
$ cd ..
$ make
```

### Putting it all together, 
Run the server localy or remotly from  another machine :
```shell
$ sudo ./opc-ua-multiple-server -d /dev/rtc0
```

Now open run the client pointing to OPC-UA server IPv4 address and port 4840 :
```shell
$ ./opc-ua-multiple-client opc.tcp://<server#0>:4840 -d <cycle-time in us .ex 250=250us or 60000=60ms> -l <timesptamp logfile>
```

### Analyzing the OPC-UA traffic latency
OPC-UA _UA_ReadRequest_ (opcua.servicenodeid.numeric==634) can be easily analyzed & measured using [Wireshark OPC-UA Binary Filters] (./tshark_opcua-filters_fields.md)

```shell
$ sudo tcpdump -i enp2s0 -w tmp.pcap -j adapter_unsynced -tt --time-stamp-precision=nano port 4840 or port 319 or port 320 -c 10000 && tshark -r tmp.pcap -t e -2 -R opcua.servicenodeid.numeric==634 -E separator=, -E header=n -Tfields \
-e frame.number \
-e frame.time_epoch \
-e opcua.nodeid.string  \
-e  opcua.datavalue.SourceTimestamp > tmp.out && python ./opcua-ts_offset.py -i tmp.out -o 420000000.0 > tmp.out.off && head tmp.out.off && ./stats.sh -c 1 -f tmp.out.off
tcpdump: listening on enp2s0, link-type EN10MB (Ethernet), capture size 262144 bytes
1000 packets captured
1002 packets received by filter
0 packets dropped by kernel
250.0
363.0
358.0
351.0
348.0
339.0
354.0
393.0
361.0
355.0
min:    +1.660000e+02
max:    +6.260000e+02
pk-pk:  +4.600000e+02
mean:   +3.536918e+02
stddev: +4.887878e+01
count:   305
```

Congratulations! PTP network time-synchrnoization and OPUC-UA client-server applications can live happily ever after in a Time Synchronize Network (IEEE 801.2/TSN) world ... more to come ;-)

THE END.

## Additional Information
* [OPC Foundation](https://opcfoundation.org/about/opc-technologies/opc-ua/) - The official OPC Foundation group
* [OPC Unified Architecture - Wikipedia](https://en.wikipedia.org/wiki/OPC_Unified_Architecture)
* [open62541.org Tutorial](https://open62541.org/doc/0.2/tutorials.html)
* [PTP Wikipedia](https://en.wikipedia.org/wiki/Precision_Time_Protocol)
* [Starting PTP4L](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/6/html/deployment_guide/s1-starting_ptp4l)

## Appendix 
### Tshark '-TField' command-line (tshark -G list)
* [PTP v2 Filter](./tshark_ptp-filters_fields.md) 
* [OPC-UA Filter](./tshark_opcua-filters_fields.md)
