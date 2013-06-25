#include "PageManager.h"


PageManager::PageManager(void)
{
	/*PPage FreePage;
	PageCache* pageCache;
	FILE dbFile;*/
	this->FreePage=NULL;
	this->pageCache=new PageCache();

}


PageManager::~PageManager(void)
{
}

PPage PageManager::newPage(PageType pageType)
{
	return NULL;
}

PPage PageManager::readPage(PageNo pageNo)
{
	return NULL;
}

int PageManager::writePage(PageNo pageNo,const char* pageBuffer)
{
	return 1;
}

PPage PageManager::getPage(PageNo pageNo)
{
	return NULL;
}