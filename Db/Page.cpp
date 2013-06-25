#include "Page.h"


Page::Page(void)
{
}


Page::~Page(void)
{
}

PageNo Page::getPageNo(void)
{
	return this->pageNo;
}

void Page::setPageNo(PageNo pageNo)
{
	this->pageNo=pageNo;
}

PageType Page::getPageType(void)
{
	return this->pageType;
}

void Page::setReCalculate(bool b)
{
	this->reCalculate=b;
}