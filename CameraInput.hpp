#ifndef CAMERA_INPUT_HPP
#define CAMERA_INPUT_HPP

#include <opencv2/opencv.hpp>

class CameraInput {
private:
    cv::VideoCapture cap; // OpenCV object that controls the camera

public:
    // Constructor: initializes the camera
    CameraInput(int deviceID = 0); 
    
    // Destructor: releases the camera upon closing
    ~CameraInput(); 
    
    // Main method to extract a frame
    bool getFrame(cv::Mat& frame); 
};

#endif