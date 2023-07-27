#include "ClientSession.h"


ClientSession::ClientSession() : socket(INVALID_SOCKET)
{}

ClientSession::~ClientSession()
{
}

void ClientSession::Connect()
{
	ProcessAccept();
}


void ClientSession::Dispatch(IocpEvent* iocpEvent)
{
	switch (iocpEvent->eventType)
	{
	case EventType::Accept:
		ProcessAccept();
		break;
	case EventType::Recv:
		ProcessRecv();
		break;
	case EventType::Send:
		ProcessSend();
		break;
	}
}

void ClientSession::RegisterRecv()
{
	WSABUF wsaBuf;
	wsaBuf.buf = recvBuffer;
	wsaBuf.len = buffSize;

	RecvEvent* recvEvent = new RecvEvent();
	recvEvent->session = this;

	DWORD recvLen = 0;
	DWORD flags = 0;

	::WSARecv(socket, &wsaBuf, 1, &recvLen, &flags, recvEvent, NULL);
}

void ClientSession::RegisterSend()
{
}

void ClientSession::ProcessAccept()
{
	RegisterRecv();
}

void ClientSession::ProcessRecv()
{
}

void ClientSession::ProcessSend()
{
}
