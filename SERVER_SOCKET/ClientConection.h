#pragma once
#include <winsock2.h>

#include "MessageTransmitter.h"

class ClientConection
{


public:

	ClientConection(MessageTransmitter* transmitter, SOCKET connection);

	void SendMessageToClient(char msg[256]);

	SOCKET GetSocket() { return m_socConnection; };

private:

	void MessagesRecieveThread();

	SOCKET m_socConnection;


	MessageTransmitter* m_ptrMsgTransmitter;

};

