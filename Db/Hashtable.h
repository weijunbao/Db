#pragma once


enum HashType{
	HT_INT=0x00,
	HT_CHAR=0x01
};

template<typename T,int GROW_FACTOR>
class Hashtable
{
public:
	class HashElement{
		friend class vHash;
		HashKey hashKey;
		void* pValue;
		HashElement* next;
	};
	Hashtable(void);
	~Hashtable(void);
private:
	HashType hashType;
	HashElement** elements;
	int size;
	int capacity;
	int growFactor;
public:
	
};

