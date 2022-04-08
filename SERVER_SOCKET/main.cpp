//#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>


#include "SocketHandler.h"



#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {

	
	SocketHandler* SocketHandler = new class SocketHandler();
	SocketHandler->StartListening();

	std::cout << sizeof(SOCKET) << std::endl;

	std::string str("start");

	while (str != "exit");
	{
		std::cin >> str;
	}

	SocketHandler->StopListening();


	system("pause");
	return 0;
}