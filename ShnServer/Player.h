#pragma once
#include "pch.h"
#include "ClientPacketHandler.h"

class ClientSession;


class Player
{
public:
	Player(int32 id, Position pos);
	~Player();

	void setSession(ClientSession* session);

	void sendPacket();

private:
	ClientSession* _session;
	int32 _id;
	Position _position;
};

