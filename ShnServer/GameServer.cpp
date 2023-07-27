
#include <iostream>
#include "pch.h"
#include "IocpCore.h"
#include "ClientSessionManager.h"


const __int32 BUFSIZE = 1000;

struct Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BUFSIZE] = "";
	__int32 recvBytes = 0;
};

struct OverlappedEx
{
	WSAOVERLAPPED overlapped = {};
	__int32 type = 0;
};

void WorkerThreadMain(HANDLE iocpHandle)
{
	cout << "Working.." << endl;
	while (true)
	{
		// DWORD : uint32
		DWORD bytesTransferred = 0;
		Session* session = nullptr;
		OverlappedEx* overlappedEx = nullptr;

		bool ret = ::GetQueuedCompletionStatus(iocpHandle, &bytesTransferred,
			(ULONG_PTR*)&session, (LPOVERLAPPED*)&overlappedEx, INFINITE);

		if (ret == FALSE || bytesTransferred == 0)
		{
			cout << "IOCP fail" << endl;
			continue;
		}

		cout << "Parse" << endl;

		if (overlappedEx->type == IO_TYPE::ACCEPT)
		{
			{
				OverlappedEx* overlappedEx = new OverlappedEx();
				overlappedEx->overlapped = {};
				overlappedEx->type = IO_TYPE::WRITE;

				WSABUF wsaBuf;
				wsaBuf.buf = session->recvBuffer;
				wsaBuf.len = BUFSIZE;

				DWORD sendLen = 0;
				DWORD flags = 0;

				::WSASend(session->socket, &wsaBuf, 1, &sendLen, flags, &overlappedEx->overlapped, NULL);
			}
			{
				cout << "Recv IOCP: " << bytesTransferred << endl;
				WSABUF wsaBuf;
				wsaBuf.buf = session->recvBuffer;
				wsaBuf.len = BUFSIZE;

				DWORD recvLen = 0;
				DWORD flags = 0;
				::WSARecv(session->socket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);
			}
		}

		if (overlappedEx->type == IO_TYPE::WRITE)
		{
			cout << "Send Success." << endl;
 		}
	}
}

SOCKET InitListenSocket(SOCKET& listenSocket);

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
		threads.push_back(thread([=]() {iocpCore->Dispatch(); } ));
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

		cout << "Client Connected" << endl;

		iocpCore->Register(&clientSocket);
		session->Connect();
	}

	for (__int32 i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}


	::WSACleanup();
}



SOCKET InitListenSocket(SOCKET &listenSocket)
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