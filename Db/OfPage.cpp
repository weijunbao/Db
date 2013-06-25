#include "const.h"
#include "vCode.h"
#include "Page.h"
#include <assert.h>

int OfPage::getFreeSpace(void)
{
	return DEFAULT_PAGE_SIZE - PAGE_NO_SIZE*2 - PAGE_TYPE_SIZE - this->row->getKeySize() + vCode::getVariableSize(this->row->getKeySize());
}

int OfPage::getPageSpace(void)
{
	return 0;
}

int OfPage::writeBuffer(char* pageBuffer,int offset)
{
	assert(pageBuffer);
	int freeSpace=this->getFreeSpace();
	if(freeSpace>0){//说明一个溢出页就够了

	}
	else{//write到N个溢出页
		int r=this->row->getKeySize();
		
	}
	return 1;
}