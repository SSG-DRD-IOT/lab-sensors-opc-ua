|   Description |   Field   |  Type  |  Categories  | BASE encoding |   Maskset |  Comments | 
|-------------- | ----------|--------|--------------|---------------|-----------|-----------| 
|   transportSpecific   | ptp.v2.transportspecific  | FT_UINT8   | ptp |    BASE_HEX     | 0xf0 |  |
|   V1 Compatibility    | ptp.v2.transportspecific.v1compatibility  | FT_BOOLEAN     | ptp |    8    | 0x10 |    |
|   802.1as conform | ptp.v2.transportspecific.802.1asconform   | FT_BOOLEAN     | ptp |    8    | 0x10 |    |
|   messageId   | ptp.v2.messageid  | FT_UINT8   | ptp |    BASE_HEX     | 0xf |     |
|   versionPTP  | ptp.v2.versionptp | FT_UINT8   | ptp |    BASE_DEC     | 0xf |     |
|   messageLength   | ptp.v2.messagelength  | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   subdomainNumber | ptp.v2.subdomainnumber    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   flags   | ptp.v2.flags  | FT_UINT16  | ptp |    BASE_HEX     | 0x0 |     |
|   PTP_ALTERNATE_MASTER    | ptp.v2.flags.alternatemaster  | FT_BOOLEAN     | ptp |    16   | 0x100 |   |
|   PTP_TWO_STEP    | ptp.v2.flags.twostep  | FT_BOOLEAN     | ptp |    16   | 0x200 |   |
|   PTP_UNICAST | ptp.v2.flags.unicast  | FT_BOOLEAN     | ptp |    16   | 0x400 |   |
|   PTP profile Specific 1  | ptp.v2.flags.specific1    | FT_BOOLEAN     | ptp |    16   | 0x2000 |      |
|   PTP profile Specific 2  | ptp.v2.flags.specific2    | FT_BOOLEAN     | ptp |    16   | 0x4000 |      |
|   PTP_SECURITY    | ptp.v2.flags.security | FT_BOOLEAN     | ptp |    16   | 0x8000 |      |
|   PTP_LI_61   | ptp.v2.flags.li61 | FT_BOOLEAN     | ptp |    16   | 0x1 |     |
|   PTP_LI_59   | ptp.v2.flags.li59 | FT_BOOLEAN     | ptp |    16   | 0x2 |     |
|   PTP_UTC_REASONABLE  | ptp.v2.flags.utcreasonable    | FT_BOOLEAN     | ptp |    16   | 0x4 |     |
|   PTP_TIMESCALE   | ptp.v2.flags.timescale    | FT_BOOLEAN     | ptp |    16   | 0x8 |     |
|   TIME_TRACEABLE  | ptp.v2.flags.timetraceable    | FT_BOOLEAN     | ptp |    16   | 0x10 |    |
|   FREQUENCY_TRACEABLE | ptp.v2.flags.frequencytraceable   | FT_BOOLEAN     | ptp |    16   | 0x20 |    |
|   correction  | ptp.v2.correction.ns  | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   correctionSubNs | ptp.v2.correction.subns   | FT_DOUBLE  | ptp |         | 0x0 |     |
|   ClockIdentity   | ptp.v2.clockidentity  | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   SourcePortID    | ptp.v2.sourceportid   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   sequenceId  | ptp.v2.sequenceid | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   control | ptp.v2.control    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   logMessagePeriod    | ptp.v2.logmessageperiod   | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   originTimestamp (seconds)   | ptp.v2.an.origintimestamp.seconds | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   originTimestamp (nanoseconds)   | ptp.v2.an.origintimestamp.nanoseconds | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   originCurrentUTCOffset  | ptp.v2.an.origincurrentutcoffset  | FT_INT16   | ptp |    BASE_DEC     | 0x0 |     |
|   TimeSource  | ptp.v2.timesource | FT_UINT8   | ptp |    BASE_HEX     | 0x0 |     |
|   localStepsRemoved   | ptp.v2.an.localstepsremoved   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   grandmasterClockIdentity    | ptp.v2.an.grandmasterclockidentity    | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   grandmasterClockClass   | ptp.v2.an.grandmasterclockclass   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   grandmasterClockAccuracy    | ptp.v2.an.grandmasterclockaccuracy    | FT_UINT8   | ptp |    BASE_HEX     | 0x0 |     |
|   grandmasterClockVariance    | ptp.v2.an.grandmasterclockvariance    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   priority1   | ptp.v2.an.priority1   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   priority2   | ptp.v2.an.priority2   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   tlvType | ptp.v2.an.tlvType | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   lengthField | ptp.v2.an.lengthField | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   organizationId  | ptp.v2.an.oe.organizationId   | FT_UINT24  | ptp |    BASE_HEX     | 0x0 |     |
|   organizationSubType | ptp.v2.an.oe.organizationSubType  | FT_UINT24  | ptp |    BASE_HEX     | 0x0 |     |
|   dataField   | ptp.v2.an.oe.dataField    | FT_BYTES   | ptp |         | 0x0 |     |
|   grandmasterID   | ptp.v2.an.oe.grandmasterID    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   grandmasterTimeInaccuracy (nanoseconds) | ptp.v2.an.oe.grandmasterTimeInaccuracy    | FT_UINT32  | ptp |    BASE_DEC     | 0x0 |     |
|   networkTimeInaccuracy (nanoseconds) | ptp.v2.an.oe.networkTimeInaccuracy    | FT_UINT32  | ptp |    BASE_DEC     | 0x0 |     |
|   reserved    | ptp.v2.an.oe.reserved | FT_UINT16  | ptp |    BASE_HEX     | 0x0 |     |
|   keyField    | ptp.v2.an.atoi.keyField   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   currentOffset   | ptp.v2.an.atoi.currentOffset  | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   jumpSeconds | ptp.v2.an.atoi.jumpSeconds    | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   timeOfNextJump  | ptp.v2.an.atoi.timeOfNextJump | FT_BYTES   | ptp |         | 0x0 |     |
|   displayName | ptp.v2.an.atoi.dislpayName    | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.an.atoi.dislpayName.length | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   PathSequence    | ptp.v2.an.pathsequence    | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   data    | ptp.v2.an.tlv.data    | FT_BYTES   | ptp |         | 0x0 |     |
|   originTimestamp (seconds)   | ptp.v2.sdr.origintimestamp.seconds    | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   originTimestamp (nanoseconds)   | ptp.v2.sdr.origintimestamp.nanoseconds    | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   preciseOriginTimestamp (seconds)    | ptp.v2.fu.preciseorigintimestamp.seconds  | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   preciseOriginTimestamp (nanoseconds)    | ptp.v2.fu.preciseorigintimestamp.nanoseconds  | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   receiveTimestamp (seconds)  | ptp.v2.dr.receivetimestamp.seconds    | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   receiveTimestamp (nanoseconds)  | ptp.v2.dr.receivetimestamp.nanoseconds    | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   requestingSourcePortIdentity    | ptp.v2.dr.requestingsourceportidentity    | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   requestingSourcePortId  | ptp.v2.dr.requestingsourceportid  | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   originTimestamp (seconds)   | ptp.v2.pdrq.origintimestamp.seconds   | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   originTimestamp (nanoseconds)   | ptp.v2.pdrq.origintimestamp.nanoseconds   | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   requestreceiptTimestamp (seconds)   | ptp.v2.pdrs.requestreceipttimestamp.seconds   | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   requestreceiptTimestamp (nanoseconds)   | ptp.v2.pdrs.requestreceipttimestamp.nanoseconds   | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   requestingSourcePortIdentity    | ptp.v2.pdrs.requestingportidentity    | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   requestingSourcePortId  | ptp.v2.pdrs.requestingsourceportid    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   responseOriginTimestamp (seconds)   | ptp.v2.pdfu.responseorigintimestamp.seconds   | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   responseOriginTimestamp (nanoseconds)   | ptp.v2.pdfu.responseorigintimestamp.nanoseconds   | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   requestingSourcePortIdentity    | ptp.v2.pdfu.requestingportidentity    | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   requestingSourcePortId  | ptp.v2.pdfu.requestingsourceportid    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   targetPortIdentity  | ptp.v2.sig.targetportidentity | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   targetPortId    | ptp.v2.sig.targetportid   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   tlvType | ptp.v2.sig.tlv.tlvType    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   lengthField | ptp.v2.sig.tlv.lengthField    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   data    | ptp.v2.sig.tlv.data   | FT_BYTES   | ptp |         | 0x0 |     |
|   messageType | ptp.v2.sig.tlv.messageType    | FT_UINT8   | ptp |    BASE_HEX     | 0xf0 |    |
|   logInterMessagePeriod   | ptp.v2.sig.tlv.logInterMessagePeriod  | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   period  | ptp.v2.sig.tlv.logInterMessagePeriod.period   | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   rate    | ptp.v2.sig.tlv.logInterMessagePeriod.rate | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   durationField   | ptp.v2.sig.tlv.durationField  | FT_UINT32  | ptp |    BASE_DEC     | 0x0 |     |
|   renewalInvited  | ptp.v2.sig.tlv.renewalInvited | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   targetPortIdentity  | ptp.v2.mm.targetportidentity  | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   targetPortId    | ptp.v2.mm.targetportid    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   startingBoundaryHops    | ptp.v2.mm.startingboundaryhops    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   boundaryHops    | ptp.v2.mm.boundaryhops    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   action  | ptp.v2.mm.action  | FT_UINT8   | ptp |    BASE_DEC     | 0xf |     |
|   tlvType | ptp.v2.mm.tlvType | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   lengthField | ptp.v2.mm.lengthField | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   managementId    | ptp.v2.mm.managementId    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   data    | ptp.v2.mm.data    | FT_BYTES   | ptp |         | 0x0 |     |
|   clockType   | ptp.v2.mm.clockType   | FT_UINT16  | ptp |    BASE_HEX     | 0x0 |     |
|   The node implements an ordinary clock   | ptp.v2.mm.clockType.OC    | FT_BOOLEAN     | ptp |    16   | 0x8000 |      |
|   The node implements a boundary clock    | ptp.v2.mm.clockType.BC    | FT_BOOLEAN     | ptp |    16   | 0x4000 |      |
|   The node implements a peer-to-peer transparent clock    | ptp.v2.mm.clockType.p2p_TC    | FT_BOOLEAN     | ptp |    16   | 0x2000 |      |
|   The node implements an end-to-end transparent clock | ptp.v2.mm.clockType.e2e_TC    | FT_BOOLEAN     | ptp |    16   | 0x1000 |      |
|   The node implements a management node   | ptp.v2.mm.clockType.MM    | FT_BOOLEAN     | ptp |    16   | 0x800 |   |
|   Reserved    | ptp.v2.mm.clockType.reserved  | FT_BOOLEAN     | ptp |    16   | 0x7ff |   |
|   physicalLayerProtocol   | ptp.v2.mm.physicalLayerProtocol   | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.physicalLayerProtocol.length    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   physical address length | ptp.v2.mm.physicalAddressLength   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   physical address    | ptp.v2.mm.physicalAddress | FT_BYTES   | ptp |         | 0x0 |     |
|   protocol address    | ptp.v2.mm.protocolAddress | FT_BYTES   | ptp |         | 0x0 |     |
|   network protocol    | ptp.v2.mm.networkProtocol | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   length  | ptp.v2.mm.protocolAddress.length  | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   manufacturer identity   | ptp.v2.mm.manufacturerIdentity    | FT_BYTES   | ptp |         | 0x0 |     |
|   reserved    | ptp.v2.mm.reserved    | FT_BYTES   | ptp |         | 0x0 |     |
|   product description | ptp.v2.mm.productDescription  | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.productDescription.length   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   revision data   | ptp.v2.mm.revisionData    | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.revisionData.length | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   user description    | ptp.v2.mm.userDescription | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.userDescription.length  | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   profileIdentity | ptp.v2.mm.profileIdentity | FT_BYTES   | ptp |         | 0x0 |     |
|   Pad | ptp.v2.mm.pad | FT_BYTES   | ptp |         | 0x0 |     |
|   initialization key  | ptp.v2.mm.initializationKey   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   number of fault records | ptp.v2.mm.numberOfFaultRecords    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   fault record length | ptp.v2.mm.faultRecordLength   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   severity code   | ptp.v2.mm.severityCode    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   faultName   | ptp.v2.mm.faultName   | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.faultName.length    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   faultValue  | ptp.v2.mm.faultValue  | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.faultValue.length   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   faultDescription    | ptp.v2.mm.faultDescription    | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.faultDescription.length | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Fault time (seconds)    | ptp.v2.mm.faultTime.seconds   | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   Fault time (nanoseconds)    | ptp.v2.mm.faultTime.nanoseconds   | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   current time (seconds)  | ptp.v2.mm.currentTime.seconds | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   current time (nanoseconds)  | ptp.v2.mm.currentTime.nanoseconds | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   Clock accuracy  | ptp.v2.mm.clockaccuracy   | FT_UINT8   | ptp |    BASE_HEX     | 0x0 |     |
|   priority1   | ptp.v2.mm.priority1   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   priority2   | ptp.v2.mm.priority2   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Slave only  | ptp.v2.mm.SlavOnly    | FT_BOOLEAN     | ptp |    8    | 0x2 |     |
|   Two step    | ptp.v2.mm.twoStep | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   number of ports | ptp.v2.mm.numberPorts | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   Clock class | ptp.v2.mm.clockclass  | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Clock variance  | ptp.v2.mm.clockvariance   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   Clock identity  | ptp.v2.mm.clockidentity   | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   domain number   | ptp.v2.mm.domainNumber    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   steps removed   | ptp.v2.mm.stepsRemoved    | FT_INT16   | ptp |    BASE_DEC     | 0x0 |     |
|   parent ClockIdentity    | ptp.v2.mm.parentclockidentity | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   parent SourcePortID | ptp.v2.mm.parentsourceportid  | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   parent stats    | ptp.v2.mm.parentstats | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   observedParentOffsetScaledLogVariance   | ptp.v2.mm.observedParentOffsetScaledLogVariance   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   observedParentClockPhaseChangeRate  | ptp.v2.mm.observedParentClockPhaseChangeRate  | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   Grandmaster priority1   | ptp.v2.mm.grandmasterPriority1    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Grandmaster priority2   | ptp.v2.mm.grandmasterPriority2    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Grandmaster clock class | ptp.v2.mm.grandmasterclockclass   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Grandmaster clock accuracy  | ptp.v2.mm.grandmasterclockaccuracy    | FT_UINT8   | ptp |    BASE_HEX     | 0x0 |     |
|   Grandmaster clock variance  | ptp.v2.mm.grandmasterclockvariance    | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   Grandmaster clock identity  | ptp.v2.mm.grandmasterclockidentity    | FT_UINT64  | ptp |    BASE_HEX     | 0x0 |     |
|   CurrentUTCOffset    | ptp.v2.mm.currentutcoffset    | FT_INT16   | ptp |    BASE_DEC     | 0x0 |     |
|   leap 61 | ptp.v2.mm.li61    | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   leap 59 | ptp.v2.mm.li59    | FT_BOOLEAN     | ptp |    8    | 0x2 |     |
|   CurrentUTCOffset valid  | ptp.v2.mm.CurrentUTCOffsetValid   | FT_BOOLEAN     | ptp |    8    | 0x4 |     |
|   PTP timescale   | ptp.v2.mm.ptptimescale    | FT_BOOLEAN     | ptp |    8    | 0x8 |     |
|   Time traceable  | ptp.v2.mm.timeTraceable   | FT_BOOLEAN     | ptp |    8    | 0x10 |    |
|   Frequency traceable | ptp.v2.mm.frequencyTraceable  | FT_BOOLEAN     | ptp |    8    | 0x20 |    |
|   TimeSource  | ptp.v2.mm.timesource  | FT_UINT8   | ptp |    BASE_HEX     | 0x0 |     |
|   correction  | ptp.v2.mm.offset.ns   | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   SubNs   | ptp.v2.mm.offset.subns    | FT_DOUBLE  | ptp |         | 0x0 |     |
|   ns  | ptp.v2.mm.pathDelay.ns    | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   SubNs   | ptp.v2.mm.pathDelay.subns | FT_DOUBLE  | ptp |         | 0x0 |     |
|   PortNumber  | ptp.v2.mm.PortNumber  | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   Port state  | ptp.v2.mm.portState   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   logMinDelayReqInterval  | ptp.v2.mm.logMinDelayReqInterval  | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   ns  | ptp.v2.mm.peerMeanPathDelay.ns    | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   SubNs   | ptp.v2.mm.peerMeanPathDelay.subns | FT_DOUBLE  | ptp |         | 0x0 |     |
|   logAnnounceInterval | ptp.v2.mm.logAnnounceInterval | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   announceReceiptTimeout  | ptp.v2.mm.announceReceiptTimeout  | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   logSyncInterval | ptp.v2.mm.logSyncInterval | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   Delay mechanism | ptp.v2.mm.delayMechanism  | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   logMinPdelayReqInterval | ptp.v2.mm.logMinPdelayReqInterval | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   versionNumber   | ptp.v2.mm.versionNumber   | FT_UINT8   | ptp |    BASE_DEC     | 0xf |     |
|   Primary domain number   | ptp.v2.mm.primaryDomain   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Faulty flag | ptp.v2.mm.faultyFlag  | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   managementErrorId   | ptp.v2.mm.managementErrorId   | FT_UINT16  | ptp |    BASE_DEC     | 0x0 |     |
|   Display data    | ptp.v2.mm.displayData | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.displayData.length  | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Enable unicast  | ptp.v2.mm.unicastEnable   | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   Path trace unicast  | ptp.v2.mm.pathTraceEnable | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   Key field   | ptp.v2.mm.keyField    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Display name    | ptp.v2.mm.displayName | FT_STRING  | ptp |         | 0x0 |     |
|   length  | ptp.v2.mm.displayName.length  | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Max key | ptp.v2.mm.maxKey  | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Current offset  | ptp.v2.mm.currentOffset   | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   Jump seconds    | ptp.v2.mm.jumpSeconds | FT_INT32   | ptp |    BASE_DEC     | 0x0 |     |
|   Time of next jump (seconds) | ptp.v2.mm.nextjumpSeconds | FT_UINT64  | ptp |    BASE_DEC     | 0x0 |     |
|   Number of alternate masters | ptp.v2.mm.numberOfAlternateMasters    | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   Alternate multicast sync interval   | ptp.v2.mm.AlternateMulticastSyncInterval  | FT_INT8    | ptp |    BASE_DEC     | 0x0 |     |
|   Transmit alternate multicast sync   | ptp.v2.mm.transmitAlternateMulticastSync  | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   SMPTE SubType   | ptp.v2.oe.smpte.SubType   | FT_UINT24  | ptp |    BASE_HEX     | 0x0 |     |
|   SMPTE Data  | ptp.v2.oe.smpte.data  | FT_NONE    | ptp |         | 0x0 |     |
|   defaultSystemFramerate  | ptp.v2.oe.smpte.defaultsystemframerate    | FT_BYTES   | ptp |         | 0x0 |     |
|   Numerator   | ptp.v2.oe.smpte.defaultsystemframerate.numerator  | FT_UINT32  | ptp |    BASE_DEC     | 0x0 |     |
|   Denominator | ptp.v2.oe.smpte.defaultsystemframerate.denominator    | FT_UINT32  | ptp |    BASE_DEC     | 0x0 |     |
|   masterLockingStatus | ptp.v2.oe.smpte.masterlockingstatus   | FT_UINT8   | ptp |    BASE_DEC     | 0x0 |     |
|   timeAdressFlags | ptp.v2.oe.smpte.timeadressflags   | FT_UINT8   | ptp |    BASE_HEX     | 0x0 |     |
|   Drop frame  | ptp.v2.oe.smpte.timeadressflags.drop  | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   Color frame identification  | ptp.v2.oe.smpte.timeadressflags.color | FT_BOOLEAN     | ptp |    8    | 0x2 |     |
|   currentLocalOffset  | ptp.v2.oe.smpte.currentlocaloffset    | FT_INT32   | ptp |    BASE_DEC     | 0x0 |    Offset in seconds of Local Time from grandmaster PTP time |
|   jumpSeconds | ptp.v2.oe.smpte.jumpseconds   | FT_INT32   | ptp |    BASE_DEC     | 0x0 |    Size of next discontinuity, in seconds, of Local Time |
|   timeOfNextJump  | ptp.v2.oe.smpte.timeofnextjump    | FT_UINT48  | ptp |    BASE_DEC     | 0x0 |    Value of the seconds portion at the time that the next discontinuity of the currentLocalOffset will occur |
|   timeOfNextJam   | ptp.v2.oe.smpte.timeofnextjam | FT_UINT48  | ptp |    BASE_DEC     | 0x0 |    Value of the seconds portion to the next scheduled Daily Jam |
|   timeOfPreviousJam   | ptp.v2.oe.smpte.timeofpreviousjam | FT_UINT48  | ptp |    BASE_DEC     | 0x0 |    Value of the seconds portion of the previous Daily Jam |
|   previousJamLocalOffset  | ptp.v2.oe.smpte.previousjamlocaloffset    | FT_INT32   | ptp |    BASE_DEC     | 0x0 |    Value of current LocalOffset at the time of the previous Daily Jam |
|   daylightSaving  | ptp.v2.oe.smpte.daylightsaving    | FT_UINT8   | ptp |    BASE_HEX     | 0x0 |     |
|   Current | ptp.v2.oe.smpte.daylightsaving.current    | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   Next    | ptp.v2.oe.smpte.daylightsaving.next   | FT_BOOLEAN     | ptp |    8    | 0x2 |     |
|   Previous    | ptp.v2.oe.smpte.daylightsaving.previous   | FT_BOOLEAN     | ptp |    8    | 0x4 |     |
|   leapSecondJump  | ptp.v2.oe.smpte.leapsecondjump    | FT_UINT8   | ptp |    BASE_HEX     | 0x0 |     |
|   Change in number    | ptp.v2.oe.smpte.leaspsecondjump   | FT_BOOLEAN     | ptp |    8    | 0x1 |     |
|   Expert Info | ptp.v2.msg_len_too_large  | FT_NONE    | ptp |         | 0x0 |    Message length goes past the end of the packet |
|   Expert Info | ptp.v2.msg_len_too_small  | FT_NONE    | ptp |         | 0x0 |    Message length too short to include the message length field |
