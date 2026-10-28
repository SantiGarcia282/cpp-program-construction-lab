#include "marker_detection.h"

//outer vector list of candidates, inner the four corners of a marker
std::vector<std::vector<cv::Point2f>>
MarkerDetection::detect(cv::Mat& frame) //input frame refrence
{
    std::vector<std::vector<cv::Point2f>> markers;

    if (frame.empty())
        return markers;

    cv::Mat gray, edges; // storing grayscale image and edges

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); //opencv uses bluegreenred instead of redgreenblue

    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 1.5); // greyscale frame blur to reduce noise 

    //cv::Canny(gray, edges, 50, 150); was not included in PBL guideline, how to replace its effects?

    std::vector<std::vector<cv::Point>> contours; //list of contours found in frame

    cv::findContours( // find contours in edges, store it in contours
        edges, contours,
        cv::RETR_LIST, // retrieve all contours
        cv::CHAIN_APPROX_SIMPLE // compress contours that are straight by reducing the amount of points
    );

    for (const auto& contour : contours) { // go through ever contour
        std::vector<cv::Point> polygon; // list to hold simplified contours

        cv::approxPolyDP(
            contour, polygon,
            0.02 * cv::arcLength(contour, true),
            true
        );

        if (polygon.size() != 4 ||
            !cv::isContourConvex(polygon))
            continue;

        if (std::abs(cv::contourArea(polygon)) < 500)
            continue;

        std::vector<cv::Point2f> corners(
            polygon.begin(), polygon.end()
        );

        markers.push_back(corners);

        for (int i = 0; i < 4; ++i) {
            cv::line(
                frame,
                polygon[i],
                polygon[(i + 1) % 4],
                cv::Scalar(0, 255, 0),
                2
            );
        }
    }

    return markers;
}