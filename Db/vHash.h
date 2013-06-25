#pragma once
#include <stdint.h>

typedef enum HashType HashType;
typedef union HashKey HashKey;
enum HashType{
	HT_INT=0x00,
	HT_CHAR=0x01
};
union HashKey{
	uint32_t iKey;
	const char* pKey;
};

class vHash
{
public:
	class vHashElement{
		friend class vHash;
		HashKey hashKey;
		void* pValue;
		vHashElement* next;
	};
		
	vHash(HashType hashType);
	~vHash(void);
public:
	int insert(HashKey hashKey,const void* pValue);
	void* get(HashKey hashKey);
	bool reHash(unsigned int n);
private:
	HashType hashType;
	vHashElement** elements;
	int size;
	int capacity;
};