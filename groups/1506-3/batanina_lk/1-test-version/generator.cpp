#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>
#include "linear_correction.h"

using namespace std;
using namespace cv;

bool writeMatBinary(std::ofstream& ofs, const cv::Mat& out_mat);

int main(int argc, char** argv){
	const string test_image_dir = argv[1];
	const string save_path      = argv[2];
	const int count_image  = atoi(argv[3]);

	Mat input_image;
	Mat gray_image;
	Mat output_image;

	ofstream input_file;
	ofstream output_file;

	for(int i = 0; i < count_image; ++i){
		input_image = imread(test_image_dir + to_string(i) + ".jpg");
		cvtColor(input_image, gray_image, CV_BGR2GRAY);

		input_file.open(save_path + to_string(i), ios::out | ios::binary);
		writeMatBinary(input_file, input_image);
		input_file.close();

		resize(gray_image, output_image, gray_image.size());
		linearCorection(gray_image, output_image);

		output_file.open(save_path + to_string(i) + ".ans", ios::out | ios::binary);
		writeMatBinary(output_file, output_image);
		output_file.close();
	}
	return 0;
}
bool writeMatBinary(std::ofstream& ofs, const cv::Mat& out_mat){
		if(!ofs.is_open()){
				return false;
		}
		if(out_mat.empty()){
				int s = 0;
				ofs.write((const char*)(&s), sizeof(int));
				return true;
		}
		int type = out_mat.type();
		ofs.write((const char*)(&out_mat.rows), sizeof(int));
		ofs.write((const char*)(&out_mat.cols), sizeof(int));
		ofs.write((const char*)(&type), sizeof(int));
		ofs.write((const char*)(out_mat.data), out_mat.elemSize() * out_mat.total());

		return true;
}
