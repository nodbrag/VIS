#pragma once
#include <string>

class Command
{
public:
	Command(void);
	~Command(void);
public:
	  static std::string init;
	  static std::string start;
	  static std::string stop;
	  static std::string takePicture;
	  static std::string test;
};

