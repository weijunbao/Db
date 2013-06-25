#pragma once
#include "commonType.h"
#include "Page.h"
class PageState :
	public IHashCode<PageNo>
{
public:
	PageState(PageNo pageNo,uint16_t rowCount,uint16_t freeSpace);
	~PageState(void);
	PageNo getHashCode(void);
private:
	PageNo pageNo;
	uint16_t rowCount;
	uint16_t freeSpace;
};

