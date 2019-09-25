#include "CameraGroup.h"


CameraGroup::CameraGroup(void)
{
	//Ëã·¨½Ó¿Ú
	VICoreInterface vicode;
	this->VICode = vicode;
}

void CameraGroup::initVIParms(int mincommonnum, bool isDrawCode, bool isDrawTail, float decodeInteval,float detectMinArea, float detectMaxArea, int eshiftx,int pshiftx, int bloodMax, float scale, int innerThresh, std::map<int, std::vector<int>> colorval) {

	this->VICode.init(mincommonnum, isDrawCode, isDrawTail, decodeInteval, detectMinArea, detectMaxArea, eshiftx,pshiftx, bloodMax,scale,innerThresh, colorval);
}

CameraGroup::~CameraGroup(void)
{
}

string CameraGroup::getIr_camera_ip()
{
	return ir_camera_ip;
}

void CameraGroup::setIr_camera_ip( string ir_camera_ip )
{
	this->ir_camera_ip=ir_camera_ip;
}

int CameraGroup::getIr_camera_channal()
{
	return ir_camera_channal;
}

void CameraGroup::setIr_camera_channal( int ir_camera_channal )
{
	this->ir_camera_channal=ir_camera_channal;
}

string CameraGroup::getRgb_camera_ip()
{
	return rgb_camera_ip;
}

void CameraGroup::setRgb_camera_ip( string rgb_camera_ip )
{
	this->rgb_camera_ip=rgb_camera_ip;
}

int CameraGroup::getRgb_camera_channal()
{
	return rgb_camera_channal;
}

void CameraGroup::setRgb_camera_channal( int rgb_camera_channal )
{
	this->rgb_camera_channal=rgb_camera_channal;
}

void CameraGroup::setGroupid( int groupid )
{
	this->groupid=groupid;
}

int CameraGroup::getGroupid()
{
	return groupid;
}
void CameraGroup::setTank_group_id(string tank_group_id) {
	this->tank_group_id = tank_group_id;
}
string CameraGroup::getTank_group_id() {
	return tank_group_id;
}
