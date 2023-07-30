#include "IocpCore.h"
#include "ClientSession.h"

IocpCore::IocpCore()
{
	iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}

IocpCore::~IocpCore()
{
}

void IocpCore::Register(SOCKET* acceptSocket)
{
	ULONG key = 0;
	::CreateIoCompletionPort((HANDLE)acceptSocket, iocpHandle, (ULONG_PTR) &key, 0);
}

void IocpCore::Dispatch()
{
	while (true)
	{
		// DWORD : uint32
		DWORD numOfBytes = 0;
		ULONG key = 0;
		IocpEvent* eventType = nullptr;

		bool ret = ::GetQueuedCompletionStatus(iocpHandle, &numOfBytes,
			(ULONG_PTR*)&key, OUT (LPOVERLAPPED*)&eventType, INFINITE);

		if (ret == FALSE || numOfBytes == 0)
		{
			cout << "IOCP Fail" << endl;
			// todo: error handle
			continue;
		}

		ClientSession* session = eventType->session;
		session->Dispatch(eventType, numOfBytes);
	}
}