#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class MarkerDetection {
public:
    std::vector<std::vector<cv::Point2f>> detect(
        cv::Mat& frame
    );
};
