#include "StudentHistogram.h"


StudentHistogram::StudentHistogram(int height, int width)
{
	std::vector<int> histogramTable(height);
}

void StudentHistogram::setHistogram(int value) {
	histogramTable[value];
}

std::vector<int> StudentHistogram::getHistogram() {
	return histogramTable;
}