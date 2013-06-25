#include "util.h"

void setU64(char* buffer,int offset,uint64_t value){

}

uint64_t getU64(const char* buffer,int offset){
	return buffer[offset + 7] |	(buffer[offset + 6] <<8)	|
		(buffer[offset + 5] <<16) | (buffer[offset + 4] <<24) |
		((uint64_t)buffer[offset + 3]) <<32 | ((uint64_t)buffer[offset + 2] <<40) |
		((uint64_t)buffer[offset + 1]) <<48 | ((uint64_t)buffer[offset + 0] <<56);
}

void setU32(char* buffer,int offset,uint32_t value){
	buffer[offset + 3] = (unsigned char)(value & 0xff);
	buffer[offset + 2] = (unsigned char)((value >> 8) & 0xff);
	buffer[offset + 1] = (unsigned char)((value >> 16) & 0xff);
	buffer[offset + 0] = (unsigned char)((value >> 24) & 0xff);
}

uint32_t getU32(const char* buffer,int offset){
	return (buffer[offset+0]<<24) | (buffer[offset+1]<<16) | (buffer[offset+2]<<8) | buffer[offset+3];
}

void setU16(char* buffer,int offset,uint16_t value){
	buffer[offset+1]=(unsigned char)(value & 0xFF);
	buffer[offset+0]=(unsigned char)((value>>8)& 0xFF);
}

uint16_t getU16(const char* buffer,int offset){
	return	buffer[offset + 1] | buffer[offset + 0] << 8;
}