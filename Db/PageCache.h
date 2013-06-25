#pragma once
#include "commonType.h"
#include "Db.h"
#include "vHash.h"
#include "DList.h"
class Db;
class PageCache:
	public NonCopyable
{
public:
	PageCache(void);
	~PageCache(void);
public:
	int addPage(PPage page);
	PPage getPage(PageNo pageNo);
	int delPage(PPage page);
	PPage newPage(PageType pageType);
private:
	vHash* pageHash;
	DList<PPage>* pageList;
	Db* db;
};

