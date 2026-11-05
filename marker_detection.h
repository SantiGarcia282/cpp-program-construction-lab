#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class MarkerDetection {
public:
    std::vector<std::vector<cv::Point2f>> detect(
        cv::Mat& frame
    );

const std::vector<cv::Mat>& getWarpedMarkers() const;

private:
    std::vector<cv::Point2f> orderCorners(
        const std::vector<cv::Point2f>& corners
    );

    std::vector<cv::Mat> warpedMarkers;
    //int frameCount = 0;
};

