#pragma once
#include "tinystr.h" 
#include "tinyxml.h"
#include "Common.h"
#include <iostream>
#include <string>

class XmlConfig
{
public:
	XmlConfig();
	~XmlConfig();
	TiXmlDocument initXml();
	std::string GetNodeValue(std::string nodename);
	std::string GetVSParmsNodeValue(std::string nodename);
	TiXmlDocument doc;
	TiXmlElement *rootElement;
};

