#pragma once
#include "pch.h"
#include "ClientSession.h"

class ClientSessionManager
{
public:
	ClientSessionManager();
	~ClientSessionManager();

	ClientSession* CreateSession();
	bool RemoveSession(ClientSession* session);


public:
	vector<ClientSession*> sessions;
};

