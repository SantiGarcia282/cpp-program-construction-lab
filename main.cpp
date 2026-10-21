#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include "marker_detection.h"
#include "CameraInput.hpp"

int main() {
    // 1. Initialize your camera component
    CameraInput camera(0);
    cv::Mat frame;

    // 2. Initialize detector with our new tolerance parameter
    MarkerDetection detection(5); 

    std::cout << "Starting camera. Press 'q' or 'Esc' in the video window to exit." << std::endl;

    while (true) {
        // 3. Request the frame
        if (!camera.getFrame(frame)) {
            std::cerr << "Error: Empty frame.\n";
            break;
        }

        // Simulate camera signal loss for 5 frames every 50 frames
        // This proves the tracking memory works during occlusion
        static int frameCount = 0;
        frameCount++;
        if (frameCount % 50 >= 45) {
            frame = cv::Mat::zeros(frame.size(), frame.type());
            cv::putText(frame, "SIMULATED CAMERA LOSS", cv::Point(20, 50), 
                        cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
        }

        // 4. Pass the frame to detection logic
        std::vector<MarkerDetection::Marker> markers = detection.detect(frame);

        for(const MarkerDetection::Marker &marker : markers) {
            std::cout << "Marker found: " << marker.id << "\n";
        }

        // 5. Display the final window
        cv::imshow("Goalkeeper Minigame", frame);        

        // 6. Exit condition
        int key = cv::waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }
    
    cv::destroyAllWindows();
    return 0;
}