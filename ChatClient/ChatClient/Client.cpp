#include "Client.h"

Client::Client(std::string IP, int PORT)
{
	WSADATA wsaData;
	int resut = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (resut != NO_ERROR)
		printf("Init error.\n");

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(IP.c_str());
	service.sin_port = htons(PORT);
	clientptr = this;
}

bool Client::Connect()
{
	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET)
	{
		printf("Err creat sock: %ld\n", WSAGetLastError());
		WSACleanup();
		system("pause");
		return false;
	}

	if (connect(mainSocket, (SOCKADDR *)&service, sizeofservice) == SOCKET_ERROR)
	{
		printf("Failed to connect.\n");
		WSACleanup();
		system("pause");
		return false;
	}
	else
	{
		printf("Client connected.\n");
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL);
	return true;
}

bool Client::ProcessPacket(Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage:
	{
		std::string Message;
		if (!GetString(Message))
			return false;
		std::cout << Message << std::endl;
		break;
	}
	default:
		std::cout << "Unrecognized packet: " << _packettype << std::endl;
		break;
	}
	return true;
}

bool Client::CloseConnection()
{
	if (closesocket(mainSocket) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAENOTSOCK)
			return true;

		std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, ErrorMessage.c_str(), "error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void Client::ClientThread()
{
	Packet packettype;
	while (true)
	{
		if (!clientptr->GetPacketType(packettype))
			break;
		if (!clientptr->ProcessPacket(packettype)) //if not properly process break? - 2d catch err
			break;
	}
	std::cout << "Lost connection." << std::endl;
	
	if (CloseClipboard())
	{
		std::cout << "Socket closed successfuly." << std::endl;
	}
	else
	{
		std::cout << "Socket was not able to closed." << std::endl;
	}
}