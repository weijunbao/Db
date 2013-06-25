#pragma once
#include "commonType.h"
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
typedef class File* PFile;

class File :
	public Object,public NonCopyable
{
public:
	File(void){}
	virtual ~File(void){delete this;}
	virtual bool open(const char* fileName)=0;
	virtual bool read(char* buffer,uint64_t offset,size_t size)=0;
	virtual bool write(const char* buffer,uint64_t offset,size_t size,bool flush)=0;
	virtual uint64_t tell()=0;
	virtual bool flush()=0;
	virtual bool close(void)=0;

	virtual uint64_t getFileSize(void)=0;
	
protected:
	char fileName[_MAX_PATH];
};

class CFile :
	public File{
public:
	CFile(void);
	CFile(const char* fileName);
	virtual ~CFile(void);
	bool open(const char* fileName);
	bool read(char* buffer,uint64_t offset,size_t size); 
	bool write(const char* buffer,uint64_t offset,size_t size,bool flush);
	uint64_t tell();
	bool flush();
	bool close(void);
	uint64_t getFileSize(void);
private:
	FILE* pFile;
};

class CPPFile :
	public File{
public:
	bool read(char* buffer,uint64_t offset,size_t size); 
	bool write(const char* buffer,uint64_t offset,size_t size,bool flush);
	bool close(void);
	uint64_t getSize(void);
private:

};

class WINFile :
	public File{

};