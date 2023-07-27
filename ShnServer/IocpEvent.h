#pragma once
#include "pch.h"

class ClientSession;

enum class EventType : int8
{
	Accept,
	Recv,
	Send
};


class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void Init();

public:
	EventType eventType;
	ClientSession* session;
};

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::Accept) {}
};

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::Recv) {}
};

class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::Send) {}
};