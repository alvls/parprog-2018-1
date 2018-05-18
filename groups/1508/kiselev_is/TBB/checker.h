#pragma once

#include <cstdio> 
#include <string>
#include <iostream>
#include <cstring>
#include "sol.h"

using namespace std;

// ������������ ��� �������������� � ����������� �������� //////////////////////////////////////////////////////////////////////////////////////////// /* // Checker ����� ������������� ��� ��� ��� ��������: AC = Accepted = ������� ����� ���������� ��������� �� ������ ����� WA = Wrong Answer = ������� ����� ������������ ��������� �� ������ ����� PE = Presentation Error = ������ ������� �������� ������
// ��������� �������� checker �� ����� ������������� 
/*
NO = No verdict = ������� ����������� 
CE = Compilation Error = ������ ���������� 
ML = Memory Limit Exceeded = ��������� ����������� �� ������ 
TL = Time Limit Exceeded = ��������� ����������� �� ������� ������ 
RE = Runtime Error = ������ ������� ���������� ��������� 
IL = Idle Limit Exceeded = ��������� ����� ������� (�����������) ��������� 
DE = Deadly Error = ������ ����������� ������� */ 
enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private: FILE * bur; 
public: 
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY }; 
		
	result(bool read = false) { 
			if (read) bur = fopen("result.txt", "r");
			else bur = fopen("result.txt", "wb"); } 

		~result() { 
			fclose(bur); 
		} 

		void write_type(ext_cls t) { 
			fwrite(&t, sizeof(t), 1, bur); 
		}
		 // �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict 
			 void write_verdict(verdict v) {
				 write_type(ext_cls::VERDICT);
				 fwrite(&v, sizeof (v), 1, bur); 
		 }
		 // �������� ��������� �� checker'a ������������. 
		 // ��������, ��� ������� ������, ��� ��������. 
		 // ������������ ������ ��������� ����� � ����� ���������� 
		 void write_message(string str) {
			 write_type(ext_cls::MESSAGE);
			 int l = str.size ();
			 fwrite(&l, sizeof (l), 1, bur);
			 fwrite (&str[0], sizeof (str[0]), l, bur); 
		 }
		 // �������� ����������� ������� ����� ������ ��������� ���������, 
		 // ����������� � ������� before_code 
		 //  x ����� ����������� 100 �� = 10 ^ (-7) ��� 
		 void write_time(long long x) { write_type(ext_cls::TIME);
		 fwrite(&x, sizeof (x), 1, bur); 
		 }
		 // �������� ����������� �������, ������ ������������� ���������� ��������� 
		 void write_memory(unsigned long long x) { 
			 write_type(ext_cls::MEMORY);
			 fwrite(&x, sizeof (x), 1, bur); 
		 }
		 void write_res(double res) {
			 fwrite(&res, sizeof(double), 1, bur);
		 }

} 
checker_result;
