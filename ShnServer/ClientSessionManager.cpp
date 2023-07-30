#include "ClientSessionManager.h"

ClientSessionManager::ClientSessionManager()
{
}

ClientSessionManager::~ClientSessionManager()
{
}

ClientSession* ClientSessionManager::CreateSession()
{
	ClientSession* session = new ClientSession();
	sessions.push_back(session);

	return session;
}

bool ClientSessionManager::RemoveSession(ClientSession* session)
{
	return false;
}
