#include <opencv2/aruco.hpp>
#include "marker_detection.h"
#include "marker_recognizer.h"

int main()
{
    // Open the supplied video file.
   // cv::VideoCapture video("resources/camera_test.mp4");


    cv::VideoCapture video(0);
    //std::string image_path = samples::findFile("aruco_id_25.png");
    //cv::Mat image = cv::imread(image_path);
    
    if (!video.isOpened()) {
        std::cerr << "Could not open the video.\n";
        return 1;
    }

    /*if (image.empty())
    {
        std::cout << "Could not load image!" << std::endl;
        return -1;
    }*/

    MarkerDetection detection;
    MarkerRecognizer recognizer;  

    cv::Mat frame;
        // Read and display one frame at a time
    while (video.read(frame)) {
         //cv::imshow("detector", outputImage);
        //std::vector<std::vector<cv::Point2f>> markers = detection.detect(frame);
       // std::vector<cv::Mat> detect(cv::Mat& frame);
        auto markers = detection.detect(frame);

        const auto& warpedMarkers = detection.getWarpedMarkers();
            //cv::imshow(image);
        for(const std::vector<cv::Point2f> &marker : markers)
        {
        //std::cout<<"marker candidate found";
         //for(const cv::Point2f& corner : marker)
            //{
             //std::cout << "(" << corner.x << "," << corner.y << ")";
          //  }
        cv::imshow("OpenCV video test", frame);        
        // Wait briefly Escape closes the program.
        if (cv::waitKey(20) == 27) {
            break;
            return 0;
            }
        }

        for (const auto& warped : warpedMarkers)
        {
            int id = recognizer.recognize(warped);
            if (id != -1)
                std::cout << "Marker ID: " << id << std::endl;
        }
    }
}