#pragma once

#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>


class MarkerRecognizer
{
public:
    MarkerRecognizer();

    int recognize(const cv::Mat& warped);
    
    cv::Mat extractBits(const cv::Mat& warped);
    cv::Mat getTemplate(int id);

private:
    cv::aruco::Dictionary dictionary;
};