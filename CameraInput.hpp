#ifndef CAMERA_INPUT_HPP
#define CAMERA_INPUT_HPP

#include <opencv2/opencv.hpp>

class CameraInput {
private:
    cv::VideoCapture cap; // El objeto de OpenCV que controla la cámara

public:
    // Constructor: enciende la cámara
    CameraInput(int deviceID = 0); 
    
    // Destructor: apaga la cámara al cerrar
    ~CameraInput(); 
    
    // Método principal para sacar un fotograma
    bool getFrame(cv::Mat& frame); 
};

#endif