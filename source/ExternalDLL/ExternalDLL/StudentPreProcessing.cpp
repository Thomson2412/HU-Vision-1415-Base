#include "StudentPreProcessing.h"
#include <cmath>
#include <iostream>


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImage *newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	for (int i = 0; i < image.getWidth() * image.getHeight(); i++){
		RGB rgbPixel =  image.getPixel(i);
		//newImage->setPixel(i, Intensity((rgbPixel.r + rgbPixel.g + rgbPixel.b) / 3));
		newImage->setPixel(i, Intensity(((rgbPixel.r*0.21) + (rgbPixel.g*0.72) + (rgbPixel.b*0.07))));
	}
	return newImage;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	IntensityImage *newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	IntensityImage *newImageBlur = new IntensityImageStudent(image.getWidth(), image.getHeight());
	char kernelBlur[3][3] = {
	{ 1, 2, 1 },
	{ 2, 4, 2 },
	{ 1, 2, 1 }
	};
	float blur;
	for (int y = 1; y < image.getHeight() - 1; y++){
		for (int x = 1; x < image.getWidth() - 1; x++){
			blur = 0.0;
			for (int k = -1; k <= 1; k++){
				for (int j = -1; j <= 1; j++){
					blur += kernelBlur[j + 1][k + 1] * image.getPixel(x - k, y - j);
				}
			}
			newImageBlur->setPixel(x, y, blur / 16);
		}
	}


	char kernel[9][9] =
	{ { 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 1, 1, 1, -4, -4, -4, 1, 1, 1 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0 } };

	for (int y = 0; y < newImage->getHeight(); y++){
		for (int x = 0; x <= newImage->getWidth(); x++){
			newImage->setPixel(x, y, 0);
		}
	}

	int sum;

	for (int y = 4; y < newImageBlur->getHeight() - 4; y++){
		for (int x = 4; x < newImageBlur->getWidth() - 4; x++){
			sum = 0;
			for (int k = -4; k <= 4; k++){
				for (int j = -4; j <= 4; j++){
					sum += kernel[k + 4][j + 4] * newImageBlur->getPixel(x - k, y - j);

				}
			}
			if (sum > 255){
				sum = 255;
			}
			else if (sum < 0){
				sum = 0;
			}
			newImage->setPixel(x, y, sum);
		}
	}
	return newImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage *intensityImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int intensityValue = 0;
	int threshold = 0;
	int offset = 150;

	for (int y = 0; y < image.getHeight(); y++){
		for (int x = 0; x <= image.getWidth(); x++){
			threshold += image.getPixel(x, y);
		}
	}
	threshold = (threshold / (image.getHeight() * image.getWidth())) + offset;
	
	for (int y = 0; y < image.getHeight(); y++){
		for (int x = 0; x < image.getWidth(); x++){
			intensityValue = image.getPixel(x, y);
			if (intensityValue >= threshold) {
				intensityValue = 0;
			} else {
				intensityValue = 255;
			}
			intensityImage->setPixel(x, y, intensityValue);
		}
	}

	return intensityImage;
}