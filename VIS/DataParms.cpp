#include "DataParms.h"

DataParms::DataParms(void)
{
}
DataParms::DataParms(string cameraIp, string cameraPass,int type,string idCode,string personCode,int dryIsCheck,int cleanStatus,string cleanStartTime,string cleanEndTime,string tankType,int gunStopID,int x,int y,int width,int height,string imagedatas,int imageFormart)
{
	this->_cameraIp=cameraIp;
	this->_cameraPass=cameraPass;
	this->_gunStopID=gunStopID;
	this->_type=type;
	this->_width=width;
	this->_height=height;
	this->_idCode=idCode;
	this->_x=x;
	this->_y=y;
	this->_imagedatas=imagedatas;
	this->_imageFormart=imageFormart;
	this->personCode = personCode;
	this->cleanStatus = cleanStatus;
	this->cleanStartTime = cleanStartTime;
	this->cleanEndTime = cleanEndTime;
	this->dryischeck = dryIsCheck;
}
DataParms::DataParms(string cameraIp, string cameraPass, int type, string idCode, string personCode,  int gunStopID, int x, int y, int width, int height, string imagedatas, int imageFormart)
{
	this->_cameraIp = cameraIp;
	this->_cameraPass = cameraPass;
	this->_gunStopID = gunStopID;
	this->_type = type;
	this->_width = width;
	this->_height = height;
	this->_idCode = idCode;
	this->_x = x;
	this->_y = y;
	this->_imagedatas = imagedatas;
	this->_imageFormart = imageFormart;
	this->personCode = personCode;
	this->cleanStatus = cleanStatus;
	this->cleanStartTime = cleanStartTime;
	this->cleanEndTime = cleanEndTime;
}

DataParms::~DataParms(void)
{
}

void DataParms::setCameraIp( string cameraIp )
{
	_cameraIp=cameraIp;
}

string DataParms::getCameraIp()
{
	return _cameraIp;
}

string DataParms::getCameraPass()
{
    return _cameraPass;
}

void DataParms::setCameraPass( string cameraPass )
{
	_cameraPass=cameraPass;
}

int DataParms::getType()
{
	return _type;
}

void DataParms::setType( int type )
{
	_type=type;
}

string DataParms::getIdCode()
{
	return _idCode;
}

void DataParms::setIdCode( string idCode )
{
	_idCode=idCode;
}

int DataParms::getGunStopID()
{
	return _gunStopID;
}

void DataParms::setGunStopID( int gunStopID )
{
	_gunStopID=gunStopID;
}

int DataParms::getX()
{
	return _x;

}

void DataParms::setX( int x )
{
	_x=x;
}

int DataParms::getY()
{
	return _y;
}

void DataParms::setY( int y )
{
	_y=y;
}

int DataParms::getWidth()
{
	return _width;
}

void DataParms::setWidth( int width )
{
	_width=width;
}

int DataParms::getHeight()
{
	return _height;
}

void DataParms::setHeight( int height )
{
	_height=height;
}

string DataParms::getImageDatas()
{
	return _imagedatas;
}

void DataParms::setImageDatas( string imagedatas )
{
	_imagedatas=imagedatas;
}

int DataParms::getImageFormart()
{
	return _imageFormart;
}

void DataParms::setImageFormart( int imageFormart )
{
	_imageFormart=imageFormart;
}
string DataParms::getPersonCode() {
	return this->personCode;
}
void DataParms::setPersonCode(string personCode) {
	this->personCode = personCode;
}

//内镜清洗状态 0 结束清洗 1 开始清洗
int DataParms::getCleanStatus() {
	return this->cleanStatus;
}
void DataParms::setCleanStatus(int cleanStatus) {
	this->cleanStatus = cleanStatus;
}
//内镜开始时间
string DataParms::getCleanStartTime() {
	return this->cleanStartTime;
}
void DataParms::setCleanStartTime(string cleanstarttime) {
	this->cleanStartTime = cleanstarttime;
}
//内镜结束时间
string DataParms::getCleanEndTime() {
	return this->cleanEndTime;
}
void DataParms::setCleanEndTime(string cleanendtime) {
	this->cleanEndTime = cleanendtime;
}

string   DataParms::getTankType() {
	return this->tankType;
}
void  DataParms::setTankType(string tankType) {
	this->tankType = tankType;
}

int DataParms::getDryischeck() {
	return this->dryischeck;
}
void DataParms::setDryischeck(int dryischeck)
{
	this->dryischeck = dryischeck;
}