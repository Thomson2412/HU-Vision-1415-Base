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
	float max = 200;
	int width = image.getWidth();
	int height = image.getHeight();
	float ratio = 0;

	if (image.getWidth() > image.getHeight() && image.getWidth() > max){
		//std::cout << "w > m" << std::endl;
		ratio = max / image.getWidth();
	}
	else if (image.getHeight() > max){
		//std::cout << "w > h" << std::endl;
		ratio = max / image.getHeight();
	}
	if (ratio > 0){
		height = image.getHeight() * ratio;
		width = image.getWidth() * ratio;
	}
	//std::cout << ratio << std::endl;
	//std::cout << image.getHeight() << std::endl << image.getWidth() << std::endl;
	//std::cout << height << std::endl << width << std::endl;
	IntensityImage *newImage = new IntensityImageStudent(width, height);
	int A, B, C, D, x, y, index, gray;
	float x_ratio = ((float)(image.getWidth() - 1)) / width;
	float y_ratio = ((float)(image.getHeight() - 1)) / height;
	float x_diff, y_diff, ya, yb;
	int offset = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			x = (int)(x_ratio * j);
			y = (int)(y_ratio * i);
			x_diff = (x_ratio * j) - x;
			y_diff = (y_ratio * i) - y;
			index = y*image.getWidth() + x;

			A = image.getPixel(index);
			B = image.getPixel(index+1);
			C = image.getPixel(index+image.getWidth());
			D = image.getPixel(index+image.getWidth()+1);

			// Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
			gray = (int)(
				A*(1 - x_diff)*(1 - y_diff) + B*(x_diff)*(1 - y_diff) +
				C*(y_diff)*(1 - x_diff) + D*(x_diff*y_diff)
				);

			newImage->setPixel(offset++, gray);
		}
	}



	return newImage;
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