#include "FileHelper.h"



FileHelper::FileHelper()
{

}


FileHelper::~FileHelper()
{

}

bool FileHelper::createDirectory(std::string folder)
{

	std::string folder_builder;
	std::string sub;
	sub.reserve(folder.size());
	for (auto it = folder.begin(); it != folder.end(); ++it)
	{
		
		const char c = *it;
		sub.push_back(c);
		if (c == PATH_DELIMITER || it == folder.end() - 1)
		{
			folder_builder.append(sub);
			if (0 != ::_access(folder_builder.c_str(), 0))
			{
				// this folder not exist  
				if (0 != ::_mkdir(folder_builder.c_str()))
				{
					// create failed  
					return false;
				}
			}
			sub.clear();
		}
	}
	return true;
}
bool FileHelper::checkFolderExist(std::string dir) {

	bool isExist = false;
	struct _stat fileStat;
	if ((_stat(dir.c_str(), &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))
	{
		isExist = true;
	}
	return isExist;
}
