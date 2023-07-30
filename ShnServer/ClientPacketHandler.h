#pragma once
#include "SendBuffer.h"
#include "Types.h"
#include "pch.h"

enum
{
	S_USER = 1,
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
#pragma pack(0)

class ClientPacketHandler
{
public:
	static void HandlePacket();

	static char* Make_S_USER();
};

