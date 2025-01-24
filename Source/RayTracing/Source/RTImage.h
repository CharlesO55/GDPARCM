#pragma once

#include "opencv2/core.hpp"

class RTImage {
public:
	RTImage(const int imageWidth, const int imageHeight);
	void setPixel(int x, int y, float r, float g, float b, int samplePerPixel);

	void saveImage(cv::String& fileName) const;

	const std::unique_ptr<cv::Mat>* getBGRChannel();

private:
	std::unique_ptr<cv::Mat> BGR_Channel;
	int imageWidth, imageHeight;
};