#include "Db.h"
#include "const.h"
#include <assert.h>

enum PageSize{
	PageSize_512,
	PageSize_1024
};

Db::Db(void)
{
	this->pageManager=new PageManager();
	this->pageStateManager=new PageStateManager();
	
}

Db::Db(const char* dir)
{
	assert(dir);
	if(dir==NULL){
		this->dbFile=new CFile(dir);
	}
	else{
	
	}
}

Db::~Db(void)
{
}


PPage Db::getRootPage(void)
{
	return this->rootPage;
}

void Db::setRootPage(PPage page)
{
	assert(page);
	this->rootPage=page;
}

PFile Db::getDbFile(void)
{
	return this->dbFile;
}

PageNo Db::getPageCount(void)
{
	return this->pageCount;
}

void Db::setPageCount(PageNo pageCount)
{
	this->pageCount=pageCount;
}

int Db::insert(Value key,Value value)
{
	
	return 1;
}