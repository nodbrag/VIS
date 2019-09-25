#include "XmlConfig.h"

XmlConfig::XmlConfig()
{
	
}

XmlConfig::~XmlConfig()
{
}

TiXmlDocument XmlConfig::initXml() {
	 //std::string path = Common::GetCurrentPath();
	 //TiXmlDocument doc( (path+ "/Config/config.xml").c_str()); // 读入XML文件
	 char *xml = "/Config/config.xml";
	 char  path[1024] = { 0 };;
	 strcpy(path, Common::GetCurrentPath());
	 strcat(path, xml);
	 TiXmlDocument doc(path);
	 if (!doc.LoadFile(TIXML_ENCODING_UTF8)) {
		 printf_s("%s\r\n", "读取配置文件xml错误!");
	 }// 如果无法读取文件，则返回
	 TiXmlHandle hDoc(&doc);         // hDoc是&doc指向的对象
	// TiXmlElement* pElem;            // 指向元素的指针
	 
	 this->rootElement = hDoc.FirstChildElement().Element(); //指向根节点
	 return doc;
}

std::string XmlConfig::GetVSParmsNodeValue(std::string nodename) {

	TiXmlElement* elem = this->rootElement->FirstChildElement();
	TiXmlNode* e1 = elem->FirstChild(nodename.c_str());
	if (e1 != NULL) {
		TiXmlNode* e2 = e1->FirstChild();
		return  e2->Value(); 
	}
	else {
		printf_s("%s\r\n", "read config error：NO find " + nodename + " xml node");
		return "";
	}
}

