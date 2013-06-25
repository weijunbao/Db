#ifndef util_h
#define util_h

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void setU64(char* buffer,int offset,uint64_t value);
uint64_t getU64(const char* buffer,int offset);

void setU32(char* buffer,int offset,uint32_t value);

uint32_t getU32(const char* buffer,int offset);

void setU16(char* buffer,int offset,uint16_t value);
uint16_t getU16(const char* buffer,int offset);


	#ifdef __cplusplus
  }
	#endif
#endif