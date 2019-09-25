#pragma once
#include <string>
using namespace std;
class SimulatedData
{
public:
	SimulatedData(string ecode,int x,int y);
	~SimulatedData(void);
	void setEcode(string ecode);
	string getEcode();
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
private:
	string ecode;
	int x;
	int y;
};

