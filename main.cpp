#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include "marker_detection.h"
#include "CameraInput.hpp"

int main() {
    // 1. Initialize your camera component
    CameraInput camera(0);
    cv::Mat frame;

    // 2. Initialize detector
    MarkerDetection detection; 

    std::cout << "Starting camera. Press 'q' or 'Esc' in the video window to exit." << std::endl;

    while (true) {
        // 3. Request the frame
        if (!camera.getFrame(frame)) {
            std::cerr << "Error: Empty frame.\n";
            break;
        }

        // 4. Pass the frame to detection logic
        std::vector<MarkerDetection::Marker> markers = detection.detect(frame);

        for(const MarkerDetection::Marker &marker : markers) {
            std::cout << "Marker found: " << marker.id << "\n";
        }

        // 5. Display the final window
        cv::imshow("Goalkeeper Minigame", frame);        

        // 6. Exit condition (Supports both your 'q' and their 'Esc')
        int key = cv::waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }
    
    cv::destroyAllWindows();
    return 0;
}