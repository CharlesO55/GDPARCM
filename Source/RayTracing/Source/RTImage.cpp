#include "RTImage.h"

#include <algorithm>
#include <opencv2/opencv.hpp>


RTImage::RTImage(const int imageWidth, const int imageHeight) :
	imageWidth(imageWidth),
	imageHeight(imageHeight)
{
	BGR_Channel = std::make_unique<cv::Mat>(cv::Mat::zeros(imageHeight, imageWidth, CV_8UC3));
}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samplePerPixel)
{
	/* REDUCES THE GAMMA
	float scale = 1.0f / samplePerPixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);*/

	int rInt = static_cast<uchar>(256 * std::clamp(r, 0.0f, 0.999f));
	int gInt = static_cast<uchar>(256 * std::clamp(g, 0.0f, 0.999f));
	int bInt = static_cast<uchar>(256 * std::clamp(b, 0.0f, 0.999f));


	/*cv::Mat imgChannels[3] = {
		cv::Mat(this->imageHeight, this->imageWidth, CV_8UC1),
		cv::Mat(this->imageHeight, this->imageWidth, CV_8UC1),
		cv::Mat(this->imageHeight, this->imageWidth, CV_8UC1)
	};

	imgChannels[2].at<uchar>(this->imageHeight - 1 - y, x) = rInt;
	cv::merge(imgChannels, 3, *this->pixels);*/
	 
	
	BGR_Channel.get()->at<cv::Vec3b>(y, x) = cv::Vec3b(bInt, gInt, rInt);
}

void RTImage::saveImage(cv::String& fileName) const
{
	cv::imwrite(fileName, *this->BGR_Channel);
}

const std::unique_ptr<cv::Mat>* RTImage::getBGRChannel()
{
	return &BGR_Channel;
}