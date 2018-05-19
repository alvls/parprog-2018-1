#ifndef LINEAR_CORRECTION_CHECKER_H
#define LINEAR_CORRECTION_CHECKER_H

#include <iostream>
#include <fstream>
#include <string>

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class Checker{
	public:
		Checker(const std::string& result_path){
			result_checker_.open(result_path);
		}

		~Checker(){
			result_checker_.close();
		}

	private:
		std::ofstream result_checker_;
		enum class params_ { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	public:
		void write_type(params_ param);
		void write_verdict(verdict v);
		void write_message(std::string message);
};
#endif //LINEAR_CORRECTION_CHECKER_H 
