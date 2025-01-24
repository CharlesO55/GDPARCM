#pragma once

#include "opencv2/core.hpp"

class RTImage {
public:
	RTImage(const int imageWidth, const int imageHeight);
	void setPixel(int x, int y, float r, float g, float b, int samplePerPixel);

	void saveImage(cv::String& fileName) const;


private:
	std::unique_ptr<cv::Mat> space_RGB;
	
	int imageWidth, imageHeight;
};