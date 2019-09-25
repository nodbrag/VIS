#include "Person.h"



Person::Person()
{
}


Person::~Person()
{
}
void Person::setX(int x) {
	this->x = x;
}
int Person::getX() {
	return this->x;
}
void Person::setY(int y) {
	this->y = y;
}
int Person::getY() {
	return this->y;
}
ec::Time Person::getRecentVITime() {
	return this->recentVITime;
}
void Person::setRecentVITime(ec::Time time) {
	this->recentVITime.setSeconds(time.getUTCFullSeconds());
	this->recentVITime.setMicroSeconds(time.tv_usec());
}
void Person::setCode(std::string code) {
	this->code = code;
}
std::string Person::getCode() {
	return this->code;
}
void Person::setTankgroupid(std::string tankgroupid) {
	this->tankgroupid = tankgroupid;
}
std::string Person::getTankgroupid() {
	return this->tankgroupid;
}
