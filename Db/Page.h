#pragma once

#include "commontype.h"
#include "vector.h"
#include "DataRow.h"
#include "Value.h"
#include <stdint.h>

class Row;
class PageManager;

typedef class Page* PPage;
typedef class LeafPage* PLeafPage;
typedef class IndexPage* PIndexPage;
typedef class OfPage* POfPage;

enum PageFormatError{
		PFE_SUCESS,
		PFE_PAGETYPE,//不存在的pageType
		PTE_MEMORY,//内存不足
		PTE_KEYSIZE_ZERO,//keysize=0
		PTE_KEYSIZE_MAX,//keysize 超了
		PFE_ERROR
	};
/*
abstract class
*/
class Page :
	public NonCopyable , public Object
{
public:
	Page(void);
	~Page(void);
public:
	PageNo getPageNo(void);
	void setPageNo(PageNo);
	PPage getParentPage(void){
		return this->parentPage;
	}
	PageNo getParentPageNo(void){
		return this->parentPageNo;
	}
	PageType getPageType(void);
	void setPageType(PageType pageType);
	virtual int getFreeSpace(void)=0;
	virtual int getPageSpace(void)=0;
	virtual int writeBuffer(char* pageBuffer,int offset)=0;

	virtual bool findPosition(Row* row,int& rv)=0;
	virtual bool findPosition(Value key,int& rv)=0;
	virtual int spaceRate(void)=0;//页的空间利用率
	virtual vector<Row*> getRows(void)=0;

	void setReCalculate(bool b);
	
protected:
	PageNo pageNo;
	PageType pageType;
	uint8_t dirty;
	int freeSpace;
	uint16_t recordCount;
	PPage parentPage;//不会存在磁盘里。NULL :root page
	PageNo parentPageNo;
	bool reCalculate;//是否重新计算freeSpace
};

class LeafPage :
	public Page
{
public:
	int addRow(Row* row);
	int insertRow(PageManager* pageManager,Row* row,int index);
	int removeRow(int index);
	int getFreeSpace(void);
	int getPageSpace(void);
	int writeBuffer(char* pageBuffer,int offset);
	static int parse(PLeafPage& page,const char* dataBuffer,int& offset);

	bool findPosition(Row* row,int& rv);
	bool findPosition(Value key,int& rv);
	int spaceRate(void);

	int assertRowOrder(void);
	vector<Row*> getRows(void){
		return this->rows;
	}
private:
	vector<Row*> rows;
	PageNo npn;//next pageNo
};
class IndexPage :
	public Page
{
public:
	int insertRow(Row* row,int index);
	int removeRow(int index);
	int getFreeSpace(void);
	int getPageSpace(void);
	int writeBuffer(char* pageBuffer,int offset);
	static int parse(PIndexPage& page,const char* dataBuffer,int& offset);

	bool findPosition(Row* row,int& rv);
	bool findPosition(Value key,int& rv);
	int spaceRate(void);

	int assertRowOrder(void);
	vector<Row*> getRows(void){
		return this->rows;
	}
	PageNo getLeftPageNo(void){
		return this->n;
	}
private:
	vector<Row*> rows;
	PageNo n;//left
};

class OfPage :
	public Page{
public:
	int getFreeSpace(void);
	int getPageSpace(void);
	int writeBuffer(char* pageBuffer,int offset);
	static int parse(POfPage& page,const char* dataBuffer,int& offset);
	Row* getRow(void){
		return this->row;
	}
	PageNo getNPageNo(void){
		return this->nPage;
	}
	bool findPosition(Row* row,int& rv){return false;}
	bool findPosition(Value key,int& rv){return false;}
	int spaceRate(void){return 0;}
	vector<Row*> getRows(void){return 0;}

private:
	Row* row;
	PageNo nPage;//next overflow page
};
#include "PageManager.h"