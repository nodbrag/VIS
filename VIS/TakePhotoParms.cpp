#include "TakePhotoParms.h"

TakePhotoParms::TakePhotoParms(void)
{
}

TakePhotoParms::~TakePhotoParms(void)
{
}

long TakePhotoParms::getCameraPass()
{
	return _cameraPass;
}

int TakePhotoParms::getFrequency()
{
	return _frequency;
}

int TakePhotoParms::getImageFormat()
{
	return _imageFormat;
}

bool TakePhotoParms::getIsImageDrowBorder()
{
	return _IsImageDrowBorder;
}

std::string TakePhotoParms::getCameraIp()
{
	return _cameraIp;

}
void TakePhotoParms::setCameraIp( std::string cameraIp )
{
	_cameraIp=cameraIp;
}

void TakePhotoParms::setCameraPass( long cameraPass )
{
	_cameraPass=cameraPass;
}

void TakePhotoParms::setFrequency( int frequency )
{
	_frequency=frequency;
}

void TakePhotoParms::setImageFormat( int imageFormat )
{
	_imageFormat=imageFormat;
}

void TakePhotoParms::setIsImageDrowBorder( bool isImageDrowBorder )
{
	_IsImageDrowBorder=isImageDrowBorder;
}

int TakePhotoParms::getCompression()
{
	return _compression;
}

void TakePhotoParms::setCompession( int comperssion)
{
	this->_compression=comperssion;
}
