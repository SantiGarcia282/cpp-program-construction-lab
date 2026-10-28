#include "marker_detection.h"

std::vector<std::vector<cv::Point2f>>
MarkerDetection::detect(cv::Mat& frame)
{
    std::vector<std::vector<cv::Point2f>> markers;

    if (frame.empty())
        return markers;

    cv::Mat gray, edges;

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 1.5);

    //cv::Canny(gray, edges, 50, 150);

    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(
        edges, contours,
        cv::RETR_LIST,
        cv::CHAIN_APPROX_SIMPLE
    );

    for (const auto& contour : contours) {
        std::vector<cv::Point> polygon;

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