#include "vHash.h"
#include <string.h>
#include <stdlib.h>


//http://www.cnblogs.com/napoleon_liu/archive/2010/12/29/1920839.html
static uint32_t intHash( uint32_t a) 
{ 
	  a = (a+0x7ed55d16) + (a<<12); 
	  a = (a^0xc761c23c) ^ (a>>19); 
	  a = (a+0x165667b1) + (a<<5); 
	  a = (a+0xd3a2646c) ^ (a<<9); 
	  a = (a+0xfd7046c5) + (a<<3); // <<和 +的组合是可逆的 
	  a = (a^0xb55a4f09) ^ (a>>16);  
	  return a; 
}
/*http://www.cnblogs.com/napoleon_liu/archive/2010/12/29/1920839.html
int hash
*/
static uint32_t intHash32(uint32_t key) 
{ 
	key = ~key + (key << 15); // key = (key << 15) - key - 1; 
	key = key ^ (key >> 12); 
	key = key + (key << 2); 
	key = key ^ (key >> 4); 
	key = key * 2057; // key = (key + (key << 3)) + (key << 11); 
	key = key ^ (key >> 16); 
	return key; 
}
static long strHash( const char *key )
{
	long hash = 1315423911;
	int  len=strlen(key);
	int i;
	for(i = 0; i < len; i++)
	{
		hash ^= ((hash << 5) + key[i] + (hash >> 2));
	}
	return hash;
}
bool vHash::reHash(unsigned int n){
	return true;
}
vHash::vHash(HashType hashType){
	this->hashType=hashType;
}

vHash::~vHash(void)
{
}

int vHash::insert(HashKey hashKey,const void* pValue){
	return 1;
}

void* vHash::get(HashKey hashKey){
	int n;
	vHashElement* element;
	if(this->hashType==HT_INT)
		n=intHash(hashKey.iKey) % this->capacity;
	else if(this->hashType==HT_CHAR)
		n=strHash(hashKey.pKey) % this->capacity;
	element=this->elements[n];
	while(element!=NULL){
		if(this->hashType==HT_INT){
			if(element->hashKey.iKey==hashKey.iKey)
				return element->pValue;
		}
		else if(this->hashType==HT_CHAR){
			if(strcmp(element->hashKey.pKey,hashKey.pKey)==0)
				return element->pValue;
		}
		element=element->next;
	}
	return NULL;
}