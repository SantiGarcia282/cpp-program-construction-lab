#include <opencv2/opencv.hpp>
#include <iostream>

#include "marker_detection.h"
#include "marker_recognizer.h"

int main()
{
    cv::VideoCapture video(0);

    if (!video.isOpened())
    {
        std::cerr << "Could not open the camera.\n";
        return 1;
    }

    MarkerDetection detection;
    MarkerRecognizer recognizer("aruco_id_25.png");

    cv::Mat frame;
    int frameCount = 0;

    while (video.read(frame))
    {
        int64 start = cv::getTickCount();

        // Detect candidates
        auto markers = detection.detect(frame);

        int64 afterDetection = cv::getTickCount();

        // Recognize candidates
        const auto& warpedMarkers = detection.getWarpedMarkers();

        for (const auto& warped : warpedMarkers)
        {
            if (recognizer.recognize(warped) && frameCount % 30 == 0)
            {
                std::cout << "Our marker detected!\n";
            }
        }

        int64 afterRecognition = cv::getTickCount();

        // Calculate timings
        double detectionMs =
            (afterDetection - start) * 1000.0 / cv::getTickFrequency();

        double recognitionMs =
            (afterRecognition - afterDetection) * 1000.0 / cv::getTickFrequency();

        // Print every 30 frames
        if (++frameCount % 30 == 0)
        {
            std::cout << "Detection: " << detectionMs
                      << " ms | Recognition: " << recognitionMs
                      << " ms | Candidates: " << warpedMarkers.size()
                      << '\n';
        }

        cv::imshow("OpenCV video test", frame);

        if (cv::waitKey(1) == 27)
            break;
    }

    video.release();
    cv::destroyAllWindows();

    return 0;
}