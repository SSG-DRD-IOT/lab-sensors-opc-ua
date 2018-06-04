#  OPC-UA client-server application runtime tunning 

This lab will guide you through the synchonizing Network and Real-Time Clock domains for OPC UA application to illustrate multiple client-server communications accross a network.

** PTP time-synchronization ** 
The Precision Time Protocol (PTP) is a protocol used to synchronize clocks throughout a computer network. On a local area network, it achieves clock accuracy in the sub-microsecond range, making it suitable for measurement and control systems.
https://www.nist.gov/el/intelligent-systems-division-73500/ieee-1588 

 IEEE standard 1588 Precision Time Protocol (PTP) support is provide in every linux distribution including http://manpages.ubuntu.com/manpages/bionic/man8/ptp4l.8.html 
```shell
$ sudo apt-get install ethtool linuxptp tshark
```

At start we need to discover what time-synchonization feature our machine Network Interface Controller(NIC) are capable of : 
```shell
$ sudo ethtool -T enp2s0
$ sudo ethtool -T enp3s0
```
For UP2, unfortunatly RT8186G NIC doesn't provide any time-synchonization HW-features, unlike most intel NIC : i210, i211, e1000, i350,... (.e.g. expose /dev/ptp0 device providing L2/UPDv4/UPDv6 HW-offload of Announce/Sync/Follow_Up/Delay_Req/Delay_Resp/... messages communication, extenal HW-timestamping from an Free Running Timer, Pulse-Per-Second on External Pins,...).

So software PTP time-synchronization is our only option here.
```shell
sudo ptp4l -i enp2s0 -f ptp4l_1.conf -m -s
```
_TBD_

```shell
phc2sys -c enp2s0 -s CLOCK_REALTIME -w
phc2sys -s enp2s0 -w
phc2sys -a -r -s enp2s0 -w
service phc2sys restart
```
_TBD_

```shell
sudo pmc -u -b 0 'GET TIME_STATUS_NP'
sudo pmc -u -b 0 'GET CURRENT_DATA_SET'
```
_TBD_

```shell
sudo tcpdump -i enp2s0 -w tmp.pcap -j adapter_unsynced -tt --time-stamp-precision=nano port 319 or port 320 -c 10000 && tshark -r tmp.pcap -t e -E separator=, -E header=n -R -Tfields -e frame.number -e frame.time_epoch -e ptp.v2.an.origincurrentutcoffset > tmp.out && ./stat.sh -c 2 -i tmp.out
```
Congratulations! You just made your all boards in time-sync with the master clock.

**Open Platform Communications - Unified Architecture**

Here our objectives are touch-base some concepts of network timing determinism that all Industrial Protocol MUST support.

A given Industrial network usually instanciate multiple OPC-UA client-server:
* server: contains an instance of server node that read RTC time-stamp object nodes on every Read Request. 
* client: Queries one or several the server node for timestamp object nodes to be able to estimate the RTC time between client-server accross PTP synchronized network layers.

In OPC UA, servers may provide information as object nodes and variable nodes.  Object nodes can contain other object and variables nodes known as children. Variable nodes can contain other variable nodes.

opc-ua-multi-server and opc-ua-multi-client implementation are split in a set of small steps to illustrate Network PTP, System and Realtime (RTC) clock-domains independently. The complete files are also provided for reference as [opc-ua-multi-server.c](./opc-ua-multi-server.c) and [opc-ua-multi-client.c](./opc-ua-multi-client.c). 

The example is an extension of the tutorials and source from [open62541](https://github.com/open62541/open62541) [Tutorials](https://open62541.org/doc/0.2/tutorials.html) and distributed under the same terms: Public Domain (Creative Commons CC0).

A working [Makefile](./Makefile) is also provided.

IMPORTANT!! This example is based of sligthly older library open62541 release 0.2 (commit: 24604543cd071ad04b6a19ad07b8456cd0c91340). 
To avoid compile errors, please make sure you clone & checkout exacly this commit or link with prebuilt static libraries are availables under this repo.

# Multiple OPC-UA Server 

## Real-Time Clock device Argument

Similarly with previous OPC-UA process that we can interrupt with Ctrl-C. 
but now we add the capability to select Real-Time clock device (e.g /dev/rtc0) to connect server onto.
The code would be:
_TBD_

```c
_TBD_
```
In this example you can use the Makefile to handle compilation :
```shell
$ make
```

_TBD_


```
# Putting it all together

Open a terminal and run the server:
```shell
$ ./opc-ua-multiple-server -d /dev/rtc0
```

Now open another terminal and run the client:
```shell
$ ./opc-ua-multiple-client opc.tcp://<server#0>:4840 -d <cycle-time in us .ex 250=250us> -l <timesptamp logfile>
```
# Analyzing the OPC-UA traffic latency

_TBD_
```shell
tshark -r tmp.pcap -t e -2 -R opcua.servicenodeid.numeric==634 -E separator=, -E header=n -Tfields -e frame.number -e frame.time_epoch -e opcua.nodeid.string  -e  opcua.datavalue.SourceTimestamp > tmp.out && python ./offset.py -i tmp.out > tmp.out.off && head tmp.out.off && ./stats.sh -c 1 -f tmp.out.off
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
* [PTP v2 Filter](./tshark_opcua-filters_fields.md) 
* [OPC-UA Filter](./tshark_ptp-filters_fields.md)