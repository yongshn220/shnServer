#pragma once
#include "pch.h"
#include "Player.h"

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	Player* CreatePlayer();

private:
	int32 _playerCount;
	vector<Player*> _players;
	Position _startPosition;
};

extern PlayerManager GPlayerManager;