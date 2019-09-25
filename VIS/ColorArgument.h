#pragma once
class ColorArgument
{
   public:
	ColorArgument();
	~ColorArgument();
	void setTypeid(int type_id);
	void setHueNormal(int hue_normal);
	void setHueUpVal(int hue_up_val);
	void setHueDownVal(int hue_down_val);
	void setSaturationNormal(int saturation_normal);
	void setSaturationUpVal(int saturation_up_val);
	void setSaturationDownVal(int saturation_down_val);
	void setValueNormal(int value_normal);
	void setValueUpVal(int value_up_val);
	void setValueDownVal(int value_down_val);
	int getTypeid();
	int getHueNormal();
	int getHueUpVal();
	int getHueDownVal();
	int getSaturationNormal();
	int getSaturationUpVal();
	int getSaturationDownVal();
	int getValueNormal();
	int getValueUpVal();
	int getValueDownVal();
private:
	int type_id;
	int hue_normal;
	int hue_up_val;
	int hue_down_val;
	int saturation_normal;
	int saturation_up_val;
	int saturation_down_val;
	int value_normal;
	int value_up_val;
	int value_down_val;
};

