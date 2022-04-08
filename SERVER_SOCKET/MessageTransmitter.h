#pragma once
#include <winsock2.h>

class MessageTransmitter
{
public:
	virtual void SendMessageEveryone(SOCKET ConnFrom, char msg[256]) = 0;

};

