#include "marker_detection.h"

MarkerDetection::MarkerDetection()
{
    cv::aruco::Dictionary dictionary =
        cv::aruco::getPredefinedDictionary(
            cv::aruco::DICT_6X6_50
        );

    detector = cv::aruco::ArucoDetector(dictionary);
}


std::vector<MarkerDetection::Marker>
MarkerDetection::detect(const cv::Mat& frame)
{
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;

    detector.detectMarkers(frame, corners, ids);

    std::vector<Marker> markers;

    for (size_t i = 0; i < ids.size(); i++)
    {
        Marker marker;

        marker.id = ids[i];
        marker.corners = corners[i];

        markers.push_back(marker);
    }

    return markers;
}

   /* std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);
    cv::aruco::ArucoDetector detector(dictionary, detectorParams);
    detector.detectMarkers(frame, markerCorners, markerIds, rejectedCandidates);  

    cv::Mat outputframe = frame.clone();
    cv::aruco::drawDetectedMarkers(outputframe, markerCorners, markerIds); */

