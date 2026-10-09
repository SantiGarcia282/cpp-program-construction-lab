#include <opencv2/opencv.hpp>
#include <iostream>
#include "CameraInput.hpp"
#include <opencv2/objdetect/aruco_detector.hpp>
#include "marker_detection.h"

int main() {
    CameraInput camera(0);
    MarkerDetection detection; // Iniciar tu componente
    cv::Mat frame;

    std::cout << "Iniciando cámara. Pulsa 'q' en la ventana de video para salir." << std::endl;

    while (true) {
        // Pedirle el fotograma a tu componente
        if (!camera.getFrame(frame)) {
            std::cerr << "Error: Fotograma en blanco." << std::endl;
            break;
        }

        std::vector<MarkerDetection::Marker> markers = detection.detect(frame);

        for(const MarkerDetection::Marker &marker : markers)
        {
            std::cout<<"Marker found: "<<marker.id<<"\n";
        }
        // Mostrar la ventana (Tu First Evidence)
        cv::imshow("Goalkeeper Minigame - Camera", frame);

        // Esperar 30 milisegundos y salir si se pulsa la tecla 'q'
        if (cv::waitKey(30) == 'q') {
        
        cv::destroyAllWindows();
            return 0;
        }
    }
}