#include <iostream>
#include <winsock2.h>
#include <cstdint>
#pragma comment (lib ,"WS2_32.lib")

using namespace std;

int main()
{
	WSADATA WSAData;

	SOCKET server, client;

	SOCKADDR_IN serverAddr, clientAddr;
	
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);

	bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	listen(server, 0);

	cout << "Listening for incoming connections..." << endl;

	char buffer[1024];
	char x[3];
	int clientAddrSize = sizeof(clientAddr);
	if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
	{
		cout << "Client connected!" << endl;


		recv(client, x, sizeof(x), 0);
		int arr[3];

		for (int i = 0; i < 3; i++)
		{
			arr[i] = static_cast<int>(x[i]);
			cout << "server recive : " << arr[i] << " " << endl;
		}

		int sum = arr[0] + arr[1] + arr[2];
		char c = static_cast<char>(sum);
		char ac[1] = { c };


		send(client, ac, sizeof(ac), 0);
		cout << "server say : " << "result sent ! " << endl;
		closesocket(client);
		cout << "Client disconnected." << endl;




	}
	system("pause");
}