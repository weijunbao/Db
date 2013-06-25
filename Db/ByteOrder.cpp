#include "ByteOrder.h"

ByteOrder::ByteOrder(void)
{
}


ByteOrder::~ByteOrder(void)
{
}

bool ByteOrder::IS_BIG_ENDIAN=false;//这是因为静态的成员变量要进行初始化.要不编译不通过

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