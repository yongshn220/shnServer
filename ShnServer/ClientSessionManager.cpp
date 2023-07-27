#include "ClientSessionManager.h"

ClientSessionManager::ClientSessionManager()
{
}

ClientSessionManager::~ClientSessionManager()
{
}

bool ClientSessionManager::CreateSession()
{
	ClientSession* session = new ClientSession();
	sessions.push_back(session);

	return true;
}

bool ClientSessionManager::RemoveSession(ClientSession* session)
{
	return false;
}
