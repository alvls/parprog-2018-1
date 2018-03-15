#include <iostream>
#include <fstream>
#include <algorithm>
#include "linear_correction.h"
#include "checker.h"

using namespace std;
using namespace cv;

bool readMatBinary(ifstream& ifs, Mat& in_mat);
bool loadMatBinary(const string& filename, Mat& output);
bool is_equal(const Mat& m1, const Mat& m2);

int main(int argc, char* argv[]){
	const string test_image_dir = argv[1];
	const string result_path    = argv[2];
	int count_test = atoi(argv[3]);

	Mat input_image;
	Mat answer_image;
	Mat output_image;
	Mat gray_image;
	Mat diff;

	Checker checker(result_path);

	for(int i = 0; i < count_test; ++i){
		loadMatBinary(test_image_dir + to_string(i), input_image);
		loadMatBinary(test_image_dir + to_string(i) + ".ans", answer_image);

		cvtColor(input_image, gray_image, CV_BGR2GRAY);
		resize(gray_image, output_image, gray_image.size());
		linearCorection(gray_image, output_image);
		if(is_equal(answer_image, output_image))
			checker.write_message("[ TEST " + to_string(i) + "] images are equal.");
		else
			checker.write_message("[ TEST " + to_string(i) + "] images aren't equal.");
	}
}

bool readMatBinary(ifstream& ifs, Mat& in_mat){

	if(!ifs.is_open()){
		return false;
	}

	int rows, cols, type;
	ifs.read((char*)(&rows), sizeof(int));
	if(rows==0){
		return true;
	}
	ifs.read((char*)(&cols), sizeof(int));
	ifs.read((char*)(&type), sizeof(int));

	in_mat.release();
	in_mat.create(rows, cols, type);
	ifs.read((char*)(in_mat.data), in_mat.elemSize() * in_mat.total());

	return true;
}
bool loadMatBinary(const string& filename, Mat& output){
	ifstream ifs(filename, ios::binary);
	return readMatBinary(ifs, output);
}

bool is_equal(const Mat& m1, const Mat& m2){
	for(int i = 0; i < m1.rows; ++i){
		const uchar* m1_line = m1.ptr<uchar>(i);
		const uchar* m2_line = m2.ptr<uchar>(i);

		for(int j = 0; j < m1.cols; ++j){
			if(m1_line[j] != m2_line[j])
				return false;
		}
	}
	return true;
}
