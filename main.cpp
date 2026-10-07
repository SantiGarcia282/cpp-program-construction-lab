#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include "marker_detection.h"

int main()
{
    // Open the supplied video file.
   // cv::VideoCapture video("resources/camera_test.mp4");
    cv::VideoCapture video(0);
    
    if (!video.isOpened()) {
        std::cerr << "Could not open the video.\n";
        return 1;
    }

    MarkerDetection detection;
    cv::Mat frame;

    // Read and display one frame at a time
    while (video.read(frame)) {

        //cv::imshow("detector", outputImage);
        std::vector<MarkerDetection::Marker> markers = detection.detect(frame);

        for(const MarkerDetection::Marker &marker : markers)
        {
            std::cout<<"marker found: "<<marker.id<<"\n";
        }
        cv::imshow("OpenCV video test", frame);        
        // Wait briefly Escape closes the program.
        if (cv::waitKey(20) == 27) {
            break;
        }
    }
    
    return 0;
}