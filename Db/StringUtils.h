#pragma once
#include "commonType.h"
class StringUtils
{
private:
	StringUtils(void);
	~StringUtils(void);
public:
	static int compare(const char* s1,int s1size,const char* s2,int s2size);
	template<typename T>
	static bool binarySearch(const T* data,const T t,int size,int& rv,CompareValue compareFunc);
	template<typename T>
	static bool binarySearch(const T* data,const T t,int size,int& rv);

	static bool binarySearch(const float* data,const float t,int size,int& rv);
};

