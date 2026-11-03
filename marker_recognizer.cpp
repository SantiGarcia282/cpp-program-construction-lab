#include "marker_recognizer.h"
#include <cfloat>

MarkerRecognizer::MarkerRecognizer()
{
    dictionary = cv::aruco::getPredefinedDictionary(
        cv::aruco::DICT_6X6_50
    );
}

int MarkerRecognizer::recognize(const cv::Mat& warped)
{
    if (warped.empty())
        return -1;

    cv::Mat bits = extractBits(warped);

    int bestId = -1;
    double bestScore = DBL_MAX;

    for (int id = 0; id < dictionary.bytesList.rows; id++)
    {
        cv::Mat templ = getTemplate(id);
        cv::Mat result;

        cv::matchTemplate(
            bits,
            templ,
            result,
            cv::TM_SQDIFF_NORMED
        );

        double score = result.at<float>(0, 0);

        if (score < bestScore)
        {
            bestScore = score;
            bestId = id;
        }
    }

    return bestScore < 0.1 ? bestId : -1;
}

cv::Mat MarkerRecognizer::extractBits(const cv::Mat& warped)
{
    cv::Mat binary;

    cv::threshold(
        warped,
        binary,
        0,
        255,
        cv::THRESH_BINARY | cv::THRESH_OTSU
    );

    cv::Mat bits(6, 6, CV_8UC1);

    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            int x = (col + 1) * 25 + 12;
            int y = (row + 1) * 25 + 12;

            bits.at<uchar>(row, col) =
                binary.at<uchar>(y, x) == 255 ? 255 : 0;
        }
    }

    return bits;
}

cv::Mat MarkerRecognizer::getTemplate(int id)
{
    cv::Mat templ(6, 6, CV_8UC1);

    cv::Mat bytes = dictionary.bytesList.row(id);

    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 6; col++)
        {
            int bit = row * 6 + col;
            int byteIndex = bit / 8;
            int bitIndex = 7 - (bit % 8);

            uchar value = bytes.at<uchar>(0, byteIndex);

            templ.at<uchar>(row, col) =
                ((value >> bitIndex) & 1) ? 255 : 0;
        }
    }

    return templ;
}