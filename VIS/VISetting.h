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
	//�Ƿ���Ҫ��Աʶ��
	bool _isPersonIdentified;
	//�Ƿ���Ҫ�ھ�ʶ��
	bool _isEndoscopeIdentified;
	//�Ƿ���Ҫǹʶ��
	bool _isGunIdentified;
	//�Ƿ���Ҫøϴ��Һʶ��
	bool _isTransferEnzymeLiquidIdentified;
	//�Ƿ���Ҫ������Һʶ��
	bool _isTransferInfectionLiquidIdentified;
	//�Ƿ���Ҫ����ʶ��
	bool _isTransferClothIdentified;
};

