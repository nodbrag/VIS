#pragma once
#include <io.h>  
#include <direct.h>
#include <string>

#define PATH_DELIMITER '\\'  
class FileHelper
{
public:
	FileHelper();
	~FileHelper();
	bool createDirectory(std::string dir);
	bool checkFolderExist(std::string dir);
};

