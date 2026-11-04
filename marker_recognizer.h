#pragma once

#include <opencv2/opencv.hpp>

class MarkerRecognizer
{
public:
    MarkerRecognizer(const std::string& templatePath);

    bool recognize(const cv::Mat& warped);

private:
    cv::Mat markerTemplate;
};