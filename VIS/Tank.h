#pragma once
#include <string>
using namespace std;
class Tank
{
public:
	Tank(void);
	~Tank(void);
	void setTank_type(string tankType);
	string getTank_type();
	void setTank_id(int tank_id);
	int getTank_id();
	void setTank_name(string tank_name);
	string getTank_name();
	void setTank_group_id(string tank_group_id);
	string getTank_group_id();
	void setCamera_ip(string camera_ip);
	string getCamera_id();
	void setCamera_channal(int camera_channal);
	int getCamera_channal();
	void setCamera_type(string camera_type);
	string getCamera_type();
	void setArea_1_ltx(int area_1_ltx);
	int getArea_l_ltx();
	void setArea_1_lty(int area_1_lty);
	int getArea_1_lty();
	void setArea_1_rbx(int area_1_rbx);
	int getArea_1_rbx();
	void setArea_1_rby(int area_1_rby);
	int getArea_1_rby();
	void setArea_2_ltx(int area_1_ltx);
	int getArea_2_ltx();
	void setArea_2_lty(int area_1_lty);
	int getArea_2_lty();
	void setArea_2_rbx(int area_1_rbx);
	int getArea_2_rbx();
	void setArea_2_rby(int area_1_rby);
	int getArea_2_rby();
	void setExposure_val(int exposure_val);
	int getExposure_val();
private:
	string tank_type;
	int tank_id;
	string tank_group_id;
	string tank_name;
	string camera_ip;
	int   camera_channal;
	string camera_type;
	int area_1_ltx;
	int area_1_lty;
	int area_1_rbx;
	int area_1_rby;
	int area_2_ltx;
	int area_2_lty;
	int area_2_rbx;
	int area_2_rby;
	int exposure_val;
};

