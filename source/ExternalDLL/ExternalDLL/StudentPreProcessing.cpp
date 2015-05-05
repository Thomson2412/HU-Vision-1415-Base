#include "StudentPreProcessing.h"
#include <cmath>
#include <iostream>


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	IntensityImage *newImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	for (int i = 0; i < image.getWidth() * image.getHeight(); i++){
		RGB rgbPixel =  image.getPixel(i);
		newImage->setPixel(i, Intensity((rgbPixel.r + rgbPixel.g + rgbPixel.b) / 10));
	}

	/*IntensityImage *newImageBlur = new IntensityImageStudent(newImage->getWidth(), newImage->getHeight());
	char kernel[3][3] = {
			{ 1, 2, 1 },
			{ 2, 4, 2 },
			{ 1, 2, 1 }
	};
	float sum;

	for (int y = 1; y < newImageBlur->getHeight() - 1; y++){
		for (int x = 1; x < newImageBlur->getWidth() - 1; x++){
			sum = 0.0;
			for (int k = -1; k <= 1; k++){
				for (int j = -1; j <= 1; j++){
					sum = sum + kernel[j + 1][k + 1] * newImageBlur->getPixel(x - k, y - j);
				}
			}
			newImageBlur->setPixel(x, y, int(sum / 16));
		}
	}*/
	return newImage;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	IntensityImage *newImageBlur = new IntensityImageStudent(image.getWidth(), image.getHeight());
	char kernel[3][3] = {
			{ 1, 2, 1 },
			{ 2, 4, 2 },
			{ 1, 2, 1 }
	};
	float sum;

	for (int y = 1; y < image.getHeight() - 1; y++){
		for (int x = 1; x < image.getWidth() - 1; x++){
			sum = 0.0;
			for (int k = -1; k <= 1; k++){
				for (int j = -1; j <= 1; j++){
					sum = sum + kernel[j + 1][k + 1] * image.getPixel(x - k, y - j);
				}
			}
			newImageBlur->setPixel(x, y, sum / 16);
		}
	}

	/*IntensityImage *newImageLap = new IntensityImageStudent(image.getWidth(), image.getHeight());
	char kernelLap[3][3] = {
			{ -1, -1, -1 },
			{ -1, -8, -1 },
			{ -1, -1, -1 }
	};
	sum = 0.0;

	for (int y = 1; y < newImageBlur->getHeight() - 1; y++){
		for (int x = 1; x < newImageBlur->getWidth() - 1; x++){
			sum = 0.0;
			for (int k = -1; k <= 1; k++){
				for (int j = -1; j <= 1; j++){
					sum = sum + kernelLap[j + 1][k + 1] * newImageBlur->getPixel(x - k, y - j);
				}
			}
			newImageLap->setPixel(x, y, sum);
		}
	}*/

	IntensityImage *newImageSobel = new IntensityImageStudent(newImageBlur->getWidth(), newImageBlur->getHeight());
	char kernelX[3][3] = {
							{ -1, 0, 1 }, 
							{ -2, 0, 2 }, 
							{ -1, 0, 1 }
						};
	char kernelY[3][3] = {
							{ -1, -2, -1 },
							{ 0, 0, 0 },
							{ 1, 2, 1 }
						};

	float sumX;
	float sumY;

	for (int y = 1; y < newImageBlur->getHeight() - 1; y++){
		for (int x = 1; x < newImageBlur->getWidth() - 1; x++){
			sumX = 0.0;
			sumY = 0.0;
			for (int k = -1; k <= 1; k++){
				for (int j = -1; j <= 1; j++){
					sumX = sumX + kernelX[j + 1][k + 1] * newImageBlur->getPixel(x - k, y - j);
					sumY = sumY + kernelY[j + 1][k + 1] * newImageBlur->getPixel(x - k, y - j);

				}
			}
			float sum = abs(sumX) + abs(sumY);
			if (sum > 255){
				sum = 255;
			}
			else if (sum < 0){
				sum = 0;
			}
			newImageSobel->setPixel(x, y, int(sum));
		}
	}
	return newImageSobel;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage *intensityImage = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int intensityValue = 0;
	
	for (int y = 1; y < image.getHeight() - 1; y++){
		for (int x = 1; x < image.getWidth() - 1; x++){
			intensityValue = image.getPixel(x, y);
			if (intensityValue > 120) {
				intensityValue = 0;
			} else {
				intensityValue = 255;
			}
			intensityImage->setPixel(x, y, intensityValue);
		}
	}

	return intensityImage;
}