#include "ByteOrder.h"

ByteOrder::ByteOrder(void)
{
}


ByteOrder::~ByteOrder(void)
{
}

bool ByteOrder::IS_BIG_ENDIAN=false;//������Ϊ��̬�ĳ�Ա����Ҫ���г�ʼ��.Ҫ�����벻ͨ��

void ByteOrder::checkEndian(void)
{
	int i=0x00000001;
	//short s=*((short*)&i+1);
	short s=*(short*)&i;
	if(s==1){
		IS_BIG_ENDIAN=false;
	}
	else{
		IS_BIG_ENDIAN=true;
	}
}