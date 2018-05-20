// sol.cpp : Defines the entry point for the console application.
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
				if (arr[(i*Width_)+k]) {
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
Cell** omp_alg(int w, int h, int *arr)
{
	vector<int> st;
	vector<set<int>> objects;
	int marker = 0;
	Field *f = new Field(w, h, arr);
	cout << f->PrintField() << endl;
	cout << st.size() << endl;
	int i, k, nthreads;
	map<set<int>, int> temp;
	int obj_number = 1;
	cout << "-======================-" << endl;
	#pragma omp parallel  
	{
		
		#pragma omp single 
		{
			nthreads = omp_get_num_threads();
			st.resize(nthreads);
			cout << nthreads << endl;
			cout << st.size() << endl;
		}

		#pragma omp for private (i,k)
		for (i = 0; i < h; i++) {
			const int ithread = omp_get_thread_num();
			const int start = ithread * w / nthreads;
			st[ithread] = start;
			const int finish = (ithread + 1) * w / nthreads;
			for (k = 0; k < w; k++) {
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
									vector<set<int>> ::iterator temp_iter;
									bool flag=true;
									for (vector<set<int>> ::iterator it = objects.begin(); it != objects.end(); ++it)
									{
										if ((*it).find(f->field_[i + i1][k + k1].tag) != (*it).end() ||
											(*it).find(temp_marker) != (*it).end() ||
											(*it).find(f->field_[i][k].tag) != (*it).end()) {
											if (flag) {
												//#pragma omp critical (first) 
												//{
													temp_iter = it;
													(*temp_iter).emplace(f->field_[i + i1][k + k1].tag);
													(*temp_iter).emplace(temp_marker);
													(*temp_iter).emplace(f->field_[i][k].tag);
													flag = false;
												//}
											}//*
											else {
												(*temp_iter).emplace(f->field_[i + i1][k + k1].tag);
												(*temp_iter).emplace(temp_marker);
												(*temp_iter).emplace(f->field_[i][k].tag);
												(*temp_iter).insert(it->begin(), it->end());
											}//*/
										}
									}
								}
								temp_marker = f->field_[i + i1][k + k1].tag;
								f->MarkCell(i, k, f->field_[i + i1][k + k1].tag);
							}
						}
						k1 = temp;
					}
					if (f->field_[i][k].tag == 0 && temp_marker == 0) {
						f->MarkCell(i, k, ++marker);
						set<int> temp;
						temp.emplace(f->field_[i][k].tag);
						objects.push_back(temp);
					}
				}
			}
		}
		cout << f->PrintField() << endl;
		obj_number = 0;
		#pragma omp for private (i,k)
		for (i = 0; i < h ; i++) {
			for (k = 0; k < w; k++) {
				if ((f->field_[i][k]).bit) {
					for (vector<set<int>> ::iterator it = objects.begin(); it != objects.end(); ++it)
					{
						if ((*it).find((f->field_[i][k]).tag) != (*it).end()) {
							#pragma omp critical 
							{
								map<set<int>, int>::iterator pos = temp.find(*it);
								if (pos == temp.end()) {
									#pragma omp atomic
									obj_number++;
									f->field_[i][k].tag = obj_number;
									temp.insert(pair<set<int>, int>((*it), obj_number));
									
								} else {
									f->field_[i][k].tag = (*pos).second;
								}
							}
							break;
						}
					}
				}
			}
		}
	}
	cout << f->PrintField() << endl;

	getchar();
	return f->field_;
}

