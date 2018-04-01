// sol.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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

	bool OpenNearCell(int x, int y, int marker) {
		if (field_[x][y].tag == 0 && field_[x][y].tag < marker) {
			MarkCell(x, y, marker);
		}
		else
			return false;
		int i1, k1, Hlimit, Wlimit, temp;
		k1 = i1 = temp = -1;
		Wlimit = Hlimit = 2;
		if (x == 0)
			i1 = 0;
		if (x == Height_ - 1)
			Hlimit = 1;
		if (y == 0)
			k1 = temp = 0;
		if (y == Width_ - 1)
			Wlimit = 1;
		for (; i1 < Hlimit; i1++) {
			for (; k1 < Wlimit; k1++) {
				if (field_[x + i1][y + k1].bit && (x + i1 != x || y != y + k1) && field_[x + i1][y + k1].tag != marker)
					OpenNearCell(x + i1, y + k1, marker);
			}
			k1 = temp;
		}
		return true;
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
Cell** serial_alg(int w,int h, int *arr)
{
	int marker = 1;
	Field *f = new Field(w, h, arr);
	cout << f->PrintField() << endl;
	for (int i = 0; i < w; i++) {
		for (int k = 0; k < h; k++) {
			if ((f->field_[i][k]).bit) {
				if(f->OpenNearCell(i, k, marker))
					marker++;
				cout << f->PrintField() << endl;
			}
		}
	}
	cout << f->PrintField() << endl;
	getchar();
    return f->field_;
}

