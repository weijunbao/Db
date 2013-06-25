#include "const.h"
#include "DataRow.h"
#include "vCode.h"
#include "util.h"
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

Row::Row(void):key(NULL),keySize(0){

}

Row::Row(const char* key,int keySize){
	this->key=const_cast<char*>(key);
	this->keySize=keySize;
}

Row::~Row(void){
	
}

PCHAR& Row::getKey(void)
{
	return this->key;
}

int Row::getKeySize(void)
{
	return this->keySize;
}

void Row::set(const char* key,int keySize)
{
	this->key=const_cast<char*>(key);
	this->keySize=keySize;
}

bool DataRow::isOfRow(void){
		assert(this->vSize>=this->curSize);
		assert((this->ofPageNo > 0 ?true : false) && (this->vSize > this->curSize ? true : false));

		if(this->ofPageNo > 0)
			return true;
		return false;
	}
/*精确计算*/
int DataRow::getSize(void){
	int size=0;
	if(this->space!=0)
		return this->space;
	size+=DEFAULT_KEY_SIZE_DISK + this->getKeySize() +vCode::getVariableSize(this->vSize) + vCode::getVariableSize(this->curSize);
	if(this->ofPageNo>0)//ofRow
		size+=DEFAULT_PAGE_SIZE;//DataRow-->ofPage
	this->space=size;
	return size;
}
char* DataRow::getValue(void)
{
	return this->value;
}

Value DataRow::getCloneValue(void)
{
	return Value(this->value,this->curSize);
}

Value DataRow::getCloneAllValue(PageManager* pageManager)
{
	PageNo ofPageNo;
	int copyPos=0;//当前要拷贝到的位置
	Value v(NULL,0);
	if(isOfRow()){
		char* ch=(char*)malloc(sizeof(char) * this->vSize);
		if(ch==NULL)
			goto OVER;
		memcpy(ch,this->value,this->curSize);
		copyPos+=this->curSize;
		//接下来拷贝OfPage中的内容
		ofPageNo=this->getOfPageNo();
		while(ofPageNo > 1){
			OfPage* ofPage=static_cast<OfPage*>(pageManager->getPage(this->ofPageNo));
			assert(ofPage);
			if(ofPage==NULL) goto ERROR;
			OfRow* ofRow=static_cast<OfRow*>(ofPage->getRow());
			if(ofRow==NULL) goto ERROR;
			memcmp(ch + copyPos,ofRow->getKey(),ofRow->getKeySize());
			copyPos += ofRow->getKeySize();
			ofPageNo=ofPage->getNPageNo();
		}
		assert(copyPos==this->vSize);//验证一下读取的和vSize是否一致
		if(copyPos!=this->vSize){
			//数据读取不完整。		
		}
		v.set(ch,this->getVSize());
		goto OVER;
ERROR:
		if(ch!=NULL)
			free(ch);
	}
	else{
		v.set(this->value,this->curSize);
	}
OVER:
	return v;

}
/*
		DataRow:
		 keySize  |1 byte
		 key	  |
		 valueSize|variableCode
	   curValueSize|variableCode(有可能存在，只有当溢出时，才存在)
		 ovPage   |4 byte（有可能不存在，只有当溢出时才存在）
*/
int DataRow::writeBuffer(char* pageBuffer,int offset)
{
	int i;
	assert(pageBuffer);
	///////////KEY/////////////////
	pageBuffer[offset]=(uint8_t)this->getKeySize();
	offset+=1;//keySize
	memcpy((void*)(pageBuffer[offset]),this->getKey(),this->getKeySize());
	offset+=this->getKeySize();//key
	//////////VALUE///////////////
	i=vCode::vCodei32(this->vSize,pageBuffer+offset);
	offset+=i;//valueSize
	memcpy(pageBuffer+offset,this->value,this->curSize);
	offset+=this->curSize;//
	////////OfPageNo/////////////
	if(this->isOfRow()){
		setU32(pageBuffer,offset,this->ofPageNo);
		offset+=4;
	}

	return 1;
}

int DataRow::parse(DataRow*& row,const char* dataBuffer,int& offset,int endOffset){

		uint8_t keySize;
		char* pKey;
		assert(dataBuffer);
		keySize=*(uint8_t*)(dataBuffer+offset);offset+=1;
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
				uint64_t i=0;
				int vSize;//variableCode size
				int x;
				memcpy(pKey,dataBuffer+offset,keySize);
				if(row==NULL)
					row=new DataRow();
				row->set(pKey,keySize);

				offset+=keySize;
				vSize=vCode::getVariableCode(dataBuffer+offset,i);//vcode 占的空间
				ASSERT_VCODE_SIZE(vSize);

				offset+=vSize;
				assert(i>0 && i<MAX_VALUE_SIZE);
				assert(endOffset>offset);
				x=endOffset-offset;

				if(x==i){//说明没有溢出
					char* v=(char*)malloc((sizeof(char)*(size_t)i));
					if(v==NULL){
						return PTE_MEMORY;
					}
					/*row->value=v;row->vSize*/
				}
				else if(x>i){//说明溢出

				}
				else if(x<i){
					//error
				}
			}
		}
		return PFE_SUCESS;
	}