#include "marker_detection.h"

MarkerDetection::MarkerDetection(int maxLossTolerance) : tolerance(maxLossTolerance)
{
    cv::aruco::Dictionary dictionary =
        cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);

    detector = cv::aruco::ArucoDetector(dictionary);
}

std::vector<MarkerDetection::Marker> MarkerDetection::detect(const cv::Mat& frame)
{
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;

    detector.detectMarkers(frame, corners, ids);

    std::vector<Marker> outputMarkers;
    std::vector<int> detectedIdsThisFrame;

    for (size_t i = 0; i < ids.size(); i++)
    {
        Marker marker;
        marker.id = ids[i];
        marker.corners = corners[i];

        outputMarkers.push_back(marker);
        detectedIdsThisFrame.push_back(marker.id);

        markerHistory[marker.id] = {marker, 0};
    }

    for (auto it = markerHistory.begin(); it != markerHistory.end(); )
    {
        int id = it->first;
        
        if (std::find(detectedIdsThisFrame.begin(), detectedIdsThisFrame.end(), id) == detectedIdsThisFrame.end())
        {
            it->second.framesLost++;
            
            if (it->second.framesLost <= tolerance) {
                outputMarkers.push_back(it->second.data);
                ++it;
            } else {
                it = markerHistory.erase(it);
            }
        } else {
            ++it;
        }
    }

    return outputMarkers;
}