#include "PlayerManager.h"

PlayerManager GPlayerManager;

PlayerManager::PlayerManager() : _playerCount(0)
{
	_startPosition.x = 500;
	_startPosition.y = 4000;
	_startPosition.z = -450;
}

PlayerManager::~PlayerManager()
{}

Player* PlayerManager::CreatePlayer()
{
	Player* player = new Player(_playerCount, _startPosition);
	_playerCount += 1;

	return player;
}
