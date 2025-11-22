/*
	概念:
		Offer
		Answer
	类:
		QWebRTCServer
		QWebRTCSignaling
		QVideoSource
		QPeerConnectionFactory
		QPeerConnectionObserver
		ClientItemWidget
		CLIController
		ClientItem
		ConfigWindow
		MediaRecorder
		MediaRendererWidget
		SRServerWindow


	QWebRTCServer:
		QMap<QString, QWebSocket *> clients_;
		QMap<QString, rtc::scoped_refptr<webrtc::PeerConnectionInterface>> peerConnections_;
		QMap<QString, rtc::scoped_refptr<QPeerConnectionObserver>> observers_;
		QMap<QString, rtc::scoped_refptr<webrtc::DataChannelInterface>> dataChannels_;

		handleClientMessage		处理客户端消息
		handleClientCommand		处理客户端命令
		sendCommandToClient		发送命令给客户端
		onSocketDisconnected	处理Socket断开

	QWebRTCSignaling
		sendOffer				发送offer
		sendAnswer			
		sendIceCandidate

		receiveOffer			接受offer
		receiveAnswer
		receiveIceCandidate

		sendDescription
		signalSendMessage

	SRServerWindow

	MediaRecorderWorker
	MediaRecorder
*/