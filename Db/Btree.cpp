#include "const.h"
#include "commonType.h"
#include "String.h"
#include "Btree.h"
#include <stddef.h>
#include <assert.h>
#include <string.h>



BtreeCursor VAILD_CURSOR={ -1,0,0};
#define PageCache
Btree::Btree(void)
{
}

Btree::~Btree(void)
{
}

BtreeCursor Btree::search(Value key)
{
	BtreeCursor bc;
		PPage pPage;
		PPage curPage;
		int level=0;
		curPage=pPage=NULL;
		
		curPage=this->db->getRootPage();
		assert(curPage);
		assert(curPage->getPageNo()==1);
		
		/*while(curPage->getPageType()==PT_INDEX){
			int startIndex,endIndex,middleIndex;
			bool isLess=false;
			IndexPage* indexPage=dynamic_cast<IndexPage*>(curPage);
			assert(indexPage);
			startIndex=0;
			endIndex=indexPage->getRows().getSize();
			level+=1;
			for(;;){
				int result;
				IndexRow* row=NULL;
				if(startIndex>endIndex){
					int i;
					if(isLess) i=endIndex;
					else i=startIndex;
					pPage=curPage;
					if(i==-1)
						curPage=db->getPageManager()->getPage(indexPage->getPageNo());
					else
						curPage=db->getPageManager()->getPage(indexPage->getRows().get(i)->getPageNo());
					assert(curPage);
					break;
				}
				middleIndex=startIndex+(endIndex-startIndex)/2;
				row=indexPage->.get(middleIndex);
				assert(row);
				result=this->compareValue(pKey,keySize,row->getKey(),row->getKeySize());
				if(result>0){
					startIndex=middleIndex+1;
					isLess=false;
				}
				else if(result==0){
					pPage=curPage;
					curPage=this->db->getPageManager()->getPage(row->getPageNo());
					assert(curPage);
				}
				else{
					endIndex=middleIndex-1;
					isLess=true;
				}
			}
		}*/
		
		if(level==0)
			bc.set(level,curPage->getPageNo(),0);
		else
			bc.set(level,curPage->getPageNo(),pPage->getPageNo());
	return bc;
}

int Btree::insert(Value key,Value value)
{
	int insertIndex;
	bool isExisted=false;
	BtreeCursor btreeCursor;
	PPage parentPage,curPage;
	assert(key.getData());
	assert(key.getSize()<=MAX_KEY_SIZE);
	assert(value.getData());
	assert(value.getSize()<=MAX_VALUE_SIZE);
	btreeCursor=search(key);
	if(btreeCursor.isValid())
		return 0;
	parentPage=curPage=NULL;
	parentPage=db->getPageManager()->getPage(btreeCursor.pPage);
	curPage=db->getPageManager()->getPage(btreeCursor.page);
	assert(curPage!=NULL);
	assert(curPage->getPageType()==PT_LEAF);
	{
		//search
		PLeafPage leafPage=static_cast<PLeafPage>(curPage);
		assert(leafPage);
		/*> 3,binarySearch*/
		if(leafPage->getRows().getSize() > 3){
			
		}
		else{
			for(int i=0;i<leafPage->getRows().getSize();i++){
				int cmpValue=0;
				DataRow* dataRow=static_cast<DataRow*>(leafPage->getRows().get(i));
				assert(dataRow);
				cmpValue=String::cmpcase(dataRow->getKey(),dataRow->getKeySize(),key.getData(),key.getSize());
				if(cmpValue > 0){
					insertIndex=i=1;
					break;
				}
				else if(cmpValue==0){
					isExisted=true;
					break;
				}
			}
		}
		if(isExisted){
			goto EXIST;
		}

		{
			int rv=0;
			//insert
			DataRow* dataRow=new DataRow(key.getData(),key.getSize(),value.getData(),value.getSize());
			rv=leafPage->addRow(dataRow);
			if(rv==PAGE_OP_SPLIT){
				this->split(leafPage);
			}
		}
	}
	
	return Success;
EXIST:
	return Failure;
}

int Btree::split(PLeafPage leafPage)
{
	int pageSpace,i,x;
	int halfSize=0;
	
	PLeafPage newChildPage;
	PIndexPage parentPage=dynamic_cast<PIndexPage>(this->db->getPageManager()->getPage(leafPage->getParentPageNo()));
	assert(leafPage);
	newChildPage=static_cast<PLeafPage>(this->db->getPageManager()->newPage(PT_LEAF));
	pageSpace=leafPage->getPageSpace();

	for(i=0;i<leafPage->getRows().getSize() && halfSize > pageSpace /2 ;i++){
		halfSize+=leafPage->getRows().get(i)->getSize();
	}
	x=i;//save variable i
	//先简单的处理
	assert(i < leafPage->getRows().getSize());//i必须小于row.size，要不没有新的datarow，可被写入newChildPage
	for(;i<leafPage->getRows().getSize();){
		leafPage->removeRow(i);
		newChildPage->addRow(leafPage->getRows().get(i));
	}
	//再次验证一下Page.getFreeSpace.看split的是否正确
	assert(leafPage->getFreeSpace() > 0);
	assert(newChildPage->getFreeSpace() >0);
	
	{
		int index=0;
		DataRow* dataRow=static_cast<DataRow*>(leafPage->getRows().get((uint16_t)x));
		IndexRow* indexRow=new IndexRow();
		indexRow->set(dataRow->getKey(),dataRow->getKeySize());//这些得重新考虑，是malloc啊，还是直接指针
		//查找indexRow应该插入的位置
		if(parentPage->getRows().getSize() > 3){
			
		}
		else{
		
		}
		if(parentPage->insertRow(indexRow,index)==PAGE_OP_SPLIT){
			split(parentPage);
		}
	}

	return Success;
ERROR:
	return Failure;
}

int Btree::split(PIndexPage indexPage)
{
	assert(indexPage);


	return 1;
}

int Btree::merge(PPage pPage,int index)
{
	return 1;
}

int Btree::update(const Value key,const Value value)
{
	return 1;
}
int Btree::remove(Value key)
{
	PPage pPage=NULL;
	assert(key.getData());
	assert(key.getSize()<=MAX_KEY_SIZE);
	
	return remove(db->getRootPage(),key);
}

int Btree::remove(PPage pPage,const Value key)
{
	bool b;
	int rvIndex=0;
	assert(pPage);

	b=pPage->findPosition(key,rvIndex);


	
	if(b){//查到了.只有查找到了，并删除了，才会进行balance
		if(pPage->getPageType()==PT_LEAF){
			PLeafPage leafPage=dynamic_cast<PLeafPage>(pPage);
			leafPage->removeRow(rvIndex);
			
			if(leafPage->getFreeSpace() < 12){
			
			}
		}
		else if(pPage->getPageType()==PT_INDEX)
		{
			//在IndexPage中查到了此Key

		}
		else
			assert(0);
	}
	else{
		if(pPage->getPageType()==PT_LEAF){
			//没有找到
			return 1;
		}
		else if(pPage->getPageType()==PT_INDEX)
		{
			PageNo childPageNo;
			
			PIndexPage indexPage=dynamic_cast<PIndexPage>(pPage); assert(indexPage);
			if(rvIndex==0){
				childPageNo=indexPage->getLeftPageNo();
			}
			else if(rvIndex >= indexPage->getRows().getSize()-1){
				childPageNo= dynamic_cast<IndexRow*>(indexPage->getRows().get(indexPage->getRows().getSize()-1))->getPageNo();
			}
			assert(childPageNo > 1);
			return this->remove(this->db->getPageManager()->getPage(childPageNo),key);
		}
		else
		{
			assert(0);
		}
	}
	return 1;
}
/*
	@parentPage
	@curPage
	@index,curPage 在parentPage中的索引
*/
BalanceRuleType Btree::trybalance(PPage parentPage,PPage curPage,int index)
{
	PPage prePage,nextPage=NULL;
	int freeSpaceOfcurPage,freeSpaceOfPrePage,freeSpaceOfNextPage;
	int spaceRateOfcurPage;
	assert(parentPage);
	assert(curPage);
	assert(parentPage->getPageType()==PT_INDEX);

	spaceRateOfcurPage=curPage->spaceRate();
	
	if(spaceRateOfcurPage > 70){
		//此时不需要balance
		return BRT_NOT;
	}
	else if(spaceRateOfcurPage < 10){
		//强行balance
		return BRT_Mandatory;
	}
	else{
		return BRT_Condition;
	}
}

/*
balance 
index:-1，插入
*/
void Btree::balance(PPage parentPage,PPage curPage,int index,OpType opType){
	
	assert(curPage);

	switch (opType)
	{
	case OP_INSERT:
		{
			if(curPage->getFreeSpace() < 0){
				//SPLIT
			}
		}
		break;
	case OP_UPDATE:
		break;
	case OP_DELETE:
		{
			
		}
		break;
	}

	if(opType==OP_INSERT){
		if(curPage->getFreeSpace() < 0){
			//SPLIT
		}
	}
	else if(opType==OP_DELETE){
		
	}
	else if(opType==OP_UPDATE){
		
	}
	if(parentPage==NULL){
		if(curPage->getFreeSpace() < 0){
			//SPLIT
		}
	}
	else
	{
		if(curPage->getFreeSpace() < 0){
			//SPLIT
		}
		else{
			
		}
	}
}

void Btree::traverse(void (*callback)(Value v))
{
	assert(callback);
}

