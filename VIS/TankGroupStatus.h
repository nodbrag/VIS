#pragma once
#include <vector>
#include "date.h"
#include "CameraMap.h"
class TankGroupStatus
{
public:
	TankGroupStatus();
	~TankGroupStatus();
	ec::Time getRecentVITime();
	void setRecentVITime(ec::Time time);
	std::vector<CameraMap *> *cameraVector;
	void setTank_group_id(std::string tank_group_id);
	std::string getTank_group_id();
	bool getIsWorking();
	void setIsWorking(bool iswork=false);
private:
	ec::Time recentVITime;
	std::string tank_group_id;
	bool isWorking;
};

