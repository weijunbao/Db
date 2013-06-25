#include "const.h"
#include "util.h"
#include "Page.h"
#include "vCode.h"
#include "StringUtils.h"
#include <assert.h>
#include <malloc.h>
#include <memory.h>
/*
	ǰ�᣺
		���뱣֤һ��ҳ������2����¼
	����ж�����:
		a. value ����ҳ��2/3 OF_VALUE_SIZE�����������
		b. value > ҳ��һ��ʱ and < OF_VALUE_SIZE ������ҳ�ڿռ�������ٿ����Ƿ������
		c.С��ҳ��1/2ʱ���������
	*/
#define ASSERT_FREE_SPACE\
	assert(this->freeSpace >=DEFAULT_PAGE_FREE_SPACE);

int LeafPage::getFreeSpace(void){
	if(this->rows.getSize()==0){
		return DEFAULT_PAGE_FREE_SPACE;
	}
	else{
		if(this->freeSpace==0 || this->reCalculate){
			//���¼���.���Լ��㣬�Ǿ�ȷ����
			int i;int usedSpace=0;int _freeSpace=0;
			for(i=0;i<this->rows.getSize();i++){
				usedSpace+=this->rows.get((uint16_t)i)->getSize();
			}
			// * 2:2������record position
			_freeSpace=DEFAULT_PAGE_FREE_SPACE - usedSpace - this->rows.getSize() * 2 ;
			assert(_freeSpace>0);
			this->freeSpace=_freeSpace;
			return _freeSpace;
		}
		else{
			return this->freeSpace;
		}
	}
}

/*��������key valueռ�õĿռ�*/
int LeafPage::getPageSpace(void)
{
	int pageSpace=0;
	for(int i=0;i<this->rows.getSize();i++){
		pageSpace+=this->rows.get((uint16_t)i)->getSize();
	}
	return pageSpace;
}

int LeafPage::writeBuffer(char* pageBuffer,int offset){
		int i;int rearOffset;//int nOffset;//next offset
		
		assert(pageBuffer);
		rearOffset=offset+DEFAULT_PAGE_SIZE-4;//4:last four byte
		setU32(pageBuffer,offset,this->pageNo);
		offset+=4;//pageNo
		pageBuffer[offset]=this->getPageType();
		offset+=1;//pageType
		
		//records   | 1 byte		| 2 byte
		i=vCode::vCodei32((uint32_t)this->rows.getSize(),pageBuffer+offset);
		offset+=i;

		for(i=0;i<this->rows.getSize();i++){
			int size=0;
			Row* dataRow=this->rows.get(i);

			assert(dataRow);
			size=dataRow->getSize();
			dataRow->writeBuffer(pageBuffer,rearOffset-size);//�˴�ֻ����һ���ط�д��ERROR
		}

		setU32(pageBuffer, offset+DEFAULT_PAGE_SIZE -4,this->npn);//next page last four byte

		return 1;
}

/*
parse ʱר��
*/
int LeafPage::addRow(Row* row){
	return this->rows.add(row);
}
/**/
int LeafPage::insertRow(PageManager* pageManager,Row* row,int index)
{
	int rowSize=0;bool isOfRow;int freeSpace;
	DataRow* dataRow=NULL;
	dataRow=static_cast<DataRow*>(row);
	assert(dataRow);
	isOfRow=dataRow->isOfRow();
	if(dataRow->getVSize() > DEFAULT_PAGE_SIZE *(2/3) && !isOfRow){//if not ofRow,overflow
		char* ofValue;char* minValue;
		OfRow* ofRow=NULL;
		OfPage* ofPage=(OfPage*)(pageManager->newPage(PT_OF));
		assert(ofPage);
		if(ofPage==NULL)
			return 0;
		ofValue=(char*)malloc(dataRow->getVSize()-MIN_VALUE_SIZE);
		minValue=(char*)malloc(MIN_VALUE_SIZE);
		if(ofValue==NULL && minValue==NULL)
			goto ERROR;
		memcpy(ofValue,dataRow->getValue() + MIN_VALUE_SIZE,dataRow->getVSize() - MIN_VALUE_SIZE);
		memcpy(minValue,dataRow->getValue(),MIN_VALUE_SIZE);

		ofRow=new OfRow(ofValue,dataRow->getVSize()-MIN_VALUE_SIZE);
		/*ofPage->value=ofValue;
		ofPage->vSize=dataRow->getVSize()-MIN_VALUE_SIZE;*/
		dataRow->setofPageNo(ofPage->getPageNo());
		dataRow->setcurSize(MIN_VALUE_SIZE);
		dataRow->setValue(minValue);

ERROR:
		if(ofValue!=NULL)
			free(ofValue);
		if(minValue!=NULL)
			free(minValue);

		return 0;
	}
	freeSpace=this->getFreeSpace();
	if(freeSpace > dataRow->getSize()){
		this->freeSpace=this->freeSpace - dataRow->getSize();
		//this->rows.add(dataRow);
		this->rows.insert(index,row);
	}
	else{
		//splite page
		//this->rows.add(dataRow);
		this->rows.insert(index,row);
		return PAGE_OP_SPLIT;
	}
	this->reCalculate=true;//ǿ�����ã����¼���
	return 1;
}

int LeafPage::removeRow(int index)
{
	assert(index>=0 && index<this->rows.getSize());
	if(this->rows.getSize()==0)
			return 0;
		DataRow* row=NULL;
		row=static_cast<DataRow*>(rows.get(index));
		if(row==NULL)
			return 0;
		this->freeSpace-=row->getSize();
		ASSERT_FREE_SPACE
		return this->rows.remove(index);
}

/*���ý��� PageIndex(PageNo),PageType,��Ϊ�Ѿ���PageParser�����ˡ�ֱ�Ӵ�records����ʼ����*/
int LeafPage::parse(PLeafPage& page,const char* dataBuffer,int& offset)
{
		int i;
		int rows;
		uint32_t npn;//next pageNo
		int preRowOffset;
		int off=offset;
		assert(dataBuffer);
		/*
		pageIndex | �̶�4���ֽ� | 4 byte
		pageType  | 4 bit		| 1 byte
		records   | 1 byte		| 2 byte
		*/
		//��records��ʼ����
		rows=getU16(dataBuffer,offset);offset+=2;
		npn=getU32(dataBuffer,offset);offset+=4;	//�������󣬲ο�KvDB.txt
		preRowOffset=DEFAULT_PAGE_SIZE-4;
		for(i=0;i<rows;i++){
			int nbytes;
			int parseState;
			uint64_t rowOffset;
			DataRow* dataRow=NULL;
			nbytes=vCode::getVariableCode(dataBuffer+offset,rowOffset);
			assert(rowOffset < DEFAULT_PAGE_SIZE);
			offset+=nbytes;
			parseState=DataRow::parse(dataRow,dataBuffer,offset,preRowOffset);
			if(parseState!=PFE_SUCESS){
				if(dataRow!=NULL) delete dataRow;
				if(page!=NULL) delete page;
				return parseState;
			}
			else{
				if(page==NULL)
					page=new LeafPage();
				
				page->addRow(dataRow);
			}
		}
		return PFE_SUCESS;
PARSE_ERROR:
		return 1;
}

/*
check row is order
*/
int LeafPage::assertRowOrder(void)
{
	return 1;
}

bool LeafPage::findPosition(Row* row,int& rv)
{
	return 1;
}

bool LeafPage::findPosition(Value key,int& rv)
{
	int startIndex,endIndex,middleIndex;
	bool isBigger=false;
	startIndex=endIndex=0;
	middleIndex=rows.getSize()-1;
	
	while(true){
		int i=0;DataRow* dataRow=NULL;
		if(startIndex>endIndex){
				if(isBigger)
					rv=middleIndex;
				else
					rv= middleIndex+1;
				return false;
		}
		middleIndex=startIndex + (endIndex - startIndex)/2;
		dataRow=dynamic_cast<PDataRow>(rows.get(i));
		assert(dataRow);
		i=StringUtils::compare(key.getData(),key.getSize(),dataRow->getKey(),dataRow->getKeySize());
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

int LeafPage::spaceRate(void)
{
	return 50;
}