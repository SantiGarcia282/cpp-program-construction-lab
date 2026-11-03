#include "marker_recognizer.h"

MarkerRecognizer::MarkerRecognizer()
{
    dictionary = *cv::aruco::getPredefinedDictionary(
        cv::aruco::DICT_6X6_50
    );
}

int MarkerRecognizer::recognize(const MarkerCandidate& candidate)
{
    if (candidate.warped.empty())
        return -1;
}