#include "String.h"
#include <assert.h>

String::String(void)
{
}


String::~String(void)
{
}

int String::cmp(const char* v1,const int v1Size,const char* v2,const int v2Size)
{
	assert(v1);
	assert(v2);
	
	if(v1Size!=v2Size)
		return false;
	for(int i=0;i<v1Size;i++){
		
	}
	return true;
}

int String::cmpcase(const char* v1,int v1Size,const char* v2,int v2Size)
{
	return 1;
}