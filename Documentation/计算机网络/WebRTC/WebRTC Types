RTCConfiguration 
0. Type
	RTCIceServer 
	RTCIceTransportPolicy 
	RTCBundlePolicy 
	RTCRtcpMuxPolicy 
	RTCSignalingState 
	RTCIceGatheringState 
	RTCPeerConnectionState 
	RTCIceConnectionState 
	RTCSessionDescription
	enum RTCSdpType 
	enum RTCBundlePolicy
	enum RTCIceTransportPolicy
	enum RTCRtcpMuxPolicy
	enum RTCSignalingState 

1. Peer-to-peer connections
	1. Configuration
	2. State Definitions	
		RTCSignalingState
			stable					There is no offer/answer exchange in progress. This is also the initial state, in which case the local and remote descriptions are empty.
			have-local-offer		A local description, of type "offer", has been successfully applied.
			have-remote-offer		A remote description, of type "offer", has been successfully applied.
			have-local-pranswer		A remote description of type "offer" has been successfully applied and a local description of type "pranswer" has been successfully applied.
			have-remote-pranswer	A local description of type "offer" has been successfully applied and a remote description of type "pranswer" has been successfully applied.
			closed					The RTCPeerConnection has been closed; its [[IsClosed]] slot is true.			
		RTCIceGatheringState 
			new
			gathering
			complete
		RTCPeerConnectionState	
			closed			[[IceConnectionState]] is "closed".
			failed			The previous state doesn't apply, and either [[IceConnectionState]] is "failed" or any RTCDtlsTransports are in the "failed" state.
			disconnected	None of the previous states apply, and [[IceConnectionState]] is "disconnected".
			new				None of the previous states apply, and either [[IceConnectionState]] is "new", and all RTCDtlsTransports are in the "new" or "closed" state, or there are no transports.
			connected		None of the previous states apply, [[IceConnectionState]] is "connected", and all RTCDtlsTransports are in the "connected" or "closed" state.
			connecting		None of the previous states apply.
		RTCIceConnectionState
			closed			The RTCPeerConnection object's [[IsClosed]] slot is true.
			failed			The previous state doesn't apply and any RTCIceTransports are in the "failed" state.
			disconnected	None of the previous states apply and any RTCIceTransports are in the "disconnected" state.
			new				None of the previous states apply and all RTCIceTransports are in the "new" or "closed" state, or there are no transports.
			checking		None of the previous states apply and any RTCIceTransports are in the "new" or "checking" state.
			completed		None of the previous states apply and all RTCIceTransports are in the "completed" or "closed" state.
			connected		None of the previous states apply and all RTCIceTransports are in the "connected", "completed" or "closed" state.
				
	3. Session Description Model
		RTCSdpType
			offer		An RTCSdpType of "offer" indicates that a description MUST be treated as an [SDP] offer.
			pranswer	An RTCSdpType of "pranswer" indicates that a description MUST be treated as an [SDP] answer, but not a final answer. A description used as an SDP pranswer may be applied as a response to an SDP offer, or an update to a previously sent SDP pranswer.			
			answer		An RTCSdpType of "answer" indicates that a description MUST be treated as an [SDP] final answer, and the offer-answer exchange MUST be considered complete. A description used as an SDP answer may be applied as a response to an SDP offer or as an update to a previously sent SDP pranswer.
			rollback	An RTCSdpType of "rollback" indicates that a description MUST be treated as canceling the current SDP negotiation and moving the SDP [SDP] offer back to what it was in the previous stable state. Note the local or remote SDP descriptions in the previous stable state could be null if there has not yet been a successful offer-answer negotiation. An "answer" or "pranswer" cannot be rolled back.
					
	4. Session Negotiation Model
		

2. RTP Media API
	RTCRtpSender
	RTCRtpReceiver 
	RTCRtpTransceiver
	RTCDtlsTransport
	RTCIceTransport

3. Peer-to-peer Data API
	RTCSctpTransport
	RTCDataChannel
		Creating a data channel
		Announcing a data channel as open
		Announcing a data channel instance
		Closing procedure
		Announcing a data channel as closed
		Transfering data channel
		Error on creating data channels
		Receiving messages on a data channel


	RTCDataChannelEvent


4. Peer-to-peer DTMF
5. Statistics Model
6. Media Stream API Extensions for Network Use
7. Examples and Call Flows
8. Error Handling
9. Event summary
10. Privacy and Security Considerations
11. Accessibility Considerations
12. 
	STUN servers
	TURN servers
	credential 
	ICE candidates 
	signaling channel
	SCTP transport
	SCTP data 
13. RFC
	1. The [RFC9429] specification, as a whole, describes the details of how the RTCPeerConnection operates.
	2. STUN or TURN URI(s) as defined in [RFC7064] and [RFC7065] or other URI types.
	3. As described in [RFC9429] (section 4.1.1.), if the iceTransportPolicy member of the RTCConfiguration is specified, it 			defines the ICE candidate policy [RFC9429] (section 3.5.3.) the browser uses to surface the permitted 				candidates to the application; only these candidates will be used for connectivity checks.