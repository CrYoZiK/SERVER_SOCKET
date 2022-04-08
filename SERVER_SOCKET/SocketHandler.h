#pragma once
#include <winsock2.h>
#include <vector>

#include "MessageTransmitter.h"
#include "ClientConection.h"


class SocketHandler : public MessageTransmitter
{

public:

	SocketHandler();

	
	void StartListening();

	void StopListening();

	void SendMessageEveryone(SOCKET ConnFrom, char msg[256]) override;


private:

	void Init();

	void ListeningThread();

	void MessagesHandlerThread();



	bool m_bListening;
	WSAData m_wsaData;
	WORD m_DLLVersion;
	SOCKADDR_IN m_addr;
	SOCKET m_sListen;

	std::vector<ClientConection*> m_vClientConnections;
	std::vector<SOCKET> m_vSocConnections;

};

