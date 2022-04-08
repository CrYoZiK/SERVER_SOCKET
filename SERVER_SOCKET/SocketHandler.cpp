#include "SocketHandler.h"

#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>


using namespace std;


SocketHandler::SocketHandler()
{
	cout << "SocketHandler constructor" << endl;

	Init();

	cout << "End constructor" << endl;
}

void SocketHandler::StartListening()
{
	m_bListening = true;

	thread thrd_listening(&SocketHandler::ListeningThread, this);

	thrd_listening.detach();

	//thread thrd_msghandle(&SocketHandler::MessagesHandlerThread, this);

	//thrd_msghandle.detach();

}

void SocketHandler::StopListening()
{
	m_bListening = false;
}

void  SocketHandler::SendMessageEveryone(SOCKET ConnFrom, char msg[256])
{
	if (m_vClientConnections.size() > 0)
	{
		for (int i = 0; i < m_vClientConnections.size(); i++)
		{
			if (m_vClientConnections[i]->GetSocket() == ConnFrom)
			{
				continue;
			}

			m_vClientConnections[i]->SendMessageToClient(msg);
		}
	}
}


void SocketHandler::Init()
{
	cout << "Initialization SocketHandler" << endl;

	m_wsaData;
	m_DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(m_DLLVersion, &m_wsaData) != 0) {
		std::cout << "Error WSAStartup" << std::endl;
		exit(1);
	}
	cout << "WSAStartup successeful" << endl;


	m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_addr.sin_port = htons(1111);
	m_addr.sin_family = AF_INET;

	m_sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(m_sListen, (SOCKADDR*)&m_addr, sizeof(m_addr));
	listen(m_sListen, SOMAXCONN);
	std::cout << "Listening is available" << std::endl;


	cout << "Initialization SocketHandler was successful" << endl;

}



void SocketHandler::ListeningThread()
{

	SOCKET newConnection;
	int sizeofaddr = sizeof(m_addr);

	while (m_bListening)
	{
		newConnection = accept(m_sListen, (SOCKADDR*)&m_addr, &sizeofaddr);

		cout << "connection " << newConnection << " was received" << endl;
		
		m_vClientConnections.push_back(new class ClientConection(this, newConnection));
		m_vSocConnections.push_back(newConnection);

		/*

		if (newConnection == 0) {
			std::cout << "Error #2" << endl;
		}
		else {
			std::cout << "Client Connected! = " << newConnection << std::endl;
			char msg[256] = "Hello. It`s my first network program!";
			send(newConnection, msg, sizeof(msg), NULL);
			std::cout << "sss" << endl;
		}
		*/

		//std::this_thread::sleep_for(2000ms);
	}

}


void SocketHandler::MessagesHandlerThread()
{
	char msg[256];
	msg[0] = '\0';

	while (m_bListening)
	{

		for (int i = 0; i < m_vSocConnections.size(); i++)
		{
			//cout << "recv from " << i << endl;
			//recv(m_vConnections[i], msg, sizeof(msg), NULL);

			if (msg[0] != '\0')
			{
				std::cout << "Message: " << msg << std::endl;
				std::cout << "from " << i << std::endl;
				msg[0] = '\0';
			}
		}

	}
}