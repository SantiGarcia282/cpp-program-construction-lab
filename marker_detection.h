#ifndef MARKER_DETECTION_H
#define MARKER_DETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <vector>
#include <map>

class MarkerDetection
{
public:
    struct Marker
    {
        int id;
        std::vector<cv::Point2f> corners;
    };

    MarkerDetection(int maxLossTolerance = 5);

    std::vector<Marker> detect(const cv::Mat& frame);

private:
    cv::aruco::ArucoDetector detector;
    
    struct TrackedMarker {
        Marker data;
        int framesLost;
    };
    
    std::map<int, TrackedMarker> markerHistory;
    int tolerance;
};

#endif