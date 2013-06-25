#pragma once
#include "Value.h"
#include "Page.h"
#include "PageManager.h"
#include "DbFile.h"
#include "PageStateManager.h"


typedef class Db* PDB;
class PageManager;
class PageStateManager;


class DbHeader{
	int i;
};
class Db
{
public:
	Db(void);
	Db(const char* dir);
	~Db(void);
public:
	int insert(Value key,Value value);
public:
	PPage getRootPage(void);
	void setRootPage(PPage);
	PageNo getPageCount(void);
	void setPageCount(PageNo pageNo);
	PFile getDbFile(void);

	PageManager* getPageManager(void){
		return this->pageManager;
	}
	PageStateManager* getPageStateManager(void){
		return this->pageStateManager;
	}
	int getPageSize(){
		return this->pageSize;
	}
private:
	PageNo leftmostPageNo;//����ߵ�ҳ.
	PageNo rightmostPageNo;//���ò�Ʋ���Ҫ��
	Value leftmostValue;//����ߵ�ֵ
	Value rightmostValue;//���ұߵ�ֵ
	int pageSize;
	int pageCount;
	PFile dbFile;
	PPage rootPage;
	PageManager* pageManager;
	PageStateManager* pageStateManager;
};

