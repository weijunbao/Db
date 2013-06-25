#pragma once
#include "commonType.h"
class Value :
	public IClone<Value>
{
public:
	Value(void);
	Value(char* data,int size);
	~Value(void);
public:
	const char* getData() const;
	int getSize() const;
	void set(char* data,int size);
	Value* Clone(void);
	int compare(const Value& v) const;

private:
	char* data;
	int size;
};
