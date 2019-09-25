#include "VISetting.h"


VISetting::VISetting(void)
{
}

VISetting::~VISetting(void)
{
}
bool VISetting::getIsPersonIdentified()
{
	return _isPersonIdentified;
}

void VISetting::setIsPersonIdentified( bool isPersonIdentified )
{
	_isPersonIdentified=isPersonIdentified;
}

bool VISetting::getIsEndoscopeIdentified()
{
	return _isEndoscopeIdentified;
}

void VISetting::setIsEndoscopeIdentified( bool isEndoscopeIdentified )
{
	_isEndoscopeIdentified=isEndoscopeIdentified;
}

bool VISetting::getIsGunIdentified()
{
	return _isGunIdentified;
}

void VISetting::setIsGunIdentified( bool isGunIdentified )
{
	_isGunIdentified=isGunIdentified;
}

bool VISetting::getIsTransferClothIdentified()
{
	return _isTransferClothIdentified;
}

void VISetting::setIsTransferClothIdentified( bool isTransferClothIdentified )
{
	_isTransferClothIdentified=isTransferClothIdentified;
}

void VISetting::setIsTransferEnzymeLiquidIdentified( bool isTransferEnzymeLiquidIdentified )
{
	 this->_isTransferEnzymeLiquidIdentified=isTransferEnzymeLiquidIdentified;
}

bool VISetting::getIsTransferEnzymeLiquidIdentified()
{
	return this->_isTransferEnzymeLiquidIdentified;
}

bool VISetting::getIsTransferInfectionLiquidIdentified()
{
	return this->_isTransferInfectionLiquidIdentified;
}

void VISetting::setIsTransferInfectionLiquidIdentified( bool isTransferInfectionLiquidIdentified )
{
	this->_isTransferInfectionLiquidIdentified=isTransferInfectionLiquidIdentified;
}
