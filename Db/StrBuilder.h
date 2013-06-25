#pragma once
class StrBuilder
{
public:
	StrBuilder(void);
	~StrBuilder(void);
private:
	char* v;
	int capacity;
	int size;
};

