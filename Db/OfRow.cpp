#include "DataRow.h"
#include "vCode.h"
#include <assert.h>
#include <memory.h>
#include <stdlib.h>

int OfRow::getSize(void)
{
	return vCode::getVariableSize(this->getKeySize()) + this->getKeySize();
}

int OfRow::writeBuffer(char* pageBuffer,int offset)
{
	int i;
	assert(pageBuffer);
	///////////VALUE////////////////////
	i=vCode::vCodei32(this->getKeySize(),pageBuffer + offset);
	offset+=i;
	///////////ValueSize////////////////////
	memcpy(pageBuffer + offset,this->getKey(),this->getKeySize());
	offset+=this->getKeySize();

	return 1;
}

int OfRow::parse(POfRow& row,char* pageBuffer,int& offset)
{
	uint64_t i;
	int vSize;
	char* value;
	int off;
	assert(pageBuffer);
	off=offset;
	vSize=vCode::getVariableCode(pageBuffer + offset,i);
	offset+=vSize;
	//����	1	warning C4244: ��������: �ӡ�uint64_t��ת������size_t�������ܶ�ʧ����	f:\projects\db\db\ofrow.cpp	37	1	Db
	value=(char*)malloc(sizeof(char) * (size_t)i);
	if(value==NULL){
		offset=off;//���ó�ֵ
		return PTE_MEMORY;
	}
	if(row==NULL)
		row=new OfRow();
	row->set(value,vSize);
	return 1;
}