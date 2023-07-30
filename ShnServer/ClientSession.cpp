#include "ClientSession.h"
#include "ClientPacketHandler.h"

ClientSession::ClientSession() : socket(INVALID_SOCKET), recvBuffer(BUFFER_SIZE)
{}

ClientSession::~ClientSession()
{}

int32 ClientSession::OnRecv(char* buffer, int32 len)
{
	return len;
}

void ClientSession::OnSend()
{
}

void ClientSession::Connect()
{
	ProcessAccept();

	char* buffer = ClientPacketHandler::Make_S_USER();
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	Send(buffer, header->size);
}

void ClientSession::Send(char* buffer, int32 len)
{
	RegisterSend(buffer, len);
}


void ClientSession::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	switch (iocpEvent->eventType)
	{
	case EventType::Accept:
		ProcessAccept();
		break;
	case EventType::Recv:
		ProcessRecv(numOfBytes);
		break;
	case EventType::Send:
		ProcessSend(numOfBytes);
		break;
	}
}

void ClientSession::RegisterRecv()
{
	WSABUF wsaBuf;
	wsaBuf.buf = recvBuffer.WritePos();
	wsaBuf.len = recvBuffer.FreeSize();

	RecvEvent* recvEvent = new RecvEvent();
	recvEvent->session = this;

	DWORD recvLen = 0;
	DWORD flags = 0;

	::WSARecv(socket, &wsaBuf, 1, &recvLen, &flags, recvEvent, NULL);
}

void ClientSession::RegisterSend(char* buffer, int32 len)
{
	WSABUF wsaBuf;
	wsaBuf.buf = buffer;
	wsaBuf.len = len;

	SendEvent* sendEvent = new SendEvent();
	sendEvent->session = this;

	DWORD sendLen = 0;
	DWORD flags = 0;

	::WSASend(socket, &wsaBuf, 1, &sendLen, flags, sendEvent, NULL);
}

void ClientSession::ProcessAccept()
{
	RegisterRecv();
}

void ClientSession::ProcessRecv(int32 numOfBytes)
{
	cout << "Data Received : " << numOfBytes << endl;

	recvBuffer.OnWrite(numOfBytes);

	int32 processLen = OnRecv(recvBuffer.ReadPos(), recvBuffer.DataSize());

	recvBuffer.OnRead(processLen);

	recvBuffer.Clean();
}

void ClientSession::ProcessSend(int32 numOfBytes)
{
	cout << "Data Sent" << endl;
}

