#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() : RGBImage() {
	//int throwError = 0, e = 1 / throwError; //Throws error without the need to include a header
	//TODO: Nothing
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: Create a copy from the other object
	RGBImageStudent temp =  RGBImageStudent(other.getWidth(),other.getHeight());
	temp.setAllPixels(getAllPixels());
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : 
RGBImage(width, height),
width(width),
height(height){
	//int throwError = 0, e = 1 / throwError;
	//TODO: Initialize pixel storage
	pixelData.resize(width*height);
	
}

RGBImageStudent::~RGBImageStudent() {
	//int throwError = 0, e = 1 / throwError;
	//TODO: delete allocated objects
}

void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage (Don't forget to delete the old storage)
	pixelData.clear();
	pixelData.resize(width*height);
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	//int throwError = 0, e = 1 / throwError;
	//TODO: resize or create a new pixel storage and copy the object (Don't forget to delete the old storage)
	set(other.getWidth(), other.getHeight());
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	int i = 0;
	if (y != 0){
		int temp = width * (y - 1);
		i = temp + x;
	}
	i = x;
	setPixel(i,pixel);
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
	//int throwError = 0, e = 1 / throwError;
	/*
	* TODO: set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/
	pixelData[i] = pixel;
}

RGB RGBImageStudent::getPixel(int x, int y) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: no comment needed :)
	int i = 0;
	if (y != 0){
		int temp = width * (y - 1);
		i = temp + x;
	}
	i = x;
	return getPixel(i);
}

RGB RGBImageStudent::getPixel(int i) const {
	//int throwError = 0, e = 1 / throwError;
	//TODO: see setPixel(int i, RGB pixel)
	return pixelData[i];
}

std::vector<RGB> RGBImageStudent::getAllPixels(){
	return pixelData;
}
void RGBImageStudent::setAllPixels(std::vector<RGB> pD){
	pixelData = pD;
}