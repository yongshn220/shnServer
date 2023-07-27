#include "IocpCore.h"

IocpCore::IocpCore()
{
	iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}

IocpCore::~IocpCore()
{
}

void IocpCore::Init(SOCKET* acceptSocket)
{
	ULONG key = 0;
	::CreateIoCompletionPort((HANDLE)acceptSocket, iocpHandle, (ULONG_PTR) &key, 0);

	RegisterReceive();
}



void IocpCore::Dispatch()
{

}