#include "VICoreInterface.h"
#include "Common.h"


VICoreInterface::VICoreInterface()
{
	

}

VICoreInterface::~VICoreInterface()
{
	  
}
void VICoreInterface::init(int mincommonnum, bool isDrawCode, bool isDrawTail, float decodeInteval, float detectMinArea, float detectMaxArea,int eshiftx,int pshiftx,int bloodMax,float scale,int innerThresh, std::map<int,std::vector<int>> colorval) {

	this->cmap.clear();

	//ͼ������
	CEndoCore ec;
	string path = Common::GetCurrentPath();
	try
	{
		/*ec.ImportIcon("27", path + "/person.png");
		ec.ImportIcon("0201", path + "/endoscope.png");*/

		//�����ò���
		int startFrame = 0;		//��Ƶ��ʼ֡��
		int wait = 1;			//��ʾ�ȴ�ʱ��

		ec.trace.distMax = 100.f;

		if (mincommonnum > 0) {
			//�����С�ȶ�����
			ec.trace.sameCodeCntMax = mincommonnum;
		}
		ec.trace.drawCode = isDrawCode;
		ec.trace.drawTail = isDrawTail;
		//ec.preProcThreshInner =30.;
		//ec.preProcThreshOuter = 15.;
		//ec.preProcThreshRange = 550;
		ec.trace.bloodMax = bloodMax;
		ec.minArea = detectMinArea;
		ec.scale = scale;
		ec.maxArea = detectMaxArea;
		ec.eshiftx = eshiftx;
		ec.pshiftx = pshiftx;
		ec.innerthresh = innerThresh; //��ֵ����ֵ Խ����ϰ����ڣ����ܱ�Եʶ��Ч�����á�
		ec.colorVal = colorval;
		this->core = ec;
	}
	catch (const std::exception& ex)
	{
		printf_s("%s", std::string(ex.what()).c_str());
	}
	
}
int VICoreInterface::viCall(string rgbId, cv::Mat rgbImg, string irId, cv::Mat irImg, vector<int> flags, int tankWidth, map<int, vector<Rect> > roiRects, cv::Mat &overlayImg, map<int, vector<vector<string> > > &objs, string &errorMsg)
{
	//ָ��ͼ��������
	this->core.flags = flags;
	//ָ������Ȥ���� 
	this->core.roiRects = roiRects;
	if (this->cmap.count(0) == 0) {
		if (minlengthpx <= 0) { 
			minlengthpx = 35;
		}
		//��ʼ����ǩ������� 
		this->core.tag.Init(lableRows, lableCols, lablemargin, cellsize,validatenum,decodeThresh);
		cmap.insert(make_pair(0,0));
	}
	if (isCupUseOptimized) {
		cv::setUseOptimized(false);
	}
	return  this->core.Process(rgbId, tankWidth,irImg, rgbImg, overlayImg, objs, errorMsg);
}
int VICoreInterface::IrCheck(cv::Rect irROI, std::string ip, Mat irimg, cv::Mat &overlayImg, map<int, vector<vector<string>>> &objs, string &errorMsg) {
	if (this->cmap.count(0) == 0) {
		if (minlengthpx <= 0) {
			minlengthpx = 35;
		}
		//��ʼ����ǩ������� 
		this->core.tag.Init(lableRows, lableCols, lablemargin, cellsize, validatenum, decodeThresh);
		cmap.insert(make_pair(0, 0));
	}
	if (isCupUseOptimized) {
		cv::setUseOptimized(false);
	}
	return  this->core.IrCheck(irROI,ip,irimg, overlayImg,objs,errorMsg);
}
void VICoreInterface::SaveRgbImageMat(cv::Mat rgb, std::string rgbip,std::string irip, std::string tankGroupid) {
	this->core.SaveRgbImageMat(rgb, rgbip,irip, tankGroupid);
}