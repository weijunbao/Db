#pragma once
#include "commonType.h"
#include <stdint.h>

#define ASSERT_VCODE_SIZE(vSize)\
	assert(vSize>0 && vSize<10);

class vCode :
	public NonCreate

{
public:
	/*vCode(void);
	virtual ~vCode(void);*/
public:
	static int vCodei8(uint8_t i,char* pData);
	static int vCodei16(uint16_t i,char* pData);
	static int vCodei32(uint32_t i,char* pData);
	static int vCodei64(uint64_t i,char* pData);
	static int getVariableSize(uint64_t i);
	static int getVariableCode(const char* pData,uint64_t& i);
};