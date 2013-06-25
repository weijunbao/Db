#pragma once
#include "commonType.h"

/*
Ô¼ÊøIHashCode
*/
template<typename T>
class HashSet
{
public:
	HashSet(void){}
	virtual ~HashSet(void){}

	bool add(T t){
		int hashCode=t.getHashCode();
		return true;
	}
	bool remove(T t){
		int hashCode=t.getHashCode();
		return true;
	}
private:
	uint16_t capacity;
	int size;
	T* _data;
};
