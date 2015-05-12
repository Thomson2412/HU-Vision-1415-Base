#include "StudentLocalization.h"
#include <iostream>

bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	Point2D<double> headTop;
	Point2D<double> headLeft;
	Point2D<double> headRight;
	if (features.hasFeature(Feature::FEATURE_HEAD_TOP) && 
		features.hasFeature(Feature::FEATURE_HEAD_LEFT_SIDE) && 
		features.hasFeature(Feature::FEATURE_HEAD_RIGHT_SIDE)){
		headTop = features.getFeature(Feature::FEATURE_HEAD_TOP).getPoints()[0];
		headLeft = features.getFeature(Feature::FEATURE_HEAD_LEFT_SIDE).getPoints()[0];
		headRight = features.getFeature(Feature::FEATURE_HEAD_RIGHT_SIDE).getPoints()[0];
		std::cout << headTop << std::endl;
		std::cout << headLeft << std::endl;
		std::cout << headRight << std::endl;
	}
	double segmentWidth = ((headRight.getX() - headLeft.getX()) / 4)-10;
	double segmentHeight = 70;
	double segmentX = headTop.getX() - (segmentWidth / 2);
	double segmentY = headLeft.getY() - 20;


	std::cout << "segmentWidth: " << segmentWidth << " segmentHeight: " << segmentHeight << std::endl;
	std::cout << "segmentX: " << segmentX << " segmentY: " << segmentY << std::endl;
	Point2D<double> featureFoundList[40];
	int count = 0;
	int blackCount = 0;
	int lastPixel = 0;
	for (int y = segmentY; y < (segmentHeight + segmentY); y++){
		bool featureFound = true;
		for (int x = segmentX; x < segmentX + (segmentWidth); x++){
			Intensity pixel = image.getPixel(x,y);
			if (pixel == 255){
				featureFound = false;
				break;
			}
			if (pixel == 0){
				++blackCount;
			}
		}
		if (featureFound && y > lastPixel + 2){
			lastPixel = y;
			featureFoundList[count] = Point2D<double>(segmentX + (segmentWidth/2),y);
			++count;
		}
		std::cout << "y: " << y << " blackCount: " << blackCount << std::endl;
		blackCount = 0;
	}
	for (int i = 0; i < count; i++){
		std::cout << featureFoundList[i].getY() << std::endl;
	}

	Feature FT;
	FT = Feature(Feature::FEATURE_NOSE_BOTTOM, Point2D<double>(featureFoundList[0]));
	features.putFeature(FT);

	FT = Feature(Feature::FEATURE_MOUTH_TOP, Point2D<double>(featureFoundList[1].getX(), featureFoundList[1].getY() - 2));
	features.putFeature(FT);
	FT = Feature(Feature::FEATURE_MOUTH_CENTER, Point2D<double>(featureFoundList[1].getX(), featureFoundList[1].getY()));
	features.putFeature(FT);
	FT = Feature(Feature::FEATURE_MOUTH_BOTTOM, Point2D<double>(featureFoundList[1].getX(), featureFoundList[1].getY() + 2 ));
	features.putFeature(FT);

	FT = Feature(Feature::FEATURE_CHIN, Point2D<double>(featureFoundList[2]));
	features.putFeature(FT);



	return true;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	return false;
}