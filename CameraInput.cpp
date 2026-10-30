#include "CameraInput.hpp"
#include <iostream>

CameraInput::CameraInput(int deviceID) {
    // Intentar abrir la cámara por defecto (0)
    cap.open(deviceID);
    if (!cap.isOpened()) {
        std::cerr << "Error: No se pudo encender la cámara." << std::endl;
    }
}

CameraInput::~CameraInput() {
    // Liberar la cámara correctamente al terminar
    cap.release();
}

bool CameraInput::getFrame(cv::Mat& frame) {
    if (!cap.isOpened()) return false;
    
    cap >> frame; // Extraer el fotograma de la cámara
    return !frame.empty(); // Devolver true si el fotograma es válido
}