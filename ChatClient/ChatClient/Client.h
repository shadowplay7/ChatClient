#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

enum Packet
{
	P_ChatMessage
};

class Client
{
public:
	Client(std::string IP, int PORT);
	bool Connect();
	bool CloseConnection();
	bool SendString(std::string & _string);
private:
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();

	//sending
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);

	//gettin
	bool GetInt(int & _int);
	bool GetPacketType(Packet & _ackettype);
	bool GetString(std::string & _string);

private:
	SOCKET mainSocket;
	sockaddr_in service;
	int sizeofservice = sizeof(service);
	//memset(&service, 0, sizeof(service));
};

static Client * clientptr;
