#ifndef MARKER_DETECTION_H
#define MARKER_DETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <vector>

class MarkerDetection {
public:
    MarkerDetection();

    // detects four corner markers
    std::vector<std::vector<cv::Point2f>>
    detect(cv::Mat& frame);

private:
    double minArea;
    double maxArea;
    
    bool isValidMarker(
        const std::vector<cv::Point>& contour,
        std::vector<cv::Point>& approx
    );
};

#endif