#ifndef common_type_h
#define common_type_h
#include <stdint.h>

typedef void (*InitDelegate)(void* data);
typedef void (*FreeDelegate)(void *data);
typedef bool (*FindDelegate)(const void* data,const void* data2);
typedef void (*ForEachDelegate)(const void* data);
/*
data1==data2 0
data1>data2  1
data1<data2  -1
*/
typedef int (*CompareDelegate)(const void* data1,const void* data2);
typedef int (*CompareValue)(const char* v1,int v1Size,const char* v2,int v2Size);

#define Failure 0
#define Success 1

class Object{
public:
	~Object();
};

class NonCopyable{
private:
	NonCopyable(const NonCopyable&);
	NonCopyable& operator=(const NonCopyable&);
public:
	NonCopyable(void);
};

template<typename T>
class IHashCode
	:public Object{
public:
	virtual T getHashCode(void)=0;
};

template<typename T>
class IComparer :
	public Object{
public:
	virtual int Compare(T t1,T t2)=0;
};

template<typename T>
class IClone {
public:
	virtual T* Clone(void)=0;
};

template<typename T>
class IComparable :
	public Object{
public:
	virtual int CompareTo(T t)=0;
};

/*
²»ÄÜnew
*/
class NonCreate{
private:
	NonCreate(const NonCreate&);
	NonCreate& operator=(const NonCreate&);
	NonCreate(void);
};

typedef uint32_t PageNo;
enum PageType:uint8_t{
	PT_LEAF=0X00,
	PT_INDEX=0X01,
	PT_OF=0X02
};
#endif