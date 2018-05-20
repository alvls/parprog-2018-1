// ComponentFinderTBB.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <vector>;
#include <set>
#include <map>
#include <tbb\tbb.h>


using namespace tbb;
using namespace std;

struct Cell {
	bool bit = false;//bit map
	int tag = -1;//mark num
};

class Field {
public:
	Cell * *field_;

	Field(int Width, int Height, int *arr) {
		Width_ = Width;
		Height_ = Height;
		field_ = new Cell*[Height_];
		for (int i = 0; i < Height_; i++) {
			field_[i] = new Cell[Width_];
			for (int k = 0; k < Width_; k++) {
				if (arr[(i*Width_) + k]) {
					field_[i][k].bit = true;
					field_[i][k].tag = 0;
				}
			}
		}
	}

	~Field() {
		for (int i = 0; i < Height_; i++) {
			delete[] field_[i];
		}
		delete[] field_;
	}

	std::string PrintField() {
		std::string temp;
		temp += " |";
		for (int i = 0; i < Width_; i++)
			temp += std::to_string(i) + " ";
		temp += "|\n-+";
		for (int i = 0; i < 2 * Width_; i++)
			temp += "-";
		temp += "+\n";
		for (int i = 0; i < Height_; i++) {
			temp += std::to_string(i) + "|";
			for (int k = 0; k < Width_; k++) {
				if ((field_[i][k].tag) == -1)
					temp += '*';
				else
					temp += std::to_string(field_[i][k].tag);
				temp += " ";
			}
			temp += "|\n";
		}
		temp += "-+";
		for (int i = 0; i < 2 * Height_; i++)
			temp += "-";
		temp += "+\n";
		return temp;
	}

	bool MarkCell(int x, int y, int mark_num) {
		if (x < 0 || y < 0 || x >= Height_ || y >= Width_)
			return false;
		field_[x][y].tag = mark_num;
		return true;
	}

private:
	int Height_;
	int Width_;
};

//accept width, heigth, bool array. => array with count binary obj.
Cell** tbb_alg(int w, int h, int *arr)
{
	vector<int> st;
	//vector<set<int>> objects;
	tbb::concurrent_vector<set<int>> objects;
	int marker = 0;
	Field *f = new Field(w, h, arr);
	//cout << f->PrintField() << endl;
	cout << st.size() << endl;
	int nthreads;
	map<set<int>, int> temp;
	int obj_number = 1;
	cout << "-======================-" << endl;
	task_scheduler_init init;
	nthreads = 4;
	st.resize(nthreads);
	init.terminate();
	init.initialize(nthreads);
	cout << st.size() << endl;
	//tbb::blocked_range2d<int> a(0, h,100, 0, w,100);
	tbb::parallel_for(tbb::blocked_range2d<int>(0, h, h/nthreads, 0, w/nthreads, 100), [&](tbb::blocked_range2d<int> r) {
		int i, k;
		for (i = r.cols().begin(); i != r.cols().end(); ++i) {
			//cout << i << endl; 0, w, 0, w .rows()
			for (k = r.rows().begin(); k != r.rows().end(); ++k) {

				if (f->field_[i][k].bit) {
					int i1 = -1, k1 = -1, Wlim = 2, Hlim = 2, temp = -1, temp_marker = 0;
					if (i == 0)
						i1 = 0;
					if (i == h - 1)
						Hlim = 1;
					if (k == 0)
						k1 = temp = 0;
					if (k == w - 1)
						Wlim = 1;
					for (; i1 < Hlim; i1++) {
						for (; k1 < Wlim; k1++) {
							if (f->field_[i + i1][k + k1].bit && f->field_[i + i1][k + k1].tag != 0) {
								if (f->field_[i + i1][k + k1].tag != temp_marker &&
									temp_marker != 0) {
									tbb::concurrent_vector<set<int>> ::iterator temp_iter;
									bool flag = true;
									for (auto it = objects.begin(); it != objects.end(); ++it)
									{
										if ((*it).find(f->field_[i + i1][k + k1].tag) != (*it).end() ||
											(*it).find(temp_marker) != (*it).end() ||
											(*it).find(f->field_[i][k].tag) != (*it).end()) {
											if (flag) {
												temp_iter = it;
												(*temp_iter).emplace(f->field_[i + i1][k + k1].tag);
												(*temp_iter).emplace(temp_marker);
												(*temp_iter).emplace(f->field_[i][k].tag);
												flag = false;
											}
											else {
												(*temp_iter).emplace(f->field_[i + i1][k + k1].tag);
												(*temp_iter).emplace(temp_marker);
												(*temp_iter).emplace(f->field_[i][k].tag);
												(*temp_iter).insert(it->begin(), it->end());
											}
										}
									}
								}
								temp_marker = f->field_[i + i1][k + k1].tag;
								f->MarkCell(i, k, f->field_[i + i1][k + k1].tag);
								//cout << f->PrintField() << endl;
							}
						}
						k1 = temp;
					}
					if (f->field_[i][k].tag == 0 && temp_marker == 0) {
						f->MarkCell(i, k, ++marker);
						set<int> temp;
						temp.emplace(f->field_[i][k].tag);
						objects.push_back(temp);
						//cout << f->PrintField() << endl;

					}
				}
			}
		}
	});

	obj_number = 0;
	tbb::mutex  mutex; 

	tbb::parallel_for(tbb::blocked_range<int>(0, h), [&](tbb::blocked_range<int> r) {
	for (int i = r.begin(); i < r.end(); i++) {
	//for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			if ((f->field_[i][k]).bit) {
				for (auto it = objects.begin(); it != objects.end(); ++it)
				{	
					if ((*it).find((f->field_[i][k]).tag) != (*it).end()) {
						mutex.lock(); 
						{
							//tbb::concurrent_hash_map<set<int>, int> a;
							map<set<int>, int>::iterator pos = temp.find(*it);
							if (pos == temp.end()) {
								obj_number++;
								f->field_[i][k].tag = obj_number;
								temp.insert(pair<set<int>, int>((*it), obj_number));
							}
							else {
								f->field_[i][k].tag = (*pos).second;
							}
						}
						mutex.unlock();
						break;
					}
				}
			}
		}
	}
});
	cout << f->PrintField() << endl;

	//getchar();
	return f->field_;
}



