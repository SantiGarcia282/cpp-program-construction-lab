#include <opencv2/opencv.hpp>
#include <iostream>

#include "CameraInput.hpp"
#include "marker_detection.h"
#include "marker_recognizer.h"
#include "InteractionMapping.h"

int main()
{
    CameraInput camera(0);
    cv::Mat frame;

    MarkerRecognizer recognizer("aruco_id_25.png");
    MarkerDetection detection(recognizer);

    //grab frame
    if (!camera.getFrame(frame)) {
        std::cerr << "Failed to grab initial frame." << std::endl;
        return 1;
    }
    int frameWidth = frame.cols;
    int frameHeight = frame.rows;

    InteractionMapper mapper(frameWidth, frameHeight);
    mapper.spawnBall(); //initiate ball

    std::cout << "Game loop started. Press ESC in the camera window to quit.\n";

    while (camera.getFrame(frame))
    {
        auto candidates = detection.detect(frame);

        //default marker position
        int markerX = frameWidth / 2;
        int markerY = frameHeight / 2;

        bool markerFound = false;
        if (!candidates.empty())
        {
            //use the first recognized marker
            cv::Point2f center(0, 0);

            for (const auto& pt : candidates[0]) {
                center += pt;
            }

            center *= 0.25f;

            markerX = static_cast<int>(center.x);
            markerY = static_cast<int>(center.y);

            markerFound = true;

            cv::circle(
                frame,
                 center,
                10,
                cv::Scalar(255, 0, 255),
                3
            );
        }

        GameState state = mapper.update(markerX, markerY);

        //draw glove
        int glovePixelX = static_cast<int>(state.gloveX * frameWidth);
        int glovePixelY = static_cast<int>(state.gloveY * frameHeight);
        int gloveRadius = static_cast<int>(state.gloveWidth * frameWidth * 0.5f);
        cv::circle(frame, cv::Point(glovePixelX, glovePixelY), gloveRadius, cv::Scalar(0, 255, 255), 2);

        //draw ball
        if (state.ballActive) {
            int ballPixelX = static_cast<int>(state.ball.x * frameWidth);
            int ballPixelY = static_cast<int>(state.ball.y * frameHeight);
            int ballRadius = static_cast<int>(0.03f * frameWidth); // Approx size based on normalization
            cv::circle(frame, cv::Point(ballPixelX, ballPixelY), ballRadius, cv::Scalar(0, 165, 255), -1);
        } else {
            //if no ball active, spawn a new one after short delay
            static int frameDelay = 0;
            if (++frameDelay > 30) { //roughly 1 second at 30fps
                mapper.spawnBall();
                frameDelay = 0;
            }
        }

        // Draw Score
        std::string scoreText = "Score: " + std::to_string(state.score);
        cv::putText(frame, scoreText, cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);

        cv::imshow("Integrated Game Test", frame);

        if (cv::waitKey(20) == 27) {
            break;
        }
    }

    return 0;
}