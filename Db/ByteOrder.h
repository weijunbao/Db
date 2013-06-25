#pragma once

enum{
	BIG_ENDIAN=0x00,
	LITTLE_ENDIAN=0x01
};

class ByteOrder
{
private:
	ByteOrder(void);
	~ByteOrder(void);
public:
	static bool IS_BIG_ENDIAN;
	static void checkEndian(void);
};