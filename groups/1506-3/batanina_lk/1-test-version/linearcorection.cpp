#include <vector>
#include <algorithm>
#include "linear_correction.h"

using namespace std;
using namespace cv;

void getMinMaxFromHistogram(const Mat& input, int& min, int& max){
    vector<int> histogram(256);
    fill(histogram.begin(), histogram.end(), 0);
    int rows = input.rows;
    int cols = input.cols;

    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            histogram[input.at<uchar>(i,j)]++;
        }
    }

    min = 0;
    while (!histogram[min]){
        min++;
    }

    max = 255;
    while (!histogram[max]){
        max--;
    }
}


void linearCorection(const Mat& input, Mat& output){
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
    for(int i = 0; i < rows; i++){
        for(int j = 0 ; j < cols; j++){
            output.at<uchar>(i, j) = saturate_cast<uchar>(
                    round(a * input.at<uchar>(i, j) + b));
        }
    }

}


