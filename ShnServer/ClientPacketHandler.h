#pragma once
#include "SendBuffer.h"
#include "Types.h"
#include "pch.h"

class Player;

enum
{
	S_USER = 1,
	S_PLAYER = 2,
};

#pragma pack(1)
struct PacketHeader
{
	int32 type;
	int32 size;
};

struct Packet_S_USER
{
	int32 ID;
};

struct Packet_S_PLAYER
{
	int32 ID;
	float x;
	float y;
	float z;
};
#pragma pack(0)

class ClientPacketHandler
{
public:
	static void HandlePacket();

	static char* Make_S_USER();

	static char* Make_S_PLAYER(int32 ID, float x, float y, float z);
};

