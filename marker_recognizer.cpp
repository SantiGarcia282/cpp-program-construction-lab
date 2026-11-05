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

    cv::threshold(
        warped,
        binary,
        0,
        255,
        cv::THRESH_BINARY | cv::THRESH_OTSU
    );

    cv::Mat rotated = markerTemplate;
    double bestScore = -1.0;

    for (int i = 0; i < 4; i++)
    {
        cv::Mat result;

        //compare the warped marker with rotated template image
        cv::matchTemplate(
            binary,
            rotated,
            result,
            cv::TM_CCOEFF_NORMED
        );

        double score = result.at<float>(0, 0);

        bestScore = std::max(bestScore, score);

        //rotate 90 degrees clockwise for the next iteration
        cv::rotate(
            rotated,
            rotated,
            cv::ROTATE_90_CLOCKWISE
        );
    }
    
    frameCount++;
    
    if(frameCount % 30 == 0)
    {
        std::cout << "Best score: " << bestScore << std::endl;        
    }

    const double Match_Max = 0.85;

    if (bestScore < Match_Max) //reject any candidate with less than .85 score
        return false;

    return true;
}