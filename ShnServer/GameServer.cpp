
#include <iostream>

#include <WinSock2.h>
#include <mswsock.h>

#pragma comment(lib, "ws2_32.lib")


using namespace std;

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		__int32 errCode = ::WSAGetLastError();
		cout << errCode << endl;
		return 0;
	}

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htons(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	if (::bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		__int32 errCode = ::WSAGetLastError();
		cout << errCode << endl;
		return 0;
	}

	if (::listen(listenSocket, 10)) //backlog - how many clients can wait.
	{
		__int32 errCode = ::WSAGetLastError();
		cout << errCode << endl;
		return 0;
	}

	cout << "Waiting for connection" << endl;

	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int addrLen = sizeof(clientAddr);

		SOCKET clientSocket = ::accept(listenSocket, (sockaddr*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			__int32 errorCode = ::WSAGetLastError();
			cout << errorCode << endl;
			return 0;
		}
		
		cout << "Client Connected" << endl;
		cout << "Size : " << addrLen << endl;
	}

	::WSACleanup();
}