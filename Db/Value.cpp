#include "Value.h"
#include "String.h"

Value::Value(void)
{
}

Value::Value(char* data,int size)
{

}

Value::~Value(void)
{
}

const char* Value::getData(void) const
{
	return this->data;
}

int Value::getSize(void) const
{
	return this->size;
}

void Value::set(char* data,int size)
{

}

Value* Value::Clone(void)
{
	return this;
}

int Value::compare(const Value& v) const
{
	return String::cmpcase(getData(),getSize(),v.getData(),v.getSize());
}

inline bool operator==(const Value& x, Value& y) {
	return x.compare(y)==0;
}

inline bool operator!=(const Value& x, const Value& y) {
	return true;
	//return !(x==y);
}

inline bool operator <(const Value& x, const Value& y) {
    return true;
}