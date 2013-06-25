#pragma once
class String
{
public:
	String(void);
	~String(void);
public:
	static int cmp(const char* v1,int v1Size,const char* v2,int v2Size);
	static int cmpcase(const char* v1,int v1Size,const char* v2,int v2Size);
	
};

