#include "ClientPacketHandler.h"

void ClientPacketHandler::HandlePacket()
{
}

char* ClientPacketHandler::Make_S_USER()
{
	char* buffer = new char[12];

	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	header->type = S_USER;
	header->size = (int32)sizeof(PacketHeader) + (int32)sizeof(Packet_S_USER);

	Packet_S_USER* packet = reinterpret_cast<Packet_S_USER*>(header + 1);

	packet->ID = 1234;

	return buffer;
}

char* ClientPacketHandler::Make_S_PLAYER(int32 ID, float x, float y, float z)
{
	char* buffer = new char[24];

	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	
	header->type = S_PLAYER;
	header->size = (int32)sizeof(PacketHeader) + (int32)sizeof(Packet_S_PLAYER);

	Packet_S_PLAYER* packet = reinterpret_cast<Packet_S_PLAYER*>(header + 1);

	packet->ID = ID;
	packet->x = x;
	packet->y = y;
	packet->z = z;

	return buffer;
}
