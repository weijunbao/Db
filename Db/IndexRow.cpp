#include "const.h"
#include "DataRow.h"
#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

int IndexRow::getSize(void)
{
	return DEFAULT_KEY_SIZE_DISK + this->getKeySize() + PAGE_NO_SIZE;
}
/*
IndexRow:
		 keySize  |1 byte
		 key	    |
		 page	    |4 byte
*/
int IndexRow::parse(PIndexRow& row,char* pageBuffer,int& offset)
{
	uint8_t keySize;
	char* pKey;
	assert(pageBuffer);
	//////////KeySize
	keySize=*(uint8_t*)(pageBuffer+offset);
	offset+=1;

	assert(keySize>0 && keySize<=MAX_KEY_SIZE);
	if(keySize==0){
		return PTE_KEYSIZE_ZERO;
	}
	else if(keySize > MAX_KEY_SIZE){
		return PTE_KEYSIZE_MAX;
	}
	else{
		pKey=(char*)malloc(keySize);
		if(pKey==NULL){
			return PTE_MEMORY;
		}
		else{
			PageNo pageNo;
			memcpy(pKey,pageBuffer+offset,keySize);
			if(row==NULL)
				row=new IndexRow();
			row->set(pKey,keySize);

			offset+=keySize;
			pageNo=getU32(pageBuffer,offset);
			row->pageNo=pageNo;
		}
	}
	return PFE_SUCESS;
}

int IndexRow::writeBuffer(char* pageBuffer,int offset)
{
	assert(pageBuffer);
	///////////KEY/////////////////
	pageBuffer[offset]=(uint8_t)this->getKeySize();
	offset+=1;//keySize
	memcpy((void*)(pageBuffer[offset]),this->getKey(),this->getKeySize());
	offset+=this->getKeySize();//key
	///////////PAGE/////////////////
	setU32(pageBuffer,offset,this->pageNo);
	offset+=4;

	return 1;
}