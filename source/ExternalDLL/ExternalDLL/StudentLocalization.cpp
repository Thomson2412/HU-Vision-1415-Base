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
		//std::cout << headTop << std::endl;
		//std::cout << headLeft << std::endl;
		//std::cout << headRight << std::endl;
	}

	double segmentWidth = ((headRight.getX() - headLeft.getX()) / 4) - 5;
	double segmentHeight = image.getHeight() - headLeft.getY();
	double segmentX = headTop.getX() - (segmentWidth / 2);
	double segmentY = headLeft.getY() - 18;


	//std::cout << "segmentWidth: " << segmentWidth << " segmentHeight: " << segmentHeight << std::endl;
	//std::cout << "segmentX: " << segmentX << " segmentY: " << segmentY << std::endl;
	//std::cout << "X: " << headTop.getX() << std::endl;


	Point2D<double> featureFoundList[4];
	int featureFoundCount = 0;
	int blackCount = 0;
	int lastPixel = 0;
	int lastFoundY = 0;
	int blackFoundCount = 0;


	for (int y = segmentY; y < (segmentHeight + segmentY); ++y){
		if (featureFoundCount > 3) break;
		bool featureFound = false;
		for (int x = segmentX; x < segmentX + (segmentWidth); ++x){
			if (image.getPixel(x, y) == 0){
				++blackCount;
			}
		}
		if (blackCount >= 7) {
			++blackFoundCount;
			lastFoundY = y;
		}
		else{
			featureFound = true;
		}
		if (featureFound && lastFoundY > 0 && blackFoundCount > 1){
			featureFoundList[featureFoundCount] = Point2D<double>(headTop.getX(), lastFoundY);
			++featureFoundCount;
			lastFoundY = 0;
			blackFoundCount = 0;
		}
		//std::cout << "y: " << y << " blackCount: " << blackCount << std::endl;
		blackCount = 0;
	}
	
	//for (int i = 0; i < featureFoundCount; i++){
	//	std::cout << featureFoundList[i].getY() << std::endl;
	//}

	if (featureFoundCount > 3){
		//std::cout << "Count > 3" << std::endl;
		Feature FT;
		FT = Feature(Feature::FEATURE_NOSE_BOTTOM, Point2D<double>(featureFoundList[0]));
		//std::cout << "NOSE_BOTTOM: " << featureFoundList[0].getY() << std::endl;
		features.putFeature(FT);

		FT = Feature(Feature::FEATURE_MOUTH_TOP, Point2D<double>(featureFoundList[1].getX(), featureFoundList[1].getY()));
		//std::cout << "MOUTH_TOP: " << featureFoundList[1].getY() << std::endl;
		features.putFeature(FT);
		FT = Feature(Feature::FEATURE_MOUTH_CENTER, Point2D<double>(featureFoundList[1].getX(), ((featureFoundList[1].getY() + featureFoundList[2].getY()) / 2)));
		//std::cout << "MOUTH_CENTER: " << (featureFoundList[1].getY() + featureFoundList[2].getY()) / 2 << std::endl;
		features.putFeature(FT);
		FT = Feature(Feature::FEATURE_MOUTH_BOTTOM, Point2D<double>(featureFoundList[2]));
		//std::cout << "MOUTH_BOTTOM: " << featureFoundList[2].getY() << std::endl;
		features.putFeature(FT);

		FT = Feature(Feature::FEATURE_CHIN, Point2D<double>(featureFoundList[3]));
		//std::cout << "FEATURE_CHIN: " << featureFoundList[3].getY() << std::endl;
		features.putFeature(FT);
	}
	else if (featureFoundCount == 3){
		//std::cout << "Count = 3" << std::endl;
		Feature FT;
		FT = Feature(Feature::FEATURE_NOSE_BOTTOM, Point2D<double>(featureFoundList[0]));
		features.putFeature(FT);

		FT = Feature(Feature::FEATURE_MOUTH_TOP, Point2D<double>(featureFoundList[1].getX(), featureFoundList[1].getY()));
		features.putFeature(FT);
		FT = Feature(Feature::FEATURE_MOUTH_CENTER, Point2D<double>(featureFoundList[1].getX(), featureFoundList[1].getY() + 2));
		features.putFeature(FT);
		FT = Feature(Feature::FEATURE_MOUTH_BOTTOM, Point2D<double>(featureFoundList[1].getX(), featureFoundList[1].getY() + 4));
		features.putFeature(FT);

		FT = Feature(Feature::FEATURE_CHIN, Point2D<double>(featureFoundList[2]));
		features.putFeature(FT);
	}
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