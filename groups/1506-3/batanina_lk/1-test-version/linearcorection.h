#ifndef BATANINA_LK_TEST_VERSION_LINEARCORECTION_H
#define BATANINA_LK_TEST_VERSION_LINEARCORECTION_H

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>

void getMinMaxFromHistogram(const cv::Mat& input, int& min, int& max);
void linearCorection(const cv::Mat& input, cv::Mat& output);

#endif //BATANINA_LK_TEST_VERSION_LINEARCORECTION_H
