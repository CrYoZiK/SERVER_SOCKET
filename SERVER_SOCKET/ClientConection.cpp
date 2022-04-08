#include "ClientConection.h"

#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>





ClientConection::ClientConection(MessageTransmitter* transmitter, SOCKET connection) :
	m_ptrMsgTransmitter(transmitter),
	m_socConnection(connection)
{

	std::thread thrd_msghandle(&ClientConection::MessagesRecieveThread, this);

	thrd_msghandle.detach();

}

void ClientConection::SendMessageToClient(char msg[256])
{

	char sendMessage[256];

	for (int i = 0; i < sizeof(sendMessage); i++)
	{
		if (msg[i] == '\0')
		{
			sendMessage[i] = msg[i];
			break;
		}
		sendMessage[i] = msg[i];
	}

	send(m_socConnection, sendMessage, sizeof(sendMessage), NULL);
}


void ClientConection::MessagesRecieveThread()
{
	char msg[256];
	msg[0] = '\0';

	while (true)
	{
			//cout << "recv from " << i << endl;
			recv(m_socConnection, msg, sizeof(msg), NULL);

			if (msg[0] != '\0')
			{
				std::cout << "(" << m_socConnection << ") Message: " << msg << std::endl;
				m_ptrMsgTransmitter->SendMessageEveryone(m_socConnection, msg);
				msg[0] = '\0';
			}

	}
}