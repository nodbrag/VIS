#include "TankGroupStatus.h"

TankGroupStatus::TankGroupStatus()
{
	this->setIsWorking(false);
	ec::Time time;
	time.addDay(-1);
	this->setRecentVITime(time);
	this->cameraVector = new std::vector<CameraMap *>();
}
TankGroupStatus::~TankGroupStatus()
{
}
ec::Time TankGroupStatus::getRecentVITime() {
	return this->recentVITime;
}
void TankGroupStatus::setRecentVITime(ec::Time time) {
	this->recentVITime.setSeconds(time.getUTCFullSeconds());
	this->recentVITime.setMicroSeconds(time.tv_usec());
}
void TankGroupStatus::setTank_group_id(std::string tank_group_id) {
	this->tank_group_id = tank_group_id;
}
std::string TankGroupStatus::getTank_group_id() {
	return this->tank_group_id;
}
bool TankGroupStatus::getIsWorking() {
	
	return this->isWorking;
}
void TankGroupStatus::setIsWorking(bool iswork) {
	this->isWorking = iswork;
}
