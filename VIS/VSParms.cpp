#include "VSParms.h"



VSParms::VSParms()
{
}


VSParms::~VSParms()
{
}
void VSParms::setXScale(float xscale) {
	this->xScale = xscale;
}
void VSParms::setYScale(float yscale) {
	this->yScale = yscale;
}
void VSParms::setXShift(float xshift) {
	this->xShift = xshift;
}
void VSParms::setYShift(float yshift) {
	this->yShift = yshift;
}
void VSParms::setMaxSearchDist(int maxSearchDist) {
	this->maxSearchDist = maxSearchDist;
}
void VSParms::setUserCode(string usercode) {
	this->UserCode = usercode;
}
void VSParms::setEndoscope(string endscope) {
	this->Endoscope = endscope;
}
float VSParms::getXScale() {
	return this->xScale;
}
float VSParms::getYScale() {
	return this->yScale;
}
float VSParms::getXShift() {
	return this->xShift;
}
float VSParms::getYShift() {
	return this->yShift;
}
int VSParms::getMaxSearchDist() {
	return this->maxSearchDist;
}
string VSParms::getUserCode() {
	return this->UserCode;
}
string VSParms::getEndoscope() {
	return this->Endoscope;
}
int VSParms::getTagAreaMin() {
	return this->tagAreaMin;
}
void VSParms::setTagAreaMin(int tagAreaMin) {
	this->tagAreaMin = tagAreaMin;
}
void  VSParms::setMinlengthPx(int minlengthpx) {
	this->MinlengthPx = minlengthpx;
}
int VSParms::getMinlengthPx() {
	return MinlengthPx;
}
void VSParms::setMinCommonNum(int mincommonnum) {
	this->MinCommonNum = mincommonnum;
}
int VSParms::getMinCommonNum() {
	return MinCommonNum;
}

bool VSParms::getIsDrawCode() {
	return this->isDrawCode;
}
bool VSParms::getIsDrawTail() {

	return this->isDrawTail;
}
float VSParms::getDecodeInteval() {

	return this->decodeInteval;
}

int VSParms::getDetectMinArea() {
	return this->detectMinArea;
}
int VSParms::getDetectMaxArea() {
	return this->detectMaxArea;
}
void VSParms::setIsDrawCode(bool isDrawCode) {

	this->isDrawCode = isDrawCode;
}
void VSParms::setIsDrawTail(bool isDrawTail) {
	this->isDrawTail = isDrawTail;
}
void VSParms::setDecodeInteval(float decodeInteval) {
	this->decodeInteval = decodeInteval;
}
void VSParms::setDetectMinArea(int detectMinArea) {
	this->detectMinArea = detectMinArea;
}
void VSParms::setDetectMaxArea(int detectMaxArea) {
	this->detectMaxArea = detectMaxArea;
}
float VSParms::getDecodeThresh() {
	return this->decodeThresh;
}
void VSParms::setDecodeThresh(float decodeThresh) {
	this->decodeThresh = decodeThresh;
}
void VSParms::setIsTest(int isTest) {
	this->IsTest = isTest;
}
int  VSParms::getIsTest() {
	return this->IsTest;
}

void VSParms::setLableCols(int lableCols) {
	this->lableCols = lableCols;
}
int VSParms::getLableCols() {
	return this->lableCols;
}
void VSParms::setLableRows(int lableRows) {
	this->lableRows = lableRows;
}
int VSParms::getLableRows() {
	return this->lableRows;
}
void VSParms::setDeviceCapturePicture(int deviceCapturePicture) {
	this->deviceCapturePicture = deviceCapturePicture;
}
int VSParms::getDeviceCapturePicture() {
	return this->deviceCapturePicture;
}

int VSParms::getVideoDecoder() {

	return this->videoDecoder;
}
void VSParms::setVideoDecoder(int videoDecoder) {
	this->videoDecoder = videoDecoder;
}

void VSParms::setIsRgbCheck(int isRgbCheck) {

	this->isRgbCheck = isRgbCheck;
}
int VSParms::getIsRgbCheck() {
	return this->isRgbCheck;
}
void VSParms::setpShiftX(int pshiftx) {
	this->pShiftX = pshiftx;
}
void VSParms::seteShiftX(int eshiftx) {
	this->eShiftX = eshiftx;
}
int VSParms::getpShiftX() {
	return this->pShiftX;
}
int VSParms::geteShiftX() {
	return this->eShiftX;
}

int VSParms::getBloodMax() {
	return this->bloodMax;
}
float VSParms::getScale() {
	return this->scale;
}
int VSParms::getInnerThresh() {
	return this->innerThresh;
}
int VSParms::getLablemargin() {
	return this->lablemargin;
}
int VSParms::getCellsize() {
	return this->cellsize;

}
void VSParms::setBloodMax(int bloodmax) {
	this->bloodMax = bloodmax;
}
void VSParms::setScale(float scale) {
	this->scale = scale;
}
void VSParms::setInnerThresh(int innerthresh) {
	this->innerThresh = innerthresh;
}
void VSParms::setLablemargin(int lablemargin) {
	this->lablemargin = lablemargin;
}
void VSParms::setCellsize(int cellsize) {
	this->cellsize = cellsize;
}
void VSParms::setTankwscale(float tankWidth) {
	this->tankwscale = tankWidth;
}
float VSParms::getTankwscale() {
	return this->tankwscale;
}
void VSParms::setTotalFrameNum(int totalFrameNum) {
	this->totalFrameNum = totalFrameNum;
};
void VSParms::setWorkSpaceTime(int workSpaceTime) {
	this->workSpaceTime = workSpaceTime;
};
void VSParms::setMinFrameNum(int minFrameNum) {
	this->minFrameNum = minFrameNum;
};
void VSParms::setCleanInfectionMachineFrameNum(int cleanInfectionMachineFrameNum) {
	this->cleanInfectionMachineFrameNum = cleanInfectionMachineFrameNum;
};
int VSParms::getTotalFrameNum() {
	return this->totalFrameNum;
};
int VSParms::getWorkSpaceTime() {
	return this->workSpaceTime;
};
int VSParms::getMinFrameNum() {
	return this->minFrameNum;
};
int VSParms::getCleanInfectionMachineFrameNum() {
	return this->cleanInfectionMachineFrameNum;
};
void VSParms::setIsDynamicSetFrameRate(bool isDynamicSetFrameRate) {
	this->isDynamicSetFrameRate = isDynamicSetFrameRate;
}
bool VSParms::getIsDynamicSetFrameRate() {
	return this->isDynamicSetFrameRate;
}

int VSParms::getRgbFrameRate() {
	return this->RgbFrameRate;
}
void VSParms::setRgbFrameRate(int rgbFrameRate) {
	this->RgbFrameRate = rgbFrameRate;
}
int VSParms::getIRMaxFrameRate() {
	return this->IRMaxFrameRate;
}
void VSParms::setIRMaxFrameRate(int irMaxFrameRate) {
	this->IRMaxFrameRate = irMaxFrameRate;
}
int VSParms::getIRMinFrameRate() {

	return this->IRMinFrameRate;
}
void VSParms::setIRMinFrameRate(int irMinFrameRate) {

	this->IRMinFrameRate = irMinFrameRate;
}

int VSParms::getIsCupUseOptimized() {
	return this->IsCupUseOptimized;
}
void VSParms::setIsCupUseOptimized(int isCupUseOptimized) {
	this->IsCupUseOptimized = isCupUseOptimized;
}
int VSParms::getPreTime() {
	return this->preTime;
}
void VSParms::setPreTime(int preTime) {
	this->preTime = preTime;
}

int VSParms::getTipCount() {
	return this->tipcount;
}
void VSParms::setTipCount(int count) {
	this->tipcount = count;
}

int VSParms::getValidateNum() {
	return this->validatenum;
}
void VSParms::setValidateNum(int num) {
	this->validatenum = num;
}

int VSParms::getIsOpenillation() {

	return this->IsOpenillation;
}
void VSParms::setIsOpenillation(int isopenillation) {
	this->IsOpenillation = isopenillation;
}

bool VSParms::getIsPureIRLableIdentification() {
	return this->IsPureIRLableIdentification;
}
void VSParms::setIsPureIRLableIdentification(bool isPureIRLableIdentification) {
	this->IsPureIRLableIdentification = isPureIRLableIdentification;
}

bool VSParms::getIsRgbDryCheck(){
	return this->IsRgbDryCheck;
}
void VSParms::setIsRgbDryCheck(bool isRgbDryCheck)
{
	this->IsRgbDryCheck = isRgbDryCheck;
}

int VSParms::getOpenillationTimeBySecond() {
	return this->OpenillationTimeBySecond;
}
void VSParms::setOpenillationTimeBySecond(int openillationTimeBySecond) {
	this->OpenillationTimeBySecond = openillationTimeBySecond;
}

int VSParms::getRgbcheckFrameNum() {
	return this->RgbcheckFrameNum;
}
void VSParms::setRgbcheckFrameNum(int rgbcheckFrameNum) {
	this->RgbcheckFrameNum = rgbcheckFrameNum;
}

int VSParms::getIsDemo() {
	return this->IsDemo;
}
void VSParms::setIsDemo(int isdemo) {
	this->IsDemo = isdemo;
}

std::string VSParms::getEndoscopeTestNameForDemo() {
	return this->EndoscopeTestNameForDemo;
}
void VSParms::setEndoscopeTestNameForDemo(std::string name) {
	this->EndoscopeTestNameForDemo = name;
}

int VSParms::getUserTestCodeForDemo() {
	return this->UserTestCodeForDemo;
}
void VSParms::setUserTestCodeForDemo(int code) {
	this->UserTestCodeForDemo = code;
}

std::string VSParms::getUserTestNameForDemo() {
	return this->UserTestNameForDemo;
}
void VSParms::setUserTestNameForDemo(std::string name) {
	this->UserTestNameForDemo = name;
}

std::string VSParms::getDefaultEndoscopeTestNameForDemo() {
	return this->DefaultEndoscopeTestNameForDemo;
}
void VSParms::setDefaultEndoscopeTestNameForDemo(std::string name) {
	this->DefaultEndoscopeTestNameForDemo = name;
}

std::string VSParms::getWeights() {
	return this->Weights;
}
std::string VSParms::getCFG() {
	return this->CFG;
}
std::string VSParms::getLNames() {
	return this->LNames;
}
void VSParms::setWeights(std::string name) {
	this->Weights = name;
}
void  VSParms::setCFG(std::string name) {
	this->CFG = name;
}
void VSParms::setLNames(std::string name) {
	this->LNames = name;
}

int VSParms::getIsDryIRLableIdentification() 
{
    return this->IsDryIRLableIdentification;
}
void VSParms::setIsDryIRLableIdentification(int isDryIRLableIdentification)
{
	this->IsDryIRLableIdentification = isDryIRLableIdentification;
}

int  VSParms::getIsTrackUser() {
	return this->IsTrackUser;
}
void  VSParms::setIsTrackUser(int istrackuser) {
	this->IsTrackUser = istrackuser;
}