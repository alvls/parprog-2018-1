#include "checker.h"


int main(int argc, char * argv[]) {

	if (argc != 3) {
		std::cout << "Use 'checker [number_test]' and 'checker [output file]'" << std::endl;
		return 1;
	}

	int size;

	double Myresult = -10.0;
	double perfect_res = 0.0;

	FILE * buo = fopen(argv[1], "rb");

	fread(&size, sizeof(int), 1, buo);

	double* buf = new double(size);

	Func* fun = new Func(size);
	for (int i = 0; i < 7; i++) {
		fread(buf, sizeof(*buf), size, buo);
		switch (i) {
		case 0: {
			fun->SetCoeffs(buf);
			break;
		}
		case 1: {
			fun->SetXindexs(buf);
			break;
		}
		case 2: {
			fun->SetYindexs(buf);
			break;
		}
		case 3: {
			fun->SetXcos(buf);
			break;
		}
		case 4: {
			fun->SetYcos(buf);
			break;
		}
		case 5: {
			fun->SetXsin(buf);
			break;
		}
		case 6: {
			fun->SetYsin(buf);
			break;
		}
		default:
			break;
		}
	}

	double confines[4];									// границы интегрирования
	fread(confines, sizeof(*confines), 4, buo);

	fclose(buo);
	Myresult = TIntegral(fun, confines[0], confines[1], confines[2], confines[3], 0.01);

	buo = fopen(argv[2], "rb");

	fread(&perfect_res, sizeof(perfect_res), 1, buo);

	if (module(Myresult - perfect_res) < 0.1) {
		checker_result.write_message("AC. Unswer is correct.");
		checker_result.write_verdict(verdict::AC);
	}
	else {
		checker_result.write_message("DE. Incorrect unswer.");
		checker_result.write_verdict(verdict::DE);
	}
	fclose(buo);
	return 0;
}