#include "CameraInput.hpp"
#include <iostream>

CameraInput::CameraInput(int deviceID) {
    // Try to open the specified camera device (default is 0)
    cap.open(deviceID);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera." << std::endl;
    }
}

CameraInput::~CameraInput() {
    // Release the camera properly upon exit
    cap.release();
}

bool CameraInput::getFrame(cv::Mat& frame) {
    if (!cap.isOpened()) return false;
    
    cap >> frame; // Extract the frame from the camera
    return !frame.empty(); // Return true if the frame is valid
}