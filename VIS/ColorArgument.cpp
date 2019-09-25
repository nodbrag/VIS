#include "ColorArgument.h"

ColorArgument::ColorArgument()
{

}
ColorArgument::~ColorArgument()
{

}
void ColorArgument::setTypeid(int type_id){
	this->type_id = type_id;
}
void ColorArgument::setHueNormal(int hue_normal) {
	this->hue_normal = hue_normal;
}
void ColorArgument::setHueUpVal(int hue_up_val) {
	this->hue_up_val = hue_up_val;
}
void ColorArgument::setHueDownVal(int hue_down_val) {
	this->hue_down_val = hue_down_val;
}
void ColorArgument::setSaturationNormal(int saturation_normal) {
	this->saturation_normal = saturation_normal;
}
void ColorArgument::setSaturationUpVal(int saturation_up_val) {
	this->saturation_up_val = saturation_up_val;
}
void ColorArgument::setSaturationDownVal(int saturation_down_val) {
	this->saturation_down_val = saturation_down_val;
}
void ColorArgument::setValueNormal(int value_normal) {
	this->value_normal = value_normal;
}
void ColorArgument::setValueUpVal(int value_up_val) {
	this->value_up_val = value_up_val;
}
void ColorArgument::setValueDownVal(int value_down_val) {
	this->value_down_val = value_down_val;
}
int ColorArgument::getTypeid() {
	return this->type_id;
}
int ColorArgument::getHueNormal() {
    return this->type_id;
}
int ColorArgument::getHueUpVal() {
	return this->hue_up_val;
}
int ColorArgument::getHueDownVal() {
	return this->hue_down_val;
}
int ColorArgument::getSaturationNormal() {
	return  this->saturation_normal;
}
int ColorArgument::getSaturationUpVal() {
	return this->saturation_up_val;
}
int ColorArgument::getSaturationDownVal() {
	return this->saturation_down_val;
}
int ColorArgument::getValueNormal() {
	return this->value_normal;
}
int ColorArgument::getValueUpVal() {
	return this->value_up_val;
}
int ColorArgument::getValueDownVal() {
	return this->value_down_val;
}
