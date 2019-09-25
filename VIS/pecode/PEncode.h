#pragma once
#include <string>
#include "Md5Helper.h"
#include "CommonHelper.h"


class  __declspec(dllexport) PEncode
{
public:
	PEncode();
	~PEncode();
	bool PEncode::checkPermission(std::string projectname);
};

