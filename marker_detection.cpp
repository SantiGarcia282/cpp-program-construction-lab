#include "marker_detection.h"
#include <cmath>
#include <cfloat>


//outer vector list of candidates, inner the four corners of a marker
std::vector<std::vector<cv::Point2f>>

MarkerDetection::detect(cv::Mat& frame) //input frame refrence
{
    std::vector<std::vector<cv::Point2f>> markers;

    if (frame.empty())
        return markers;

    warpedMarkers.clear();

    cv::Mat gray, binary;

    if (frame.channels() == 3) { 
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); //opencv uses bgr instead of rgb
    }
    else if (frame.channels() == 1) {
        gray = frame.clone();
    }
    else {
        return markers;
    }   

    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 1.5); // greyscale frame blur to reduce noise 

    // Convert grayscale image to binary.
    cv::threshold(
        gray,
        binary,
        0,
        255,
        cv::THRESH_BINARY_INV | cv::THRESH_OTSU
    );

    std::vector<std::vector<cv::Point>> contours; //list of contours found in frame

    cv::findContours( // find contours in edges, store it in contours
        binary, contours,
        //cv::RETR_LIST,    // retrieve all contours
        cv::RETR_EXTERNAL, 
        cv::CHAIN_APPROX_SIMPLE // compress contours that are straight by reducing the amount of points
    );

    for (const auto& contour : contours) { // go through ever contour
        if (contour.size() < 3)
            continue;

        if (std::abs(cv::contourArea(contour)) < 500)
            continue;

        std::vector<cv::Point> polygon;

        cv::approxPolyDP(
            contour, polygon,
            0.02 * cv::arcLength(contour, true),
            true
        );

        if (polygon.size() != 4 ||
            !cv::isContourConvex(polygon))
            continue;

        std::vector<cv::Point2f> corners(polygon.begin(), polygon.end());
        
        //order the four corners
        corners = orderCorners(corners);

        cv::Point2f src[4];

        for (int i = 0; i < 4; i++)
        {
            src[i] = corners[i];
        }

        cv::Point2f dst[4] = {
            {0, 0},
            {200, 0},
            {200, 200},
            {0, 200}
        };

        cv::Mat matrix = cv::getPerspectiveTransform(src, dst);

        cv::Mat warped;

        cv::warpPerspective(
            gray,
            warped,
            matrix,
            cv::Size(200, 200)
        );

        warpedMarkers.push_back(warped);
        
        //cv::Mat matrix = cv::getPerspectiveTransform(src, polygon);        
        //calculate center
        cv::Point2f center(0, 0);
            for (const auto& pt : corners) {
                center += pt;
                }
            center *= 0.25f;


        markers.push_back(corners);

        //draw detected quadrilateral
        for (int i = 0; i < 4; ++i) {
            cv::line(
                frame,
                polygon[i],
                polygon[(i + 1) % 4],
                cv::Scalar(0, 255, 0),
                2
            );
        }
        cv::circle( //draw circle
            frame,
            center,
            4,
            cv::Scalar(0, 0, 255),
            -1
        );
    }

    /*cv::matchTemplate(
        frame,
        image,
        result,
        TM_COEFF_NORMED
    );*/

    return markers;
}

std::vector<cv::Point2f> MarkerDetection::orderCorners(
    const std::vector<cv::Point2f>& corners)
{
    std::vector<cv::Point2f> ordered(4);

    float minSum = FLT_MAX;
    float maxSum = -FLT_MAX;
    float minDiff = FLT_MAX;
    float maxDiff = -FLT_MAX;

    for (const auto& pt : corners) {

        float sum = pt.x + pt.y;
        float diff = pt.x - pt.y;

        // Top-left
        if (sum < minSum) {
            minSum = sum;
            ordered[0] = pt;
        }

        // Bottom-right
        if (sum > maxSum) {
            maxSum = sum;
            ordered[2] = pt;
        }

        // Bottom-left
        if (diff < minDiff) {
            minDiff = diff;
            ordered[3] = pt;
        }

        // Top-right
        if (diff > maxDiff) {
            maxDiff = diff;
            ordered[1] = pt;
        }
    }

    return ordered;
}

const std::vector<cv::Mat>& MarkerDetection::getWarpedMarkers() const
{
    return warpedMarkers;
}