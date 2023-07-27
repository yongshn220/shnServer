#pragma once
#include "pch.h"
#include "IocpEvent.h"


class ClientSession : 
{
public:
	ClientSession();
	~ClientSession();

	void Dispatch(IocpEvent* iocpEvent);

	void RegisterRecv();

	void RegisterSend();

	void ProcessAccept();

	void ProcessRecv();

	void ProcessSend();

public:
	SOCKET socket;

	int32 buffSize = 1000;
	char recvBuffer[1000];

};

