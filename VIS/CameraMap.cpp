#include "CameraMap.h"


CameraMap::CameraMap(void)
{

}
CameraMap::CameraMap(string cameraIp,long cameraPass, string cameraType )
{
	this->_cameraIp=cameraIp;
	this->_cameraPass=cameraPass;
	this->_cameraType=cameraType;
	
}


CameraMap::~CameraMap(void)
{
}

string CameraMap::getCameraIp()
{
	return _cameraIp;
}

void CameraMap::setCameraIp( string cameraIp )
{
	_cameraIp=cameraIp;
}

long CameraMap::getCameraPass()
{
	return _cameraPass;
}

void CameraMap::setCameraPass( long cameraPass )
{
	_cameraPass=cameraPass;
}


string CameraMap::getCameraType()
{
	return _cameraType;
}
void CameraMap::setCameraType(string cameraType)
{
	this->_cameraType=cameraType;
}

void CameraMap::setTank_group_id(string tank_group_id) {
	this->tank_group_id = tank_group_id;
}
string CameraMap::getTank_group_id() {
	return tank_group_id;
}

long  CameraMap::getUserID() {
	return userid;
}
void  CameraMap::setUserID(long userid) {
	this->userid = userid;
}
int CameraMap::getVideoFrameRate() {
	return this->videoFrameRate;
}
void CameraMap::setVideoFrameRate(int frameRate) {
	this->videoFrameRate = frameRate;
}


