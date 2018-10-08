#include "Client.h"

bool Client::SendInt(int _int)
{
	int RetnCheck = send(mainSocket, (char*)&_int, sizeof(int), NULL); //send int: _int
	if (RetnCheck == SOCKET_ERROR)
		return false; //false cnnection isse
	return true;	//int ok sent
}

bool Client::GetInt(int & _int)
{
	int RetnCheck = recv(mainSocket, (char*)&_int, sizeof(int), NULL); //recv int: _int
	if (RetnCheck == SOCKET_ERROR)
		return false; //false cnnection isse
	return true;	//int ok sent
}

bool Client::SendPacketType(Packet _packettype)
{
	int RetnCheck = send(mainSocket, (char*)&_packettype, sizeof(Packet), NULL); //send int: _int
	if (RetnCheck == SOCKET_ERROR)
		return false; //false cnnection isse
	return true;	//int ok sent
}

bool Client::GetPacketType(Packet & _packettype)
{
	int RetnCheck = recv(mainSocket, (char*)&_packettype, sizeof(Packet), NULL); //recv int: _int
	if (RetnCheck == SOCKET_ERROR)
		return false; //false cnnection isse
	return true;	//int ok sent
}

bool Client::SendString(std::string & _string)
{
	if (!SendPacketType(P_ChatMessage))
		return false;
	int bufferlenght = _string.size();
	if (!SendInt(bufferlenght))
		return false;
	int RetnCheck = send(mainSocket, _string.c_str(), bufferlenght, NULL);
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}

bool Client::GetString(std::string & _string)
{
	int bufferlenght; //msg length
	if (!GetInt(bufferlenght))
		return false;
	char * buffer = new char[bufferlenght + 1];
	buffer[bufferlenght] = '\0';
	int RetnCheck = recv(mainSocket, buffer, bufferlenght, NULL);
	_string = buffer;
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}