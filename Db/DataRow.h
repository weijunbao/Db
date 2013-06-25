#pragma once
#include "commonType.h"
#include "Page.h"
#include "Value.h"
#include <stdint.h>
#include <memory.h>

class PageManager;
typedef char* PCHAR;
typedef class OfRow* POfRow;
typedef class DataRow* PDataRow;
typedef class IndexRow* PIndexRow;
typedef class Row* PRow;

class Row :
	public NonCopyable,public Object{
public:
	Row();
	Row(const char* key,int keySize);
	~Row();
public:
	PCHAR& getKey(void);
	int getKeySize(void);
	void set(const char* key,int keySize);
	virtual int getSize(void)=0;
	virtual int writeBuffer(char* pageBuffer,int offset)=0;
private:
	PCHAR key;
	int keySize;
};


/*
叶子节点的数据
*/
class DataRow :
	public Row{
private:
	char* value;
	uint16_t curSize;//current size of the row
	uint16_t vSize;// all size
	PageNo ofPageNo;//溢出页
	int space;//占用空间
public:
	DataRow(){}
	DataRow(const char* pKey,const int keySize,const char* pValue,const int vSize)
		:Row(pKey,keySize){
			this->value=new char[vSize];
			memcmp(this->value,pValue,vSize);
			this->vSize=vSize;
	}
	~DataRow(){
		delete this->value;
	}
	uint16_t getcurSize(void){
		return this->curSize;
	}
	void setcurSize(uint16_t curSize){
		this->curSize=curSize;
	}
	void setofPageNo(PageNo pageNo){
		this->ofPageNo=pageNo;
	}
	PageNo getOfPageNo(void){
		return this->ofPageNo;
	}
	void setVSize(uint16_t vSize){
		this->vSize=vSize;
	}
	uint16_t getVSize(void){
		return this->vSize;
	}
	void setValue(char* value){
		this->value=value;
	}
	static int parse(PDataRow& row,const char* dataBuffer,int& offset,int endOffset);
	int writeBuffer(char* pageBuffer,int offset);
	bool isOfRow(void);
	/*落到磁盘上占用的空间*/
	int getSize(void);
	char* getValue(void);//得到当前的value
	//char* getAllValue(PageManager* pageManager);//得到所有的value，包括OfPageNo中的value
	//返回客户端时调用，不一定合理。
	Value getCloneValue(void);
	Value getCloneAllValue(PageManager* pageManager);
};

/*
索引节点的数据
*/
class IndexRow :
	public Row{
public:
	static int parse(PIndexRow& row,char* dataBuffer,int& offset);
	int writeBuffer(char* pageBuffer,int offset);
	int getSize(void);
	PageNo getPageNo(void){
		return this->pageNo;
	}
private:
	PageNo pageNo;
};

class OfRow :
	public Row{
public:
	OfRow(){
	}
	OfRow(const char* key,int keySize):Row(key,keySize){
	
	}
	virtual int getSize(void);
	virtual int writeBuffer(char* pageBuffer,int offset);
	static int parse(POfRow& row,char* dataBuffer,int& offset);
};