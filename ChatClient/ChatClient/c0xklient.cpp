
#include "Client.h"

int main()
{
	system("pause");
	
	Client myClient("127.0.0.1", 1111);

	if (!myClient.Connect())
	{
		std::cout << "Failed to connect to servr..." << std::endl;
		system("pause");
		return 1;
	}

	//char nick[512] = "";
	//char tmp[3] = ": ";

	//std::cout << "Enter nickname: \n";
	//std::cin.getline(nick, 8);
	//strcat_s(nick, tmp);


	std::string userInput;

	while (true)
	{
		std::getline(std::cin, userInput);
		if (!myClient.SendString(userInput))
			break;
		//int buffLenght = buffer.size();
		//Packet packettype = P_ChatMessage;
		//send(mainSocket, (char*)&packettype, sizeof(Packet), NULL);
		//send(mainSocket, (char*)&buffLenght, sizeof(int), NULL); //msg size
		//send(mainSocket, buffer.c_str(), buffLenght, NULL);
		Sleep(10);
	}



	//int bytesSent;
	//int bytesRecv = SOCKET_ERROR;
	//char sendbuf[32] = "";
	//char recvbuf[32] = "";
	//
	//printf("Write your msg\n");
	//printf("%s", nick);
	//std::cin.getline(sendbuf, 32);
	//strcat_s(nick, sendbuf);

	/*bytesSent = send(mainSocket, nick, strlen(nick), 0);*/
	//printf("Bytes sent: %ld\n", bytesSent);

	//while (bytesRecv == SOCKET_ERROR)
	//{
	//	bytesRecv = recv(mainSocket, recvbuf, 32, 0);

	//	if (bytesRecv == 0 || bytesRecv == WSAECONNRESET)
	//	{
	//		printf("Connection closed.\n");
	//		break;
	//	}

	//	if (bytesRecv < 0)
	//		return 1;

	//	//printf("Bytes received: %ld\n", bytesRecv);
	//	//printf("Received text: %s\n", recvbuf);
	//}

	system("pause");

	/*int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char sendbuf[256];
	char recvbuf[256];

	while ()
*/
}
