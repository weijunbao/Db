#include "PageState.h"


PageState::PageState(PageNo pageNo,uint16_t rowCount,uint16_t freeSpace)
{
	this->pageNo=pageNo;
	this->rowCount=rowCount;
	this->freeSpace=freeSpace;
}


PageState::~PageState(void)
{
}

PageNo PageState::getHashCode(void)
{
	return this->pageNo;
}