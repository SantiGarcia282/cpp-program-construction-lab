#include <opencv2/opencv.hpp>
#include <iostream>
#include "CameraInput.hpp"

int main() {
    CameraInput camera(0); // Iniciar tu componente
    cv::Mat frame;

    std::cout << "Iniciando cámara. Pulsa 'q' en la ventana de video para salir." << std::endl;

    while (true) {
        // Pedirle el fotograma a tu componente
        if (!camera.getFrame(frame)) {
            std::cerr << "Error: Fotograma en blanco." << std::endl;
            break;
        }

        // Mostrar la ventana (Tu First Evidence)
        cv::imshow("Goalkeeper Minigame - Camera", frame);

        // Esperar 30 milisegundos y salir si se pulsa la tecla 'q'
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }
    
    cv::destroyAllWindows();
    return 0;
}