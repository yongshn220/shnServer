#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int32 bufferSize) : _bufferSize(bufferSize)
{
	_capacity = bufferSize * BUFFER_COUNT;
	_buffer.resize(_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	int32 dataSize = DataSize();
	if (dataSize == 0)
	{
		_readPos = 0;
		_writePos = 0;
	}
	else
	{
		if (FreeSize() < _bufferSize)
		{
			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}
	}
}

void RecvBuffer::OnRead(int32 numOfBytes)
{
	_readPos += numOfBytes;
}

void RecvBuffer::OnWrite(int32 numOfBytes)
{
	_writePos += numOfBytes;
}
