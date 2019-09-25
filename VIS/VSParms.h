#pragma once
#include <string>
using namespace std;
class VSParms
{
public:
	VSParms();
	~VSParms();
	void setXScale(float xscale);
	void setYScale(float yscale);
	void setXShift(float xshift);
	void setYShift(float yshift);
	void setMaxSearchDist(int maxSearchDist);
	void setUserCode(string usercode);
	void setEndoscope(string endscope);
	void setTagAreaMin(int tagAreaMin);
	float getXScale();
	float getYScale();
	float getXShift();
	float getYShift();
	int getMaxSearchDist();
	int getTagAreaMin();
	string getUserCode();
	string getEndoscope();
	void  setMinlengthPx(int minlengthpx);
	int getMinlengthPx();
	void setMinCommonNum(int mincommonnum);
	int getMinCommonNum();
	bool getIsDrawCode();
	bool getIsDrawTail();
	float getDecodeInteval();
	int getDetectMinArea();
	int getDetectMaxArea();
	float getDecodeThresh();
	void setIsDrawCode(bool isDrawCode);
	void setIsDrawTail(bool isDrawTail);
	void setDecodeInteval(float decodeInteval);
	void setDetectMinArea(int detectMinArea);
	void setDetectMaxArea(int detectMaxArea);
	void setDecodeThresh(float decodeThresh);
	void setIsTest(int test);
	int  getIsTest();
	void setLableCols(int lableCols);
	int getLableCols();
	void setLableRows(int lableRows);
	int getLableRows();
	void setDeviceCapturePicture(int deviceCapturePicture);
	int getDeviceCapturePicture();
	int getVideoDecoder();
	void setVideoDecoder(int videoDecoder);
	void setIsRgbCheck(int isRgbCheck);
	int getIsRgbCheck();
	void setpShiftX(int pshiftx);
	void seteShiftX(int eshiftx);
	int getpShiftX();
	int geteShiftX();
	int getBloodMax();
	float getScale();
	int getInnerThresh();
	int getLablemargin();
	int getCellsize();
	void setBloodMax(int bloodmax);
	void setScale(float scale);
	void setInnerThresh(int innerthresh);
	void setLablemargin(int lablemargin);
	void setCellsize(int cellsize);
	void setTankwscale(float tankWidth);
	float getTankwscale();
	void setTotalFrameNum(int totalFrameNum);
	void setWorkSpaceTime(int workSpaceTime);
	void setMinFrameNum(int minFrameNum);
	void setCleanInfectionMachineFrameNum(int cleanInfectionMachineFrameNum);
	int getTotalFrameNum();
	int getWorkSpaceTime();
	int getMinFrameNum();
	int getCleanInfectionMachineFrameNum();
	void setIsDynamicSetFrameRate(bool isDynamicSetFrameRate);
	bool getIsDynamicSetFrameRate();
	int getRgbFrameRate();
	void setRgbFrameRate(int rgbFrameRate);
	int getIRMaxFrameRate();
	void setIRMaxFrameRate(int irMaxFrameRate);
	int getIRMinFrameRate();
	void setIRMinFrameRate(int irMinFrameRate);
	int getIsCupUseOptimized();
	void setIsCupUseOptimized(int isCupUseOptimized);
	int getPreTime();
	void setPreTime(int preTime);

	int getTipCount();
	void setTipCount(int count);

	int getValidateNum();
	void setValidateNum(int num);

	int getIsOpenillation();
	void setIsOpenillation(int isopenillation);

	bool getIsPureIRLableIdentification();
	void setIsPureIRLableIdentification(bool isPureIRLableIdentification);

	bool getIsRgbDryCheck();
	void setIsRgbDryCheck(bool isRgbDryCheck);

	int getOpenillationTimeBySecond();
	void setOpenillationTimeBySecond(int openillationTimeBySecond);

	int getRgbcheckFrameNum();
	void setRgbcheckFrameNum(int rgbcheckFrameNum);

	int getIsDemo();
	void setIsDemo(int isdemo);

	std::string getEndoscopeTestNameForDemo();
	void setEndoscopeTestNameForDemo(std::string name);

	int getUserTestCodeForDemo();
	void setUserTestCodeForDemo(int code);

	std::string getUserTestNameForDemo();
	void setUserTestNameForDemo(std::string name);


	std::string getDefaultEndoscopeTestNameForDemo();
	void setDefaultEndoscopeTestNameForDemo(std::string name);

	std::string getWeights();
	std::string getCFG();
	std::string getLNames();
	void setWeights(std::string name);
	void  setCFG(std::string name);
	void setLNames(std::string name);

	int getIsDryIRLableIdentification();
	void setIsDryIRLableIdentification(int isDryIRLableIdentification);

	int getIsTrackUser();
	void setIsTrackUser(int istrackuser);
private:
	float xScale;
	float yScale;
	float xShift;
	float yShift;
	int  maxSearchDist;
	int  tagAreaMin;
	string UserCode;
	string Endoscope;
	int MinlengthPx;
	int MinCommonNum;
	bool isDrawCode;
	bool isDrawTail;
	float decodeInteval;
	int detectMinArea;
	int detectMaxArea;
	float decodeThresh;
	int IsTest;
	int lableCols;
	int lableRows;
	int deviceCapturePicture;
	int videoDecoder;
	int isRgbCheck;
	int pShiftX;
	int eShiftX;
	int bloodMax;
	float scale;
	int innerThresh;
	int lablemargin;
	int cellsize;
	float tankwscale;
	int totalFrameNum;
	int workSpaceTime;
	int minFrameNum;
	int cleanInfectionMachineFrameNum;
	bool isDynamicSetFrameRate;
	int RgbFrameRate;
	int IRMaxFrameRate;
	int IRMinFrameRate;
	int IsCupUseOptimized;
	int preTime;
	int tipcount;
	int validatenum;
	int IsOpenillation;
	//�Ƿ񴿱�ǩʶ��
	bool IsPureIRLableIdentification;
	//�Ƿ�rgb ����̨�Ƿ���
	bool IsRgbDryCheck;
	//�ƶϼ��ʱ�䣨�룩
	int OpenillationTimeBySecond;
	//�ж��뾵֡��
	int RgbcheckFrameNum;
	//�Ƿ���ʾ
    int IsDemo;

	std::string EndoscopeTestNameForDemo;
	//��ʾ�����û�����
	int UserTestCodeForDemo;
	//�û�����
	std::string UserTestNameForDemo;

	std::string DefaultEndoscopeTestNameForDemo;

	//yoloѵ����ʼ���ļ�
	std::string Weights;
	std::string CFG;
	std::string LNames;

	//�Ƿ����̨��ǩʶ��
	int IsDryIRLableIdentification;
	//�Ƿ������
	int IsTrackUser;
};

