#include "SimulatedData.h"


SimulatedData::SimulatedData(string ecode,int x,int y)
{
	this->ecode=ecode;
	this->x=x;
	this->y=y;
}


SimulatedData::~SimulatedData(void)
{
}

void SimulatedData::setEcode( string ecode )
{
	this->ecode=ecode;
}

string SimulatedData::getEcode()
{
	return ecode;
}

void SimulatedData::setX( int x )
{
	this->x=x;
}

int SimulatedData::getX()
{
	return x;
}

void SimulatedData::setY( int y )
{
	this->y=y;
}

int SimulatedData::getY()
{
	return y;
}
