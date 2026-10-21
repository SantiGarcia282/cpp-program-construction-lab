#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include "marker_detection.h"

int main()
{
    cv::VideoCapture video(0);
    
    if (!video.isOpened()) {
        std::cerr << "Could not open the video.\n";
        return 1;
    }

    MarkerDetection detection;
    cv::Mat frame;

    while (video.read(frame)) {
        std::vector<MarkerDetection::Marker> markers = detection.detect(frame);

        for(const MarkerDetection::Marker &marker : markers)
        {
            std::cout << "Marker " << marker.id 
                      << " found at X: " << marker.centerX 
                      << ", Y: " << marker.centerY << "\n";
            
            // Visualize the center point
            cv::Point centerPoint(static_cast<int>(marker.centerX), static_cast<int>(marker.centerY));
            cv::circle(frame, centerPoint, 5, cv::Scalar(0, 0, 255), -1); // Red dot
        }

        // Optional: Draw the bounding boxes using OpenCV's built-in function
        // cv::aruco::drawDetectedMarkers(frame, corners, ids); 

        cv::imshow("OpenCV Marker Tracker", frame);        
        
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
    
    return 0;
}