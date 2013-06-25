#pragma once
class Directory
{
private:
	Directory(void);
	~Directory(void);
public:
	static bool createDirectory(const char* filepath);
	static bool isExist(const char* filepath);
};

