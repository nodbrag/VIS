#pragma once
class VISetting
{
public:
	VISetting(void);
	~VISetting(void);
	bool getIsPersonIdentified();
	void setIsPersonIdentified(bool isPersonIdentified);
	bool getIsEndoscopeIdentified();
	void setIsEndoscopeIdentified(bool isEndoscopeIdentified);
	bool getIsGunIdentified();
	void setIsGunIdentified(bool isGunIdentified);
	bool getIsTransferEnzymeLiquidIdentified();
	void setIsTransferEnzymeLiquidIdentified(bool isTransferEnzymeLiquidIdentified);
	bool getIsTransferInfectionLiquidIdentified();
	void setIsTransferInfectionLiquidIdentified(bool isTransferInfectionLiquidIdentified);
	bool getIsTransferClothIdentified();
	void setIsTransferClothIdentified(bool isTransferClothIdentified);
private:
	//是否需要人员识别
	bool _isPersonIdentified;
	//是否需要内镜识别
	bool _isEndoscopeIdentified;
	//是否需要枪识别
	bool _isGunIdentified;
	//是否需要酶洗换液识别
	bool _isTransferEnzymeLiquidIdentified;
	//是否需要消毒换液识别
	bool _isTransferInfectionLiquidIdentified;
	//是否需要换布识别
	bool _isTransferClothIdentified;
};

