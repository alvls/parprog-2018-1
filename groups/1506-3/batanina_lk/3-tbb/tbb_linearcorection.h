#ifndef BATANINA_LK_TBB_VERSION_LINEARCORECTION_H
#define BATANINA_LK_TBB_VERSION_LINEARCORECTION_H

#include "linearcorection.h"

void tbbLinearCorection(const cv::Mat& input, cv::Mat& output, int num_threads = 1);

#endif  // BATANINA_LK_TBB_VERSION_LINEARCORECTION_H
