#include "XmlConfig.h"

XmlConfig::XmlConfig()
{
	
}

XmlConfig::~XmlConfig()
{
}

TiXmlDocument XmlConfig::initXml() {
	 //std::string path = Common::GetCurrentPath();
	 //TiXmlDocument doc( (path+ "/Config/config.xml").c_str()); // ����XML�ļ�
	 char *xml = "/Config/config.xml";
	 char  path[1024] = { 0 };;
	 strcpy(path, Common::GetCurrentPath());
	 strcat(path, xml);
	 TiXmlDocument doc(path);
	 if (!doc.LoadFile(TIXML_ENCODING_UTF8)) {
		 printf_s("%s\r\n", "��ȡ�����ļ�xml����!");
	 }// ����޷���ȡ�ļ����򷵻�
	 TiXmlHandle hDoc(&doc);         // hDoc��&docָ��Ķ���
	// TiXmlElement* pElem;            // ָ��Ԫ�ص�ָ��
	 
	 this->rootElement = hDoc.FirstChildElement().Element(); //ָ����ڵ�
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
		printf_s("%s\r\n", "read config error��NO find " + nodename + " xml node");
		return "";
	}
}

