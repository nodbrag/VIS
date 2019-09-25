#include "TagStatus.h"



TagStatus::TagStatus()
{
}

TagStatus::~TagStatus()
{
}
void TagStatus::setSTime(ec::Time time) {
	this->stime.setSeconds(time.getUTCFullSeconds());
	this->stime.setMicroSeconds(time.tv_usec());
}
ec::Time TagStatus::getStime() {
	return this->stime;
}
ec::Time TagStatus::getSendTime() {
	return this->sendTime;
}
void TagStatus::setSendTime(ec::Time sendtime) {
	this->sendTime.setSeconds(sendtime.getUTCFullSeconds());
	this->sendTime.setMicroSeconds(sendtime.tv_usec());
}

void TagStatus::setdryTime(ec::Time dryTime) {
	this->dryTime.setSeconds(dryTime.getUTCFullSeconds());
	this->dryTime.setMicroSeconds(dryTime.tv_usec());
}

ec::Time TagStatus::getdryTime() {
	return this->dryTime;
}

void TagStatus::setEtime(std::string etime) {
	this->etime = etime;
}
std::string TagStatus::getEtime() {
	return this->etime;
}
void TagStatus::setWorkstep(std::string workstep) {
	this->workstep = workstep;
}
std::string TagStatus::getWorkstep() {
	return this->workstep;
}
void TagStatus::setRgbIp(std::string rgbip) {
	this->rgbip = rgbip;
}
std::string TagStatus::getRgbIp() {
	return this->rgbip;
}
void TagStatus::setIrIp(std::string irip) {
	this->irip = irip;
}
std::string TagStatus::getIrIp() {
	return this->irip;
}
void TagStatus::setTankgroupid(std::string tankgroupid) {
	this->tankgroupid = tankgroupid;
}
std::string TagStatus::getTankgroupid() {

	return this->tankgroupid;
}
void TagStatus::setCodes(std::string code,std::string time) {
	if (this->codes.count(code) == 0) {
		if (this->codes.size() == 0) {
			this->codes.insert(make_pair(code, time));
		}
		else {
		  ec::Time now;
		  this->codes.insert(make_pair(code, now.toDate().toString()));
		}
	}
}
void TagStatus::RemoveCode(std::string code) {
	this->codes.erase(code);
}
std::map<std::string, std::string> TagStatus::getCodes() {
	return this->codes;
}
void TagStatus::setEX(int x) {
	this -> ex = x;
}
int TagStatus::getEX() {
	return this->ex;
}
void TagStatus::setEY(int y) {
	this->ey = y;
}
int TagStatus::getEY() {

	return this->ey;
}
void TagStatus::setSX(int x) {
	this->sx = x;
}
int TagStatus::getSX() {
	return this->sx;
}
void TagStatus::setSY(int y) {
	this->sy = y;
}
int TagStatus::getSY() {

	return this->sy;
}
void TagStatus::setStatus(int status) {
	this->status = status;
}
int TagStatus::getStatus() {
	return this->status;
}
void TagStatus::setPersonCode(std::string personcode) {
	this->personcode = personcode;
}
std::string TagStatus::getPersonCode() {

	return this->personcode;
}

int TagStatus::getPersonlock() {
	return this->personlock;
}
void TagStatus::setPersonLock(int lock)
{
	this->personlock = lock;
}
std::string TagStatus::getDefalutCode() {
	return this->defalutCode;
}
void TagStatus::setDefaultCode(std::string code) {
	this->defalutCode = code;
}
void TagStatus::setIsDray(int isDray) {
	this->isDray = isDray;
}
int TagStatus::getIsDray() {
	return this->isDray;
}

int TagStatus::getSkillCount() {
	return this->skillcount;
}
void TagStatus::setSKillCount(int skillcount) {
	this->skillcount = skillcount;
}

int TagStatus::getAutostopcount() {
	return this->autostopcount;
}
void  TagStatus::setAutostopcount(int autostopcount) {
	this->autostopcount = autostopcount;
}

int TagStatus::getTipCount() {
	return this->tipcount;
}
void TagStatus::setTipCount(int count) {
	this->tipcount = count;
}