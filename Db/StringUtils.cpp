#include "StringUtils.h"
#include <assert.h>

StringUtils::StringUtils(void)
{
}


StringUtils::~StringUtils(void)
{
}

int StringUtils::compare(const char* s1,int s1size,const char* s2,int s2size)
{
	assert(s1 && s1size > 0);
	assert(s2 && s2size > 0);
	if(s1size!=s2size)
		return false;
	for(int i=0;i<s1size;i++){
		if(s1[i] > s2[i]){
			return 1;
		}
		else if(s1[i] < s2[i]){
			return -1;
		}
	}
	return 0;
}

template<typename T>
bool StringUtils::binarySearch(const T* data,const T t,int size,int& rv){
	int startIndex,endIndex,middleIndex;
	bool isLess=false;
	startIndex=0;
	middleIndex=size-1;
	
	while(true){
		int i;
		if(startIndex>endIndex){
				if(isBigger)
					rv=middleIndex;
				else
					rv= middleIndex+1;
				return false;
		}
		middleIndex=startIndex + (endIndex - startIndex)/2;
		i=data[middleIndex].CompareTo(t);
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

template<typename T>
bool StringUtils::binarySearch(const T* data,const T t,int size,int& rv,CompareValue compareFunc){
	int startIndex,endIndex,middleIndex;
	bool isLess=false;
	startIndex=0;
	middleIndex=size-1;
	assert(compareFunc!=NULL);

	while(true){
		int i;
		if(startIndex>endIndex){
				if(isBigger)
					rv=middleIndex;
				else
					rv= middleIndex+1;
				return false;
		}
		middleIndex=startIndex + (endIndex - startIndex)/2;
		i=compareFunc(&data[middleIndex],t);
		
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

bool StringUtils::binarySearch(const float* data,const float t,int size,int& rv){
	int startIndex,endIndex,middleIndex;
	bool isBigger=false;// t ÊÇ·ñÐ¡ÓÚ data[middleIndex]
	startIndex=0;
	endIndex=size-1;
	
	while(true){
		int i;
		if(startIndex>endIndex){
				int insertIndex;
				/*if(isLess) insertIndex=endIndex;
				else insertIndex=startIndex;*/
				if(isBigger)
					insertIndex=middleIndex;
				else
					insertIndex= middleIndex+1;
				rv=insertIndex;
				return false;
		}
		middleIndex=startIndex + (endIndex - startIndex)/2;
		//i=data[middleIndex].CompareTo(t);
		
		if(data[middleIndex]>t){
			endIndex=middleIndex-1;
			isBigger=true;
		}
		else if(data[middleIndex]==t){
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