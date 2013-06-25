#include "const.h"
#include "PageCache.h"
#include <stddef.h>

PageCache::PageCache(void)
{
	this->pageHash=new vHash(HT_INT);
	this->pageList=new DList<PPage>();
}


PageCache::~PageCache(void)
{
}

int PageCache::addPage(PPage page)
{
	return 1;
}

PPage PageCache::getPage(PageNo pageNo)
{
	HashKey hashKey;void* p;
		int offset=0;
		PPage page=NULL;
		/*if(pageNo==0)
			return this->getRootPage();*/
		hashKey.iKey=pageNo;
		p=this->pageHash->get(hashKey);
		if(p){
			return (PPage)p;
		}
		else if(this->db->getPageCount() > pageNo){
			char readBuffer[DEFAULT_PAGE_SIZE]={'\0'};
			if(db->getDbFile()->read(readBuffer,pageNo * DEFAULT_PAGE_SIZE,DEFAULT_PAGE_SIZE)==1){
				//read data sucess
				//page=PageParser::parse(readBuffer,offset);

			}
			else{
				//Error
			}
		}
		return NULL;
}

int PageCache::delPage(PPage page)
{
	return 1;
}

PPage PageCache::newPage(PageType pageType)
{
	PPage page=NULL;
	if(pageType==PT_LEAF)
	{
		page=new LeafPage();
	}
	else if(pageType==PT_INDEX){
		page=new IndexPage();
	}
	else if(pageType==PT_OF){
		page=new OfPage();
	}
	if(page!=NULL){
		int pageCount=db->getPageCount();
		page->setPageNo((PageNo)++pageCount);
		return page;
	}
	return NULL;
}