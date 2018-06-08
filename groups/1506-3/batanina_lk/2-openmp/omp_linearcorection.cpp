#include <omp.h>
#include "omp_linearcorection.h"

using namespace std;
using namespace cv;

void ompLinearCorection(const Mat& input, Mat& output, int num_threads){
    omp_set_num_threads(num_threads);
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
    #pragma omp parallel for schedule(guided) \
            shared(rows, cols, input, output)
    for(int i = 0; i < rows; i++){
        for(int j = 0 ; j < cols; j++){
            output.at<uchar>(i, j) = saturate_cast<uchar>(
                    round(a * input.at<uchar>(i, j) + b));
        }
    }
}
