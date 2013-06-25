#pragma once
#include "commonType.h"
#include "DbFile.h"
#include "Directory.h"
#include <time.h>
#include <assert.h>
#include <string.h>
#include <direct.h>
#include <stdarg.h>


#define LOG_FILE_SIZE (1024*1024*4)

enum LoggerLevel {
	LEVEL_DEBUG = 0,
	LEVEL_INFO,
	LEVEL_WARNING,
	LEVEL_ERROR
};

enum LoggerType{
	LOG_FILE=0,
	LOG_DB,
	LOG_CONSOLE
};

class Logger:public Object
{
public:
	Logger(void);
	~Logger(void);
public:
	virtual bool write(char* logMessage)=0;
};

class FileLogger:public Logger
{
public:
	FileLogger(char* filePath,File* _file){
		char buf[_MAX_PATH]={'\0'};
		int iLen=0;
		assert(filePath);
		//初始化
		memset(filepath,'\0',sizeof(char)*_MAX_PATH);
		char timebuf[64]={'\0'};
		time_t now = time(NULL);
		strftime(timebuf, sizeof(timebuf), "%m-%d-%I-%M-%S",localtime(&now));
		iLen=strlen(filePath);
		Directory::createDirectory(filePath);
		strncpy(buf,filePath,iLen);
		strncpy(this->filepath,filePath,iLen);//赋属性
		buf[iLen]='\\';
		strcpy(buf+iLen+1,timebuf);
		_file->open(buf);
		this->file=_file;
	}

	~FileLogger(){
		delete file;
	}

	bool write(char* logMessage){
		if(file->getFileSize() > LOG_FILE_SIZE){
			char buf[_MAX_PATH]={'\0'};
			int iLen;
			char timebuf[64]={'\0'};
			time_t now = time(NULL);
			iLen=strlen(filepath);
			if(_chdir(filepath)!=0){
				perror("chdir error");
			}
			memcpy(buf,filepath,sizeof(char) * _MAX_PATH);
			strftime(timebuf, sizeof(timebuf), "%m-%d-%I-%M-%S",localtime(&now));

			buf[iLen]='\\';
			strcpy(buf+iLen+1,timebuf);
			//产生新的文件
			file->flush();
			file->close();
			file->open(buf);
		}
		return file->write(logMessage,file->tell(),strlen(logMessage),false);
	}

	char* makeLogFileName(char*& buf){
		
	}

private:
	char filepath[_MAX_PATH];
	File* file;
};

class DbLogger :
	public Logger{
public:
	bool write(char* logMessage){
		return true;
	}
};

class ConsoleLogger :
	public Logger{
public:
	bool write(char* logMessage){
		return true;
	}
};

class LoggerFormat{
private:
	LoggerFormat();
	~LoggerFormat();
public:
	static void debug(char** buf,char* file,int line,char* format,...){
		/*va_list ap;
		va_start(ap, format);
		vsnprintf(*buf, sizeof(*buf), format, ap);
		va_end(ap);*/
		
	}

	static void error(char** buf,char* file,int line,char* format,...){
	
	}

	static void info(char** buf,char* file,int line,char* format,...){
		
	}

};