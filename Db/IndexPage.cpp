#include "const.h"
#include "Page.h"
#include "util.h"
#include "vCode.h"
#include "StringUtils.h"
#include <assert.h>

int IndexPage::getFreeSpace(void)
{
	if(this->rows.getSize()==0){
			return DEFAULT_PAGE_FREE_SPACE;
	}
	else{
		if(this->freeSpace==DEFAULT_PAGE_FREE_SPACE || this->reCalculate){
			//重新计算.粗略计算，非精确计算
			int i;int usedSpace=0;int _freeSpace=0;
			for(i=0;i<this->rows.getSize();i++){
				usedSpace+=this->rows.get((uint16_t)i)->getSize();
			}
			// * 2:2是最大的record position
			_freeSpace=DEFAULT_PAGE_FREE_SPACE - usedSpace - this->rows.getSize() * 2 -PAGE_NO_SIZE;//IndexPage::n
			assert(_freeSpace>0);
			this->freeSpace=_freeSpace;
			this->reCalculate=false;
		}
		return this->freeSpace;
	}
}

int IndexPage::getPageSpace(void)
{
	int pageSpace=0;
	for(int i=0;i<this->rows.getSize();i++){
		pageSpace+=this->rows.get((uint16_t)i)->getSize();
	}
	return pageSpace;
}

int IndexPage::writeBuffer(char* pageBuffer,int offset)
{
	int i;
	assert(pageBuffer);
	assert(this->getRows().getSize()>0);
	setU32(pageBuffer,offset,this->pageNo);
	offset+=4;//pageNo
	pageBuffer[offset]=this->getPageType();
	offset+=1;//pageType

	//records   | 1 byte		| 1 byte	修正为：变长编码。因为1byte未必够
	i=vCode::vCodei32((uint32_t)this->rows.getSize(),pageBuffer+offset);
	offset+=i;

	if(this->rows.getSize() > 0){
	
	}

	return 1;
}
/*写的不对:
because PageNo n;//left.
*/
int IndexPage::insertRow(Row* row,int index)
{
	/*约定:把 需要分裂的LeafPage*/
	IndexRow* indexRow=dynamic_cast<IndexRow*>(row);
	assert(indexRow);

	this->rows.insert(index,row);
	freeSpace=this->getFreeSpace();
	if(freeSpace > indexRow->getSize()){
		this->freeSpace=this->freeSpace - indexRow->getSize();
		this->rows.insert(index,row);
	}
	else{
		//split page
		this->rows.insert(index,row);
		return PAGE_OP_SPLIT;
	}
	this->reCalculate=true;//强行设置，重新计算
	return 1;
}

int IndexPage::removeRow(int index)
{
	assert(index>=0 && index<this->rows.getSize());
	int r=this->rows.remove(index);
	if(r){
		this->setReCalculate(true);
	}
	return r;
}

int IndexPage::assertRowOrder(void)
{
	return 1;
}
/*不用解析 PageIndex(PageNo),PageType,因为已经在PageParser解析了。直接从records处开始解析*/
int IndexPage::parse(PIndexPage& page,const char* dataBuffer,int& offset)
{
	int off;
	int rows;PageNo pageNo;
	assert(dataBuffer);
	off=offset;

	/*
		index page:
		pageIndex | 固定4个字节 | 4 byte
		pageType  | 4 bit		| 1 byte
		records   | 1 byte		| 1 byte	修正为：变长编码。因为1byte未必够
		
		依次排列
		Ptr(0) | Keysize--Key(0) | Ptr(1)
		Key(0)<Key(1)<Key(2)
	*/
	rows=getU16(dataBuffer,offset);off+=2;
	
	while (rows > 0)
	{

	}
	offset=off;
	return PFE_SUCESS;
PARSE_ERROR:
	return 1;
}

bool IndexPage::findPosition(Row* row,int& rv)
{
	return 1;
}
/*
查找插入位置
rv:0<=rv<=n. if rv=n,就是add operate
*/
bool IndexPage::findPosition(Value key,int& rv)
{
	int startIndex,endIndex,middleIndex;
	bool isBigger=false;
	endIndex=startIndex=0;
	middleIndex=rows.getSize()-1;
	
	while(true){
		int i=0;IndexRow* indexRow=NULL;
		if(startIndex>endIndex){
				if(isBigger)
					rv=middleIndex;
				else
					rv= middleIndex+1;
				return false;
		}
		middleIndex=startIndex + (endIndex - startIndex)/2;
		indexRow=dynamic_cast<PIndexRow>(rows.get(i));
		assert(indexRow);
		i=StringUtils::compare(key.getData(),key.getSize(),indexRow->getKey(),indexRow->getKeySize());
		if(i>0){
			endIndex=middleIndex-1;
			isBigger=true;
		}
		else if(i==0){
			rv=middleIndex;
			break;
		}
		else{
			startIndex=middleIndex+1;
			isBigger=false;
		}
	}
	return true;
}

int IndexPage::spaceRate(void)
{
	return 50;
}