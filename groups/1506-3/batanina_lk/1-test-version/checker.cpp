#include "checker.h"

void Checker::write_type(params_ param){
	result_checker_ << static_cast<int>(param) << std::endl;
}

void Checker::write_verdict(verdict v){
	result_checker_ << v;
}

void Checker::write_message(std::string message){
	result_checker_ << message << "\n";
}
