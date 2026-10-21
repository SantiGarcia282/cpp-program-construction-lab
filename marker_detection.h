#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <vector>

class MarkerDetection
{
public:
    struct Marker
    {
        int id;
        std::vector<cv::Point2f> corners;
        float centerX; // 
        float centerY; // 
    };

    MarkerDetection();
    std::vector<Marker> detect(const cv::Mat& frame);

private:
    cv::aruco::ArucoDetector detector;
};