#include "Tank.h"


Tank::Tank(void)
{
}


Tank::~Tank(void)
{
}


void Tank::setTank_type( string tankType )
{
	this->tank_type=tankType;
}

string Tank::getTank_type()
{
	return this->tank_type;
}
void Tank::setArea_1_ltx( int area_1_ltx )
{
	this->area_1_ltx=area_1_ltx;
}

int Tank::getArea_l_ltx()
{
	return area_1_ltx;
}

void Tank::setArea_1_lty( int area_1_lty )
{
	this->area_1_lty=area_1_lty;
}

int Tank::getArea_1_lty()
{
	return area_1_lty;
}

void Tank::setArea_1_rbx( int area_1_rbx)
{
	this->area_1_rbx=area_1_rbx;
}

int Tank::getArea_1_rbx()
{
	return area_1_rbx;
}

void Tank::setArea_1_rby( int area_1_rby )
{
	this->area_1_rby=area_1_rby;
}

int Tank::getArea_1_rby()
{
	return area_1_rby;
}

void Tank::setArea_2_ltx( int area_2_ltx )
{
	this->area_2_ltx=area_2_ltx;
}

int Tank::getArea_2_ltx()
{
	return area_2_ltx;
}

void Tank::setArea_2_lty( int area_2_lty )
{
	this->area_2_lty=area_2_lty;
}

int Tank::getArea_2_lty()
{
	return area_2_lty;
}

void Tank::setArea_2_rbx( int area_2_rbx)
{
	this->area_2_rbx=area_2_rbx;
}

int Tank::getArea_2_rbx()
{
	return area_2_rbx;
}

void Tank::setArea_2_rby( int area_2_rby )
{
	this->area_2_rby=area_2_rby;
}

int Tank::getArea_2_rby()
{
	return area_2_rby;
}

void Tank::setTank_id( int tank_id )
{
	this->tank_id=tank_id;
}

int Tank::getTank_id()
{
	return tank_id;
}

void Tank::setTank_name( string tank_name )
{
	this->tank_name=tank_name;
}

string Tank::getTank_name()
{
	return tank_name;
}

void Tank::setTank_group_id( string tank_group_id )
{
	this->tank_group_id=tank_group_id;
}

string Tank::getTank_group_id()
{
	return tank_group_id;
}

void Tank::setCamera_ip( string camera_ip )
{
	this->camera_ip=camera_ip;
}

string Tank::getCamera_id()
{
	return camera_ip;
}

void Tank::setCamera_channal( int camera_channal )
{
	this->camera_channal=camera_channal;
}

int Tank::getCamera_channal()
{
	return camera_channal;
}

void Tank::setCamera_type( string camera_type )
{
	this->camera_type=camera_type;
}
string Tank::getCamera_type()
{
	return camera_type;
}
void Tank::setExposure_val(int exposure_val) {
	this->exposure_val = exposure_val;
}
int Tank::getExposure_val() {
	return this -> exposure_val;
}