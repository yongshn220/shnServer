
#include "pch.h"
#include "IocpCore.h"
#include "ClientSessionManager.h"
#include "ClientPacketHandler.h"


void InitListenSocket(SOCKET& listenSocket);

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET listenSocket;
	InitListenSocket(listenSocket);

	IocpCore* iocpCore = new IocpCore();

	ClientSessionManager* sessionManager = new ClientSessionManager();
	vector<thread> threads;
	for (__int32 i = 0; i < 5; i++) 
	{
		threads.push_back(thread([=]() { iocpCore->Dispatch(); } ));
	}

	while (true)
	{
		SOCKADDR_IN clientAddr;
		__int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
			return 0;

		ClientSession* session = sessionManager->CreateSession();
		session->socket = clientSocket;

		cout << "Client Accepter" << endl;

		iocpCore->Register(&clientSocket);
		session->Connect();
	}

	for (__int32 i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}


	::WSACleanup();
}



void InitListenSocket(SOCKET &listenSocket)
{
	listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	::bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

	// SOMAXCONN : max reasonable backlog.
	::listen(listenSocket, SOMAXCONN);
}