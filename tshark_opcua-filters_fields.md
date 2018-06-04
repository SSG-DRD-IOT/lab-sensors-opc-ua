|   Description |   Field   |  Type  |  Categories  | BASE encoding |   Maskset |  Comments | 
|-------------- | ----------|--------|--------------|---------------|-----------|-----------| 
|   Message Type     | opcua.transport.type  | FT_STRING     | opcua |       | 0x0 |     |
|   Chunk Type   | opcua.transport.chunk     | FT_STRING     | opcua |       | 0x0 |     |
|   Message Size     | opcua.transport.size  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Version  | opcua.transport.ver   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   SecureChannelId  | opcua.transport.scid  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ReceiveBufferSize    | opcua.transport.rbs   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   SendBufferSize   | opcua.transport.sbs   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxMessageSize   | opcua.transport.mms   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxChunkCount    | opcua.transport.mcc   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   EndPointUrl  | opcua.transport.endpoint  | FT_STRING     | opcua |       | 0x0 |     |
|   Error    | opcua.transport.error     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   Reason   | opcua.transport.reason    | FT_STRING     | opcua |       | 0x0 |     |
|   SecurityPolicyUri    | opcua.security.spu    | FT_STRING     | opcua |       | 0x0 |     |
|   SenderCertificate    | opcua.security.scert  | FT_BYTES  | opcua |       | 0x0 |     |
|   ReceiverCertificateThumbprint    | opcua.security.rcthumb    | FT_BYTES  | opcua |       | 0x0 |     |
|   SequenceNumber   | opcua.security.seq    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RequestId    | opcua.security.rqid   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Security Token Id    | opcua.security.tokenid    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   NodeId EncodingMask  | opcua.servicenodeid.encodingmask  | FT_UINT8  | opcua |  BASE_HEX     | 0x0 |     |
|   NodeId Namespace Index   | opcua.servicenodeid.nsid  | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   NodeId Identifier Numeric    | opcua.servicenodeid.numeric   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   EncodingMask     | opcua.diag.mask   | FT_UINT8  | opcua |  BASE_HEX     | 0x0 |     |
|   has symbolic id  | opcua.diag.has_symbolic_id    | FT_BOOLEAN    | opcua |  8    | 0x1 |     |
|   has namespace    | opcua.diag.has_namespace  | FT_BOOLEAN    | opcua |  8    | 0x2 |     |
|   has localizedtext    | opcua.diag.has_localizedtext  | FT_BOOLEAN    | opcua |  8    | 0x4 |     |
|   has locale   | opcua.diag.has_locale     | FT_BOOLEAN    | opcua |  8    | 0x8 |     |
|   has additional info  | opcua.diag.has_additional_info    | FT_BOOLEAN    | opcua |  8    | 0x10 |    |
|   has inner statuscode     | opcua.diag.has_inner_statuscode   | FT_BOOLEAN    | opcua |  8    | 0x20 |    |
|   has inner diagnostic info    | opcua.diag.has_inner_diagnostic_code  | FT_BOOLEAN    | opcua |  8    | 0x40 |    |
|   EncodingMask     | opcua.loctext.mask    | FT_UINT8  | opcua |  BASE_HEX     | 0x0 |     |
|   has locale information   | opcua.loctext.has_locale_information  | FT_BOOLEAN    | opcua |  8    | 0x1 |     |
|   has text     | opcua.loctext.has_text    | FT_BOOLEAN    | opcua |  8    | 0x2 |     |
|   EncodingMask     | opcua.nodeid.encodingmask     | FT_UINT8  | opcua |  BASE_HEX     | 0xf |     |
|   Namespace Index  | opcua.nodeid.nsindex  | FT_UINT16     | opcua |  BASE_DEC     | 0x0 |     |
|   Identifier Numeric   | opcua.nodeid.numeric  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Identifier String    | opcua.nodeid.string   | FT_STRING     | opcua |       | 0x0 |     |
|   Identifier Guid  | opcua.nodeid.guid     | FT_GUID   | opcua |       | 0x0 |     |
|   Identifier ByteString    | opcua.nodeid.bytestring   | FT_BYTES  | opcua |       | 0x0 |     |
|   EncodingMask     | opcua.expandednodeid.mask     | FT_UINT8  | opcua |  BASE_HEX     | 0x0 |     |
|   has namespace uri    | opcua.expandednodeid.has_namespace_uri    | FT_BOOLEAN    | opcua |  8    | 0x80 |    |
|   has server index     | opcua.expandednodeid.has_server_index     | FT_BOOLEAN    | opcua |  8    | 0x40 |    |
|   Locale   | opcua.loctext.Locale  | FT_STRING     | opcua |       | 0x0 |     |
|   Text     | opcua.loctext.Text    | FT_STRING     | opcua |       | 0x0 |     |
|   Id   | opcua.qualname.Id     | FT_UINT16     | opcua |  BASE_DEC     | 0x0 |     |
|   Name     | opcua.qualname.Name   | FT_STRING     | opcua |       | 0x0 |     |
|   EncodingMask     | opcua.datavalue.mask  | FT_UINT8  | opcua |  BASE_HEX     | 0x0 |     |
|   has value    | opcua.datavalue.has_value     | FT_BOOLEAN    | opcua |  8    | 0x1 |     |
|   has statuscode   | opcua.datavalue.has_statuscode    | FT_BOOLEAN    | opcua |  8    | 0x2 |     |
|   has source timestamp     | opcua.datavalue.has_source_timestamp  | FT_BOOLEAN    | opcua |  8    | 0x4 |     |
|   has server timestamp     | opcua.datavalue.has_server_timestamp  | FT_BOOLEAN    | opcua |  8    | 0x8 |     |
|   has source picoseconds   | opcua.datavalue.has_source_picoseconds    | FT_BOOLEAN    | opcua |  8    | 0x10 |    |
|   has server picoseconds   | opcua.datavalue.has_server_picoseconds    | FT_BOOLEAN    | opcua |  8    | 0x20 |    |
|   Variant Type     | opcua.variant.has_value   | FT_UINT8  | opcua |  BASE_HEX     | 0x0 |     |
|   SourceTimestamp  | opcua.datavalue.SourceTimestamp   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   SourcePicoseconds    | opcua.datavalue.SourcePicoseconds     | FT_UINT16     | opcua |  BASE_DEC     | 0x0 |     |
|   ServerTimestamp  | opcua.datavalue.ServerTimestamp   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   ServerPicoseconds    | opcua.datavalue.ServerPicoseconds     | FT_UINT16     | opcua |  BASE_DEC     | 0x0 |     |
|   SymbolicId   | opcua.diag.SymbolicId     | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   Namespace    | opcua.diag.Namespace  | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   LocalizedText    | opcua.diag.LocalizedText  | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   Locale   | opcua.diag.Locale     | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   AdditionalInfo   | opcua.diag.AdditionalInfo     | FT_STRING     | opcua |       | 0x0 |     |
|   InnerStatusCode  | opcua.diag.InnerStatusCode    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   EncodingMask     | opcua.extobj.mask     | FT_UINT8  | opcua |  BASE_HEX     | 0x0 |     |
|   has binary body  | opcua.extobj.has_binary_body  | FT_BOOLEAN    | opcua |  8    | 0x1 |     |
|   has xml body     | opcua.extobj.has_xml_body     | FT_BOOLEAN    | opcua |  8    | 0x2 |     |
|   ArraySize    | opcua.variant.ArraySize   | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   ServerIndex  | opcua.expandednodeid.ServerIndex  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   StructureChanged     | opcua.statuscode.structureChanged     | FT_BOOLEAN    | opcua |  16   | 0x8000 |      |
|   SemanticsChanged     | opcua.statuscode.semanticsChanged     | FT_BOOLEAN    | opcua |  16   | 0x4000 |      |
|   Overflow     | opcua.statuscode.overflow     | FT_BOOLEAN    | opcua |  16   | 0x80 |    |
|   HistorianBit: Partial    | opcua.statuscode.historian.partial    | FT_BOOLEAN    | opcua |  16   | 0x4 |     |
|   HistorianBit: ExtraData  | opcua.statuscode.historian.extraData  | FT_BOOLEAN    | opcua |  16   | 0x8 |     |
|   HistorianBit: MultiValue     | opcua.statuscode.historian.multiValue     | FT_BOOLEAN    | opcua |  16   | 0x10 |    |
|   InfoType     | opcua.statuscode.infoType     | FT_UINT16     | opcua |  BASE_HEX     | 0xc00 |   |
|   Limit    | opcua.statuscode.limit    | FT_UINT16     | opcua |  BASE_HEX     | 0x300 |   |
|   Historian    | opcua.statuscode.historian    | FT_UINT16     | opcua |  BASE_HEX     | 0x3 |     |
|   Return Diagnostics   | opcua.returndiag  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   ServiceLevel / SymbolicId    | opcua.returndiag.servicelevel.symbolicid  | FT_BOOLEAN    | opcua |  16   | 0x1 |     |
|   ServiceLevel / LocalizedText     | opcua.returndiag.servicelevel.localizedtext   | FT_BOOLEAN    | opcua |  16   | 0x2 |     |
|   ServiceLevel / AdditionalInfo    | opcua.returndiag.servicelevel.additionalinfo  | FT_BOOLEAN    | opcua |  16   | 0x4 |     |
|   ServiceLevel / Inner StatusCode  | opcua.returndiag.servicelevel.innerstatuscode     | FT_BOOLEAN    | opcua |  16   | 0x8 |     |
|   ServiceLevel / Inner Diagnostics     | opcua.returndiag.servicelevel.innerdiagnostics    | FT_BOOLEAN    | opcua |  16   | 0x10 |    |
|   OperationLevel / SymbolicId  | opcua.returndiag.operationlevel.symbolicid    | FT_BOOLEAN    | opcua |  16   | 0x20 |    |
|   OperationLevel / LocalizedText   | opcua.returndiag.operationlevel.localizedtext     | FT_BOOLEAN    | opcua |  16   | 0x40 |    |
|   OperationLevel / AdditionalInfo  | opcua.returndiag.operationlevel.additionalinfo    | FT_BOOLEAN    | opcua |  16   | 0x80 |    |
|   OperationLevel / Inner StatusCode    | opcua.returndiag.operationlevel.innerstatuscode   | FT_BOOLEAN    | opcua |  16   | 0x100 |   |
|   OperationLevel / Inner Diagnostics   | opcua.returndiag.operationlevel.innerdiagnostics  | FT_BOOLEAN    | opcua |  16   | 0x200 |   |
|   Expert Info  | opcua.array.length    | FT_NONE   | opcua |       | 0x0 |    Max array length exceeded |
|   NodeIdType   | opcua.NodeIdType  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   NamingRuleType   | opcua.NamingRuleType  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   OpenFileMode     | opcua.OpenFileMode    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   TrustListMasks   | opcua.TrustListMasks  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   IdType   | opcua.IdType  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   NodeClass    | opcua.NodeClass   | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   ApplicationType  | opcua.ApplicationType     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   MessageSecurityMode  | opcua.MessageSecurityMode     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   UserTokenType    | opcua.UserTokenType   | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   SecurityTokenRequestType     | opcua.SecurityTokenRequestType    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   NodeAttributesMask   | opcua.NodeAttributesMask  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   AttributeWriteMask   | opcua.AttributeWriteMask  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   BrowseDirection  | opcua.BrowseDirection     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   BrowseResultMask     | opcua.BrowseResultMask    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   ComplianceLevel  | opcua.ComplianceLevel     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   FilterOperator   | opcua.FilterOperator  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   TimestampsToReturn   | opcua.TimestampsToReturn  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   HistoryUpdateType    | opcua.HistoryUpdateType   | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   PerformUpdateType    | opcua.PerformUpdateType   | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   MonitoringMode   | opcua.MonitoringMode  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   DataChangeTrigger    | opcua.DataChangeTrigger   | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   DeadbandType     | opcua.DeadbandType    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   EnumeratedTestType   | opcua.EnumeratedTestType  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   RedundancySupport    | opcua.RedundancySupport   | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   ServerState  | opcua.ServerState     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   ModelChangeStructureVerbMask     | opcua.ModelChangeStructureVerbMask    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   AxisScaleEnumeration     | opcua.AxisScaleEnumeration    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   ExceptionDeviationFormat     | opcua.ExceptionDeviationFormat    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   AttributeId  | opcua.AttributeId     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   AccessLevel  | opcua.AccessLevel     | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   ActualSessionTimeout     | opcua.ActualSessionTimeout    | FT_DOUBLE     | opcua |       | 0x0 |     |
|   AddResults   | opcua.AddResults  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   Algorithm    | opcua.Algorithm   | FT_STRING     | opcua |       | 0x0 |     |
|   Alias    | opcua.Alias   | FT_STRING     | opcua |       | 0x0 |     |
|   AnnotationTime   | opcua.AnnotationTime  | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   ApplicationUri   | opcua.ApplicationUri  | FT_STRING     | opcua |       | 0x0 |     |
|   ArrayDimensions  | opcua.ArrayDimensions     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   AuditEntryId     | opcua.AuditEntryId    | FT_STRING     | opcua |       | 0x0 |     |
|   AuthenticationMechanism  | opcua.AuthenticationMechanism     | FT_STRING     | opcua |       | 0x0 |     |
|   AvailableSequenceNumbers     | opcua.AvailableSequenceNumbers    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   AxisSteps    | opcua.AxisSteps   | FT_DOUBLE     | opcua |       | 0x0 |     |
|   Boolean  | opcua.Boolean     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Booleans     | opcua.Booleans    | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   BuildDate    | opcua.BuildDate   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   BuildNumber  | opcua.BuildNumber     | FT_STRING     | opcua |       | 0x0 |     |
|   Byte     | opcua.Byte    | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   ByteString   | opcua.ByteString  | FT_BYTES  | opcua |       | 0x0 |     |
|   ByteStrings  | opcua.ByteStrings     | FT_BYTES  | opcua |       | 0x0 |     |
|   CancelCount  | opcua.CancelCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CertificateData  | opcua.CertificateData     | FT_BYTES  | opcua |       | 0x0 |     |
|   ChannelId    | opcua.ChannelId   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ChannelLifetime  | opcua.ChannelLifetime     | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   ClientCertificate    | opcua.ClientCertificate   | FT_BYTES  | opcua |       | 0x0 |     |
|   ClientConnectionTime     | opcua.ClientConnectionTime    | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   ClientHandle     | opcua.ClientHandle    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ClientLastContactTime    | opcua.ClientLastContactTime   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   ClientNonce  | opcua.ClientNonce     | FT_BYTES  | opcua |       | 0x0 |     |
|   ClientProtocolVersion    | opcua.ClientProtocolVersion   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ClientUserIdHistory  | opcua.ClientUserIdHistory     | FT_STRING     | opcua |       | 0x0 |     |
|   ClientUserIdOfSession    | opcua.ClientUserIdOfSession   | FT_STRING     | opcua |       | 0x0 |     |
|   ComplianceDate   | opcua.ComplianceDate  | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   ComplianceTool   | opcua.ComplianceTool  | FT_STRING     | opcua |       | 0x0 |     |
|   ConfigurationResults     | opcua.ConfigurationResults    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   ContainsNoLoops  | opcua.ContainsNoLoops     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   ContinuationPoint    | opcua.ContinuationPoint   | FT_BYTES  | opcua |       | 0x0 |     |
|   ContinuationPoints   | opcua.ContinuationPoints  | FT_BYTES  | opcua |       | 0x0 |     |
|   CreateClientName     | opcua.CreateClientName    | FT_STRING     | opcua |       | 0x0 |     |
|   CreatedAt    | opcua.CreatedAt   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   CumulatedSessionCount    | opcua.CumulatedSessionCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CumulatedSubscriptionCount   | opcua.CumulatedSubscriptionCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CurrentKeepAliveCount    | opcua.CurrentKeepAliveCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CurrentLifetimeCount     | opcua.CurrentLifetimeCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CurrentMonitoredItemsCount   | opcua.CurrentMonitoredItemsCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CurrentPublishRequestsInQueue    | opcua.CurrentPublishRequestsInQueue   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CurrentSessionCount  | opcua.CurrentSessionCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CurrentSubscriptionCount     | opcua.CurrentSubscriptionCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CurrentSubscriptionsCount    | opcua.CurrentSubscriptionsCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   CurrentTime  | opcua.CurrentTime     | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   DataChangeNotificationsCount     | opcua.DataChangeNotificationsCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   DataStatusCodes  | opcua.DataStatusCodes     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   DateTime     | opcua.DateTime    | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   DateTimes    | opcua.DateTimes   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   DaylightSavingInOffset   | opcua.DaylightSavingInOffset  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   DeadbandValue    | opcua.DeadbandValue   | FT_DOUBLE     | opcua |       | 0x0 |     |
|   DeleteBidirectional  | opcua.DeleteBidirectional     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   DeleteSubscriptions  | opcua.DeleteSubscriptions     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   DeleteTargetReferences   | opcua.DeleteTargetReferences  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   DisableCount     | opcua.DisableCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   DisabledMonitoredItemCount   | opcua.DisabledMonitoredItemCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   DiscardOldest    | opcua.DiscardOldest   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   DiscardedMessageCount    | opcua.DiscardedMessageCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   DiscoveryProfileUri  | opcua.DiscoveryProfileUri     | FT_STRING     | opcua |       | 0x0 |     |
|   DiscoveryUrl     | opcua.DiscoveryUrl    | FT_STRING     | opcua |       | 0x0 |     |
|   DiscoveryUrls    | opcua.DiscoveryUrls   | FT_STRING     | opcua |       | 0x0 |     |
|   Double   | opcua.Double  | FT_DOUBLE     | opcua |       | 0x0 |     |
|   Doubles  | opcua.Doubles     | FT_DOUBLE     | opcua |       | 0x0 |     |
|   EnableCount  | opcua.EnableCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Encoding     | opcua.Encoding    | FT_STRING     | opcua |       | 0x0 |     |
|   EncryptionAlgorithm  | opcua.EncryptionAlgorithm     | FT_STRING     | opcua |       | 0x0 |     |
|   EndTime  | opcua.EndTime     | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   EndpointUrl  | opcua.EndpointUrl     | FT_STRING     | opcua |       | 0x0 |     |
|   EndpointUrlList  | opcua.EndpointUrlList     | FT_STRING     | opcua |       | 0x0 |     |
|   ErrorCount   | opcua.ErrorCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   EventIds     | opcua.EventIds    | FT_BYTES  | opcua |       | 0x0 |     |
|   EventNotificationsCount  | opcua.EventNotificationsCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   EventNotifier    | opcua.EventNotifier   | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   EventQueueOverFlowCount  | opcua.EventQueueOverFlowCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Executable   | opcua.Executable  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Float    | opcua.Float   | FT_FLOAT  | opcua |       | 0x0 |     |
|   Floats   | opcua.Floats  | FT_FLOAT  | opcua |       | 0x0 |     |
|   GatewayServerUri     | opcua.GatewayServerUri    | FT_STRING     | opcua |       | 0x0 |     |
|   Guid     | opcua.Guid    | FT_GUID   | opcua |       | 0x0 |     |
|   Guids    | opcua.Guids   | FT_GUID   | opcua |       | 0x0 |     |
|   High     | opcua.High    | FT_DOUBLE     | opcua |       | 0x0 |     |
|   Historizing  | opcua.Historizing     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Imaginary    | opcua.Imaginary   | FT_DOUBLE     | opcua |       | 0x0 |     |
|   IncludeSubTypes  | opcua.IncludeSubTypes     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   IncludeSubtypes  | opcua.IncludeSubtypes     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Index    | opcua.Index   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   IndexRange   | opcua.IndexRange  | FT_STRING     | opcua |       | 0x0 |     |
|   InputArgumentResults     | opcua.InputArgumentResults    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   Int16    | opcua.Int16   | FT_INT16  | opcua |  BASE_DEC     | 0x0 |     |
|   Int16s   | opcua.Int16s  | FT_INT16  | opcua |  BASE_DEC     | 0x0 |     |
|   Int32    | opcua.Int32   | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   Int32s   | opcua.Int32s  | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   Int64    | opcua.Int64   | FT_INT64  | opcua |  BASE_DEC     | 0x0 |     |
|   Int64s   | opcua.Int64s  | FT_INT64  | opcua |  BASE_DEC     | 0x0 |     |
|   InvocationCreationTime   | opcua.InvocationCreationTime  | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   IsAbstract   | opcua.IsAbstract  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   IsDeleteModified     | opcua.IsDeleteModified    | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   IsForward    | opcua.IsForward   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   IsInverse    | opcua.IsInverse   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   IsOnline     | opcua.IsOnline    | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   IsReadModified   | opcua.IsReadModified  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   IssueDate    | opcua.IssueDate   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   IssuedBy     | opcua.IssuedBy    | FT_STRING     | opcua |       | 0x0 |     |
|   IssuedTokenType  | opcua.IssuedTokenType     | FT_STRING     | opcua |       | 0x0 |     |
|   IssuerCertificates   | opcua.IssuerCertificates  | FT_BYTES  | opcua |       | 0x0 |     |
|   IssuerCrls   | opcua.IssuerCrls  | FT_BYTES  | opcua |       | 0x0 |     |
|   IssuerEndpointUrl    | opcua.IssuerEndpointUrl   | FT_STRING     | opcua |       | 0x0 |     |
|   Iteration    | opcua.Iteration   | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   LastCounterResetTime     | opcua.LastCounterResetTime    | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   LastMethodCall   | opcua.LastMethodCall  | FT_STRING     | opcua |       | 0x0 |     |
|   LastMethodCallTime   | opcua.LastMethodCallTime  | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   LastTransitionTime   | opcua.LastTransitionTime  | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   LatePublishRequestCount  | opcua.LatePublishRequestCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   LinksToAdd   | opcua.LinksToAdd  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   LinksToRemove    | opcua.LinksToRemove   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   LocaleIds    | opcua.LocaleIds   | FT_STRING     | opcua |       | 0x0 |     |
|   Low  | opcua.Low     | FT_DOUBLE     | opcua |       | 0x0 |     |
|   ManufacturerName     | opcua.ManufacturerName    | FT_STRING     | opcua |       | 0x0 |     |
|   MaxAge   | opcua.MaxAge  | FT_DOUBLE     | opcua |       | 0x0 |     |
|   MaxArrayLength   | opcua.MaxArrayLength  | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   MaxBufferSize    | opcua.MaxBufferSize   | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   MaxByteStringLength  | opcua.MaxByteStringLength     | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   MaxDataSetsToReturn  | opcua.MaxDataSetsToReturn     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxKeepAliveCount    | opcua.MaxKeepAliveCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxLifetimeCount     | opcua.MaxLifetimeCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxMessageSize   | opcua.MaxMessageSize  | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   MaxMonitoredItemCount    | opcua.MaxMonitoredItemCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxNotificationsPerPublish   | opcua.MaxNotificationsPerPublish  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxRecordsToReturn   | opcua.MaxRecordsToReturn  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxReferencesToReturn    | opcua.MaxReferencesToReturn   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxRequestMessageSize    | opcua.MaxRequestMessageSize   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxResponseMessageSize   | opcua.MaxResponseMessageSize  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MaxStringLength  | opcua.MaxStringLength     | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   MdnsServerName   | opcua.MdnsServerName  | FT_STRING     | opcua |       | 0x0 |     |
|   Message  | opcua.Message     | FT_STRING     | opcua |       | 0x0 |     |
|   MinimumSamplingInterval  | opcua.MinimumSamplingInterval     | FT_DOUBLE     | opcua |       | 0x0 |     |
|   ModificationTime     | opcua.ModificationTime    | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   ModifyCount  | opcua.ModifyCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MonitoredItemCount   | opcua.MonitoredItemCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MonitoredItemId  | opcua.MonitoredItemId     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MonitoredItemIds     | opcua.MonitoredItemIds    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MonitoringQueueOverflowCount     | opcua.MonitoringQueueOverflowCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   MoreNotifications    | opcua.MoreNotifications   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Name     | opcua.Name    | FT_STRING     | opcua |       | 0x0 |     |
|   NamespaceUri     | opcua.NamespaceUri    | FT_STRING     | opcua |       | 0x0 |     |
|   NextSequenceNumber   | opcua.NextSequenceNumber  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   NodeClassMask    | opcua.NodeClassMask   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   NotificationsCount   | opcua.NotificationsCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   NumValuesPerNode     | opcua.NumValuesPerNode    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Offset   | opcua.Offset  | FT_INT16  | opcua |  BASE_DEC     | 0x0 |     |
|   OperandStatusCodes   | opcua.OperandStatusCodes  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   OperationResults     | opcua.OperationResults    | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   OperationTimeout     | opcua.OperationTimeout    | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   OrganizationUri  | opcua.OrganizationUri     | FT_STRING     | opcua |       | 0x0 |     |
|   Password     | opcua.Password    | FT_BYTES  | opcua |       | 0x0 |     |
|   PercentDataBad   | opcua.PercentDataBad  | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   PercentDataGood  | opcua.PercentDataGood     | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   PolicyId     | opcua.PolicyId    | FT_STRING     | opcua |       | 0x0 |     |
|   Priority     | opcua.Priority    | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   ProcessingInterval   | opcua.ProcessingInterval  | FT_DOUBLE     | opcua |       | 0x0 |     |
|   ProductName  | opcua.ProductName     | FT_STRING     | opcua |       | 0x0 |     |
|   ProductUri   | opcua.ProductUri  | FT_STRING     | opcua |       | 0x0 |     |
|   ProfileId    | opcua.ProfileId   | FT_STRING     | opcua |       | 0x0 |     |
|   ProfileUris  | opcua.ProfileUris     | FT_STRING     | opcua |       | 0x0 |     |
|   PublishRequestCount  | opcua.PublishRequestCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   PublishTime  | opcua.PublishTime     | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   PublishingEnabled    | opcua.PublishingEnabled   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   PublishingInterval   | opcua.PublishingInterval  | FT_DOUBLE     | opcua |       | 0x0 |     |
|   PublishingIntervalCount  | opcua.PublishingIntervalCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   QueueSize    | opcua.QueueSize   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Real     | opcua.Real    | FT_DOUBLE     | opcua |       | 0x0 |     |
|   RecordId     | opcua.RecordId    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RejectedRequestsCount    | opcua.RejectedRequestsCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RejectedSessionCount     | opcua.RejectedSessionCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ReleaseContinuationPoint     | opcua.ReleaseContinuationPoint    | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   ReleaseContinuationPoints    | opcua.ReleaseContinuationPoints   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   RemainingPathIndex   | opcua.RemainingPathIndex  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RemoveResults    | opcua.RemoveResults   | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   RepublishMessageCount    | opcua.RepublishMessageCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RepublishMessageRequestCount     | opcua.RepublishMessageRequestCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RepublishRequestCount    | opcua.RepublishRequestCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ReqTimes     | opcua.ReqTimes    | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   RequestHandle    | opcua.RequestHandle   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RequestedLifetime    | opcua.RequestedLifetime   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RequestedLifetimeCount   | opcua.RequestedLifetimeCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RequestedMaxKeepAliveCount   | opcua.RequestedMaxKeepAliveCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RequestedMaxReferencesPerNode    | opcua.RequestedMaxReferencesPerNode   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RequestedPublishingInterval  | opcua.RequestedPublishingInterval     | FT_DOUBLE     | opcua |       | 0x0 |     |
|   RequestedSessionTimeout  | opcua.RequestedSessionTimeout     | FT_DOUBLE     | opcua |       | 0x0 |     |
|   ResultMask   | opcua.ResultMask  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Results  | opcua.Results     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   RetransmitSequenceNumber     | opcua.RetransmitSequenceNumber    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ReturnBounds     | opcua.ReturnBounds    | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   ReturnDiagnostics    | opcua.ReturnDiagnostics   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RevisedContinuationPoint     | opcua.RevisedContinuationPoint    | FT_BYTES  | opcua |       | 0x0 |     |
|   RevisedLifetime  | opcua.RevisedLifetime     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RevisedLifetimeCount     | opcua.RevisedLifetimeCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RevisedMaxKeepAliveCount     | opcua.RevisedMaxKeepAliveCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RevisedProcessingInterval    | opcua.RevisedProcessingInterval   | FT_DOUBLE     | opcua |       | 0x0 |     |
|   RevisedPublishingInterval    | opcua.RevisedPublishingInterval   | FT_DOUBLE     | opcua |       | 0x0 |     |
|   RevisedQueueSize     | opcua.RevisedQueueSize    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   RevisedSamplingInterval  | opcua.RevisedSamplingInterval     | FT_DOUBLE     | opcua |       | 0x0 |     |
|   RevisedSessionTimeout    | opcua.RevisedSessionTimeout   | FT_DOUBLE     | opcua |       | 0x0 |     |
|   RevisedStartTime     | opcua.RevisedStartTime    | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   SByte    | opcua.SByte   | FT_INT8   | opcua |  BASE_DEC     | 0x0 |     |
|   SBytes   | opcua.SBytes  | FT_INT8   | opcua |  BASE_DEC     | 0x0 |     |
|   SamplingInterval     | opcua.SamplingInterval    | FT_DOUBLE     | opcua |       | 0x0 |     |
|   SecondsTillShutdown  | opcua.SecondsTillShutdown     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   SecurityLevel    | opcua.SecurityLevel   | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   SecurityPolicyUri    | opcua.SecurityPolicyUri   | FT_STRING     | opcua |       | 0x0 |     |
|   SecurityRejectedRequestsCount    | opcua.SecurityRejectedRequestsCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   SecurityRejectedSessionCount     | opcua.SecurityRejectedSessionCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   SecurityTokenLifetime    | opcua.SecurityTokenLifetime   | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   SelectClauseResults  | opcua.SelectClauseResults     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   SemaphoreFilePath    | opcua.SemaphoreFilePath   | FT_STRING     | opcua |       | 0x0 |     |
|   SendInitialValues    | opcua.SendInitialValues   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   SequenceNumber   | opcua.SequenceNumber  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ServerCapabilities   | opcua.ServerCapabilities  | FT_STRING     | opcua |       | 0x0 |     |
|   ServerCapabilityFilter   | opcua.ServerCapabilityFilter  | FT_STRING     | opcua |       | 0x0 |     |
|   ServerCertificate    | opcua.ServerCertificate   | FT_BYTES  | opcua |       | 0x0 |     |
|   ServerId     | opcua.ServerId    | FT_STRING     | opcua |       | 0x0 |     |
|   ServerName   | opcua.ServerName  | FT_STRING     | opcua |       | 0x0 |     |
|   ServerNonce  | opcua.ServerNonce     | FT_BYTES  | opcua |       | 0x0 |     |
|   ServerProtocolVersion    | opcua.ServerProtocolVersion   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ServerUri    | opcua.ServerUri   | FT_STRING     | opcua |       | 0x0 |     |
|   ServerUris   | opcua.ServerUris  | FT_STRING     | opcua |       | 0x0 |     |
|   ServerViewCount  | opcua.ServerViewCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ServiceLevel     | opcua.ServiceLevel    | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   ServiceResult    | opcua.ServiceResult   | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   SessionAbortCount    | opcua.SessionAbortCount   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   SessionName  | opcua.SessionName     | FT_STRING     | opcua |       | 0x0 |     |
|   SessionTimeoutCount  | opcua.SessionTimeoutCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Signature    | opcua.Signature   | FT_BYTES  | opcua |       | 0x0 |     |
|   SoftwareVersion  | opcua.SoftwareVersion     | FT_STRING     | opcua |       | 0x0 |     |
|   SpecifiedAttributes  | opcua.SpecifiedAttributes     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   SpecifiedLists   | opcua.SpecifiedLists  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   StartTime    | opcua.StartTime   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   StartingRecordId     | opcua.StartingRecordId    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Status   | opcua.Status  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   StatusCode   | opcua.StatusCode  | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   StatusCodes  | opcua.StatusCodes     | FT_UINT32     | opcua |  BASE_HEX     | 0x0 |     |
|   String   | opcua.String  | FT_STRING     | opcua |       | 0x0 |     |
|   StringTable  | opcua.StringTable     | FT_STRING     | opcua |       | 0x0 |     |
|   Strings  | opcua.Strings     | FT_STRING     | opcua |       | 0x0 |     |
|   SubscriptionId   | opcua.SubscriptionId  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   SubscriptionIds  | opcua.SubscriptionIds     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Symmetric    | opcua.Symmetric   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   TargetServerUri  | opcua.TargetServerUri     | FT_STRING     | opcua |       | 0x0 |     |
|   TestId   | opcua.TestId  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   TicketData   | opcua.TicketData  | FT_BYTES  | opcua |       | 0x0 |     |
|   TimeoutHint  | opcua.TimeoutHint     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Timestamp    | opcua.Timestamp   | FT_ABSOLUTE_TIME  | opcua |       | 0x0 |     |
|   TokenData    | opcua.TokenData   | FT_BYTES  | opcua |       | 0x0 |     |
|   TokenId  | opcua.TokenId     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   TotalCount   | opcua.TotalCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   TransferRequestCount     | opcua.TransferRequestCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   TransferredToAltClientCount  | opcua.TransferredToAltClientCount     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   TransferredToSameClientCount     | opcua.TransferredToSameClientCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   TransportProfileUri  | opcua.TransportProfileUri     | FT_STRING     | opcua |       | 0x0 |     |
|   TransportProtocol    | opcua.TransportProtocol   | FT_STRING     | opcua |       | 0x0 |     |
|   TreatUncertainAsBad  | opcua.TreatUncertainAsBad     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   TriggeringItemId     | opcua.TriggeringItemId    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   TrustedCertificates  | opcua.TrustedCertificates     | FT_BYTES  | opcua |       | 0x0 |     |
|   TrustedCrls  | opcua.TrustedCrls     | FT_BYTES  | opcua |       | 0x0 |     |
|   UInt16   | opcua.UInt16  | FT_UINT16     | opcua |  BASE_DEC     | 0x0 |     |
|   UInt16s  | opcua.UInt16s     | FT_UINT16     | opcua |  BASE_DEC     | 0x0 |     |
|   UInt32   | opcua.UInt32  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   UInt32s  | opcua.UInt32s     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   UInt64   | opcua.UInt64  | FT_UINT64     | opcua |  BASE_DEC     | 0x0 |     |
|   UInt64s  | opcua.UInt64s     | FT_UINT64     | opcua |  BASE_DEC     | 0x0 |     |
|   UnacknowledgedMessageCount   | opcua.UnacknowledgedMessageCount  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   UnauthorizedRequestCount     | opcua.UnauthorizedRequestCount    | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   UnitId   | opcua.UnitId  | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   UnsupportedUnitIds   | opcua.UnsupportedUnitIds  | FT_STRING     | opcua |       | 0x0 |     |
|   UseBinaryEncoding    | opcua.UseBinaryEncoding   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   UseServerCapabilitiesDefaults    | opcua.UseServerCapabilitiesDefaults   | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   UseSimpleBounds  | opcua.UseSimpleBounds     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   UseSlopedExtrapolation   | opcua.UseSlopedExtrapolation  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   UserAccessLevel  | opcua.UserAccessLevel     | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   UserExecutable   | opcua.UserExecutable  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   UserName     | opcua.UserName    | FT_STRING     | opcua |       | 0x0 |     |
|   UserWriteMask    | opcua.UserWriteMask   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   ValidBits    | opcua.ValidBits   | FT_BYTES  | opcua |       | 0x0 |     |
|   Value    | opcua.Value   | FT_FLOAT  | opcua |       | 0x0 |     |
|   ValueRank    | opcua.ValueRank   | FT_INT32  | opcua |  BASE_DEC     | 0x0 |     |
|   VendorName   | opcua.VendorName  | FT_STRING     | opcua |       | 0x0 |     |
|   VendorProductCertificate     | opcua.VendorProductCertificate    | FT_BYTES  | opcua |       | 0x0 |     |
|   Verb     | opcua.Verb    | FT_UINT8  | opcua |  BASE_DEC     | 0x0 |     |
|   ViewVersion  | opcua.ViewVersion     | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   WriteMask    | opcua.WriteMask   | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   X    | opcua.X   | FT_DOUBLE     | opcua |       | 0x0 |     |
|   XmlElement   | opcua.XmlElement  | FT_BYTES  | opcua |       | 0x0 |     |
|   XmlElements  | opcua.XmlElements     | FT_BYTES  | opcua |       | 0x0 |     |
|   Message fragments    | opcua.fragments   | FT_NONE   | opcua |       | 0x0 |     |
|   Message fragment     | opcua.fragment    | FT_FRAMENUM   | opcua |       | 0x0 |     |
|   Message fragment overlap     | opcua.fragment.overlap    | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Message fragment overlapping with conflicting data   | opcua.fragment.overlap.conflicts  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Message has multiple tail fragments  | opcua.fragment.multiple_tails     | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Message fragment too long    | opcua.fragment.too_long_fragment  | FT_BOOLEAN    | opcua |  0    | 0x0 |     |
|   Message defragmentation error    | opcua.fragment.error  | FT_FRAMENUM   | opcua |       | 0x0 |     |
|   Message fragment count   | opcua.fragment.count  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
|   Reassembled in   | opcua.reassembled.in  | FT_FRAMENUM   | opcua |       | 0x0 |     |
|   Reassembled length   | opcua.reassembled.length  | FT_UINT32     | opcua |  BASE_DEC     | 0x0 |     |
