#include "marker_detection.h"
#include <opencv2/objdetect/aruco_detector.hpp>
#include <cmath>

MarkerDetection::MarkerDetection()
    : minArea(500.0), maxArea(100000.0) {

    }


bool MarkerDetection::isValidMarker(
    const std::vector<cv::Point>& contour,
    std::vector<cv::Point>& approx)

    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);

{
    double perimeter = cv::arcLength(contour, true);

    cv::approxPolyDP(
        contour, approx, 0.02 * perimeter, true
    );

    // a marker has 4 corners
    if (approx.size() != 4)
        return false;

    double area = std::fabs(cv::contourArea(approx));

    if (area < minArea || area > maxArea)
        return false;

    // check if the angles are somewhat straight
    for (int i = 0; i < 4; ++i) {
        cv::Point2f p0 = approx[i];
        cv::Point2f p1 = approx[(i + 1) % 4];
        cv::Point2f p2 = approx[(i + 2) % 4];

        cv::Point2f v1 = p0 - p1;
        cv::Point2f v2 = p2 - p1;

        double denominator =
            cv::norm(v1) * cv::norm(v2);

        if (denominator < 1e-6)
            return false;

        double cosine =
            v1.dot(v2) / denominator;

        if (std::abs(cosine) > 0.35)
            return false;
    }

    return true;
}

std::vector<std::vector<cv::Point2f>>
MarkerDetection::detect(cv::Mat& frame)
{
    std::vector<std::vector<cv::Point2f>> markers;

    if (frame.empty())
        return markers;

    cv::Mat gray, blurred, edges;

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); //grey scale, it goes bluegreenred for some reason

    cv::GaussianBlur(
        gray, blurred, cv::Size(5, 5), 1.5
    );

    cv::Canny(blurred, edges, 50, 150);

    // find countours
    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(
        edges,
        contours,
        cv::RETR_LIST,
        cv::CHAIN_APPROX_SIMPLE
    );

    for (const auto& contour : contours) {
        std::vector<cv::Point> approx;

        if (!isValidMarker(contour, approx))
            continue;

        std::vector<cv::Point2f> corners;

        for (const auto& point : approx)
            corners.emplace_back(point.x, point.y);

        markers.push_back(corners);

        // Draw the markers four corners
        for (int i = 0; i < 4; ++i) {
            cv::line(
                frame,
                approx[i],
                approx[(i + 1) % 4],
                cv::Scalar(0, 255, 0),
                2
            );
        }

    }

   /* cv::aruco::Dictionary dictionary =
    cv::aruco::getPredefinedDictionary(  // use dict make a matrix of 6x6 bits? check if they match
        cv::aruco::DICT_6X6_50
    );
    */
    return markers;
}
