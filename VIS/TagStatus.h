#pragma once
#include "date.h"
#include <map>

class TagStatus
{
public:
	TagStatus();
	~TagStatus();
	 
	 void setSTime(ec::Time stime);
	 ec::Time getStime();
	 ec::Time getSendTime();
	 void setSendTime(ec::Time sendtime);
	 void setdryTime(ec::Time dryTime);
	 ec::Time getdryTime();
	 void setEtime(std::string etime);
	 std::string getEtime();
	 void setWorkstep(std::string workstep);
	 std::string getWorkstep();
	 void setRgbIp(std::string rgbip);
	 std::string getRgbIp();
	 void setIrIp(std::string irip);
	 std::string getIrIp();
	 void setTankgroupid(std::string tankgroupid);
	 std::string getTankgroupid();
	 void setCodes(std::string code, std::string time);
	 std::map<std::string, std::string> getCodes();
	 void RemoveCode(std::string code);
	 void setSX(int x);
	 int getSX();
	 void setSY(int y);
	 int getSY();
	 void setEX(int x);
	 int getEX();
	 void setEY(int y);
	 int getEY();
	 void setStatus(int status);
	 int getStatus();
	 void setPersonCode(std::string personcode);
	 std::string getPersonCode();
	 int getPersonlock();
	 void setPersonLock(int lock);
	 std::string getDefalutCode();
	 void setDefaultCode(std::string code);
	 void setIsDray(int isDray);
	 int getIsDray();

	 int getSkillCount();
	 void setSKillCount(int skillcount);

	 int getAutostopcount();
	 void setAutostopcount(int autostopcount);

	 int getTipCount();
	 void setTipCount(int count);

private:
	ec::Time stime;
	std::string etime;
	ec::Time sendTime;
	ec::Time dryTime;
	std::string workstep;
	std::string rgbip;
	std::string irip;
	std::string tankgroupid;
	std::map<std::string,std::string> codes;
	std::string defalutCode;
	int status;
	std::string personcode;
	int personlock;
	int sx;
	int sy;
	int ex;
	int ey;
	int isDray;
	int skillcount;
	int autostopcount;
	int tipcount;
	
};

