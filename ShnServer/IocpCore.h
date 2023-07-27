#pragma once
#include "pch.h"
#include "IocpEvent.h"

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	void Register(SOCKET* acceptSocket);

	void Dispatch();

public:
	HANDLE iocpHandle;
};

