#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

cv::Mat src, src_gray;
int thresh = 50;
std::string source_window("Source image");
std::string corners_window("Harris Corner detection");

double calculateArea(const std::vector<std::pair<int, int>>& corners) {
    double area = 0.0;
    int n = corners.size();

    int j = n - 1;
    for (int i = 0; i < n; i++) {
        area += (corners[j].first + corners[i].first) * (corners[j].second - corners[i].second);
        j = i;
    }

    area = std::abs(area) / 2.0;
    return area;
}

int main()
{
    //AreaSpace();

    src = cv::imread("../test.jpg");
    cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
    cv::namedWindow(source_window.c_str());
    cv::imshow(source_window.c_str(), src);
    
    int blockSize = 5;
    int apertureSize = 3;
    double k = 0.06;

    cv::Mat dst = cv::Mat::zeros(src.size(), CV_32FC1);
    cv::cornerHarris(src_gray, dst, blockSize, apertureSize, k);
    cv::Mat dst_norm, dst_norm_scaled;
    cv::normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
    cv::convertScaleAbs(dst_norm, dst_norm_scaled);

    //
    std::vector<std::pair<int, int>> corners;
    //

    for (int i = 0; i < dst_norm.rows; i++) {
        for (int j = 0; j < dst_norm.cols; j++) {
            if ((int)dst_norm.at<float>(i, j) > thresh) {
                cv::circle(dst_norm_scaled, cv::Point(j, i), 5, cv::Scalar(255), 2, 8, 0);

                corners.push_back(std::make_pair(j, i));
                std::cout << "x " << j << " y " << i;
            }
        }
    }
    cv::namedWindow(corners_window.c_str());
    cv::imshow(corners_window.c_str(), dst_norm_scaled);

    //std::cout << dst_norm_scaled;
    // Calculate the size of the area based on the detected corners
    double area_size = 0.0;
    for (size_t i = 0; i < corners.size(); i++) {
        //cv::Point corner = corners[i];
        
    }
    area_size = calculateArea(corners);
    std::cout << "Estimated area size: " << area_size << std::endl;

    cv::waitKey();
    return 0;
}