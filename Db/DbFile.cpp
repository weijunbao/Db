#include "DbFile.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <io.h>

CFile::CFile():pFile(NULL)
{
	
}

CFile::CFile(const char* fileName){
	this->open(fileName);
}

CFile::~CFile()
{
	close();
}

bool CFile::open(const char* fileName)
{
	errno_t err;
	FILE* _pFile=NULL;
	assert(fileName);
	err=fopen_s(&_pFile,fileName,"w+");
	if(err!=0){
		perror("open file error\n");
		return false;
	}
	//strcpy_s(this->fileName,strnlen_s(fileName,_MAX_PATH),fileName);//用法不知道对不对
	strcpy(this->fileName,fileName);
	if(this->pFile!=NULL){
		fclose(this->pFile);//关闭
	}
	this->pFile=_pFile;
	return true;
}

bool CFile::read(char* buffer,uint64_t offset,size_t size)
{
	assert(buffer);
	_fseeki64(pFile,offset,SEEK_SET);
	fread(buffer,size,1,pFile);
	return true;
}

bool CFile::write(const char* buffer,uint64_t offset,size_t size,bool flush)
{
	assert(buffer);

	if(_fseeki64(pFile,offset,SEEK_SET)==-1){
		return false;
	}

	if(fwrite(buffer,size,1,pFile)==0)
		return false;
	if(flush)
		fflush(pFile);

	return true;
}

bool CFile::flush()
{
	if(fflush(pFile)==0)
		return true;
	return false;
}

uint64_t CFile::tell()
{
	return _ftelli64(pFile);
}

uint64_t CFile::getFileSize(void)
{
	return _filelength(fileno(pFile));
}

bool CFile::close()
{
	if(fclose(pFile)==0)
		return true;
	return false;
}