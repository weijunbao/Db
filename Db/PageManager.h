#pragma once
#include "Page.h"
#include "PageCache.h"
#include <stdio.h>
class PageCache;
class Page;
/*
นÜภํว๘าณ
*/
class PageManager
{
public:
	PageManager(void);
	~PageManager(void);
public:
	PPage newPage(PageType pageType);
	PPage readPage(PageNo);
	PPage getPage(PageNo pageNo);
	int writePage(PageNo pageNo,const char* pageBuffer);
private:
	PPage FreePage;
	PageCache* pageCache;
	FILE dbFile;
};