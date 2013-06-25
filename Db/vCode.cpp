#include "vCode.h"
#include <assert.h>
#include <memory.h>

#define VCODE1 (2^7)
#define VCODE2 (2^14)
#define VCODE3 (2^21)
#define VCODE4 (2^28)
#define VCODE5 (2^35)
#define VCODE6 (2^42)
#define VCODE7 (2^49)
#define VCODE8 (2^56)
#define VCODE9 (2^63)
#define VCODE10 (2^70)
//vCode::vCode(void)
//{
//}
//
//
//vCode::~vCode(void)
//{
//}

/*0x7F	0111 1111
	0x80	1000 0000
	0xFF	1111 1111
*/
int vCode::vCodei8(uint8_t i,char* pData){
	assert(pData);
	if(i&0x80){
		pData[0]=(char)(0x80^0x01);
		pData[1]=(i&0x7f);
		return 2;
	}
	else{
		memcpy(pData,&i,sizeof(uint8_t));
		return 1;
	}
}
int vCode::vCodei16(uint16_t i,char* pData){
	uint16_t a=0x8000;
	int x=0;
	int nbyte=0;
	int returnValue;
	while(x<16){
		if(i&a) break;
		a>>=1;x+=1;
	}
	returnValue=nbyte=(16-x)/7;
	if((16-x)%7){
		returnValue+=1;
		nbyte+=1;
	}
	if(returnValue==0){
		returnValue=nbyte=1;
	}
	do{
		nbyte-=1;
		pData[nbyte]=(i & 0x7f)| 0x80;
		i>>=7;
	}
	while(nbyte);
	pData[returnValue-1]&=0x7f;
	return returnValue;
}
int vCode::vCodei32(uint32_t i,char* pData){
	uint32_t a=0x80000000;
	int x=0;
	int nbyte=0;
	int returnValue=0;
	assert(pData);
	while(x<32){
		if(i&a) break;
		a>>=1;x+=1;
	}
	returnValue=nbyte=(32-x)/7;
	if((32-x)%7){
		returnValue+=1;
		nbyte+=1;
	}
	if(returnValue==0){
		returnValue=nbyte=1;
	}
	do{
		nbyte-=1;
		pData[nbyte]=(i & 0x7f)| 0x80;
		i>>=7;
	}
	while(nbyte);
	pData[returnValue-1]&=0x7f;
	return returnValue;
}
int vCode::vCodei64(uint64_t i,char* pData){
	return 1;
}
int vCode::getVariableSize(uint64_t i){
	int byte=1;
	if(i<=VCODE1) byte=1;
	else if(i<=VCODE2) byte=2;
	else if(i<=VCODE3) byte=3;
	else if(i<=VCODE4) byte=4;
	else if(i<=VCODE5) byte=5;
	else if(i<=VCODE6) byte=6;
	else if(i<=VCODE7) byte=7;
	else if(i<=VCODE8) byte=8;
	else if(i<=VCODE9) byte=9;
	//else if(i<=VCODE10) byte=10;
	else
		assert(0);
	return byte;
}
/*
返回值:0 or 1??现在实现是返回N个字节
i:解析出的值.
加上长度判断 no complete
*/
int vCode::getVariableCode(const char* pData,uint64_t& i){
	int a=0;
	uint8_t mark=0;
	int count=0;
	uint64_t b=0;
	assert(pData);
	do{
		b<<=7;mark=(pData[a]&0x80);
		if(mark){
			b^=(pData[a]&0x7f);
		}
		else{
			b^=pData[a];
		}
		assert(a<10);//待定
		a+=1;
	}
	while(mark);
	i=b;
	//*i=b;
	return a;
}