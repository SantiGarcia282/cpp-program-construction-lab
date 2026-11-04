#include "marker_recognizer.h"
#include <iostream>
#include <stdexcept>

MarkerRecognizer::MarkerRecognizer(const std::string& templatePath)
{
    //load the reference image in grayscale
    markerTemplate = cv::imread(templatePath, cv::IMREAD_GRAYSCALE);

    if (markerTemplate.empty())
    {
        throw std::runtime_error("Could not load marker template: " + templatePath);
    }

    //resize it to match the warped marker dimensions
    cv::resize(markerTemplate, markerTemplate, cv::Size(200, 200));

    //convert it to a binary image
    cv::threshold(
        markerTemplate,
        markerTemplate,
        0,
        255,
        cv::THRESH_BINARY | cv::THRESH_OTSU
    );
}

bool MarkerRecognizer::recognize(const cv::Mat& warped)
{
    if (warped.empty() || markerTemplate.empty())
        return false;

    cv::Mat binary;

    //convert the warped marker to binary
    cv::threshold(
        warped,
        binary,
        0,
        255,
        cv::THRESH_BINARY | cv::THRESH_OTSU
    );

    cv::Mat result;

    //compare the warped marker with our PNG
    cv::matchTemplate(
        binary,
        markerTemplate,
        result,
        cv::TM_CCOEFF_NORMED
    );

    double score = result.at<float>(0, 0);

    //higher score = better match
    return score >= 0.85;
}