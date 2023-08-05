#include "Player.h"
#include "ClientSession.h"

Player::Player(int32 id, Position position)
{
	_session = nullptr;
	_id = id;
	_position = position;
	
}

Player::~Player()
{
}

void Player::setSession(ClientSession* session)
{
	_session = session;
}

void Player::sendPacket()
{
	if (_session == nullptr) {
		cout << "session is nullptr" << endl;
		return;
	}
	cout << "_position.x : " << _position.x << endl;
	cout << "_position.y : " << _position.y << endl;
	cout << "_position.z : " << _position.z << endl;

	char* buffer = ClientPacketHandler::Make_S_PLAYER(_id, _position.x, _position.y, _position.z);
	
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	cout << "size:" << header->size << endl;

	_session->Send(buffer, header->size);
}
