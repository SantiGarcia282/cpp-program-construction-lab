#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class MarkerRecognizer
{
public:
    MarkerRecognizer(const std::string& templatePath);

    bool recognize(const cv::Mat& warped);

private:
    cv::Mat markerTemplate;
    int frameCount = 0;
};