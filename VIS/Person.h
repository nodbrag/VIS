#pragma once
#include "date.h"
class Person
{
public:
	Person();
	~Person();
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	ec::Time getRecentVITime();
	void setRecentVITime(ec::Time time);
	void setCode(std::string code);
	std::string getCode();
	void setTankgroupid(std::string tankgroupid);
	std::string getTankgroupid();
private:
	int x;
	int y;
	ec::Time recentVITime;
	std::string code;
	std::string tankgroupid;
};

