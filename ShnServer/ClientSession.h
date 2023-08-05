#pragma once
#include "pch.h"
#include "IocpEvent.h"
#include "RecvBuffer.h"
#include "PlayerManager.h"

class ClientSession
{
	enum
	{
		BUFFER_SIZE = 0x10000, //64kb
	};

public:
	ClientSession();
	~ClientSession();

	int32 OnRecv(char* buffer, int32 len);
	
	void OnSend();

	void Connect();

	void Send(char* buffer, int32 len);

	void Dispatch(IocpEvent* iocpEvent, int32 numOfBytes);

	void RegisterRecv();

	void RegisterSend(char* buffer, int32 len);

	void ProcessAccept();

	void ProcessRecv(int32 numOfBytes);

	void ProcessSend(int32 numOfBytes);

public:
	SOCKET socket;

	RecvBuffer recvBuffer;
};

