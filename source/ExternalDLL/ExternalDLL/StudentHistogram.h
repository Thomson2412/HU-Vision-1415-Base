#ifndef _STUDENTHISTOGRAM_H
#define _STUDENTHISTOGRAM_H
#include <vector>

class StudentHistogram
{
public:
	StudentHistogram(int height, int width);

	int setHistogram(int value);
	std::vector<int> getHistogram();

private:
	std::vector<int> histogramTable;
};
#endif
