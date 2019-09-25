#include "CameraGroupStatus.h"

CameraGroupStatus::CameraGroupStatus()
{
}
CameraGroupStatus::~CameraGroupStatus()
{
}
int CameraGroupStatus::getVideoFrameRate() {
	return this->IrFrameRate +this->RGBRrameRate;
}
void CameraGroupStatus::setVideoFrameRate(int frameRate) {
	this->IrFrameRate = frameRate;
	this->RGBRrameRate = frameRate;
}
void CameraGroupStatus::setCameraGroupid(int cameraGroupid) {
	this->cameraGroupid = cameraGroupid;
}
void CameraGroupStatus::setGroupid(int groupid) {
	this->groupid = groupid;
}
int CameraGroupStatus::getCameraGroupid() {
	return this->cameraGroupid;
}
int CameraGroupStatus::getGroupid() {
	return this->groupid;
}
