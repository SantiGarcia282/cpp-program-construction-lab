#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

class MarkerRecognizer
{
public:
    MarkerRecognizer();

    int recognize(const cv::Mat& warped);

private:
    cv::aruco::Dictionary dictionary;
};