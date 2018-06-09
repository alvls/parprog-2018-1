#include <iostream>
#include <vector>
#include <algorithm>
#include "tbb/tbb.h"
#include "linearcorection.h"

using namespace std;
using namespace cv;

void tbbLinearCorection(const cv::Mat& input, cv::Mat& output, int num_threads = 1){
    int min = 0;
    int max = 0;
    getMinMaxFromHistogram(input, min, max);
    if (max == min) {
        input.copyTo(output);
        return;
    }
    double a = 255.0f / (max - min);
    double b = (-1) * a * min;

    int rows = input.rows;
    int cols = input.cols;
	
	tbb::task_scheduler_init init(num_threads);

    tbb::parallel_for(
       tbb::blocked_range2d<int>(0, rows, 0, cols),
    	 [&] (tbb::blocked_range2d<int> &r){
       int i, j;
       for(i = r.rows().begin(); i != r.rows().end(); ++i){
           for(j = r.cols().begin(); j != r.cols().end(); ++j){
               output.at<uchar>(i, j) = saturate_cast<uchar>(
                   round(a * input.at<uchar>(i, j) + b));
           }
       }
    });
}

