#pragma once
#include "pch.h"

class RecvBuffer
{
	enum { BUFFER_COUNT = 10 };

public:
	RecvBuffer(int32 bufferSize);
	~RecvBuffer();


	void Clean();
	void OnRead(int32 numOfBytes);
	void OnWrite(int32 numOfBytes);

	char* ReadPos()  { return &_buffer[_readPos]; }
	char* WritePos() { return &_buffer[_writePos]; }
	int32 DataSize() { return _writePos - _readPos; }
	int32 FreeSize() { return _capacity - _writePos; }

private:
	int32 _capacity = 0;
	int32 _bufferSize = 0;
	int32 _readPos = 0;
	int32 _writePos = 0;
	vector<char> _buffer;
};

