#include "Directory.h"
#include <io.h>
#include <direct.h>
#include <assert.h>
#include <string.h>

Directory::Directory(void)
{
}


Directory::~Directory(void)
{
}

bool Directory::createDirectory(const char* filepath)
{
	int iLen;
	assert(filepath);
	iLen=strlen(filepath);
	if(!Directory::isExist(filepath)){
		if(_mkdir(filepath)==0)
			return true;
		else
			return false;
	}
	else
	{
		return true;
	}
}

bool Directory::isExist(const char* filepath)
{
	assert(filepath);
	if( (_access( filepath, 0 )) ==0 )
	{
		return true;
	}
	return false;
}