#include "checker.h"

#include <stdio.h>
#include <iostream>



int main(int argc, char * argv[]) {
	

	if (argc != 3) {
		checker_result.write_verdict(NO);
		checker_result.write_message("       No verdict. Bad parameters         ");
		return 1;
	}


	task_scheduler_init init(atoi(argv[1]));
	int size;

	double* buf;

	double perfect_res;
	double line_time;
	double time;

	double confines[4];
	
	FILE * ons;
	FILE * buo;

	Func* fun = nullptr;

		buo = fopen(argv[2], "rb");
		
		fread(&size, sizeof(int), 1, buo);
		buf = new double(size);

		fun = new Func(size);
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
		// границы интегрирования
		fread(confines, sizeof(*confines), 4, buo);


		blocked_range<int> range(0, parts, 25);		// parts = 2000

		Body<double>* bod = new Body<double>(fun, range , confines[0], confines[1], confines[2], confines[3]);

		//fclose(buo);
		time = omp_get_wtime();
		
		parallel_reduce(range, bod);

		time = omp_get_wtime() - time;

		ons = fopen(strcat(argv[2], ".ans"), "rb");
		fread(&perfect_res, sizeof(perfect_res), 1, ons);
		fread(&line_time, sizeof(line_time), 1, ons);

		if (module(bod->Result() - perfect_res) < 1) {
			if (time <= line_time + 10) {
				checker_result.write_message("AC. Unswer is correct.");
				checker_result.write_verdict(AC);
			}
			else {
				checker_result.write_message("TL. Execution time exceeded.");
				checker_result.write_verdict(TL);
			}
		}
		else {
			checker_result.write_message("DE. Incorrect unswer.");
			checker_result.write_verdict(DE);
		}
		fclose(buo);
		fclose(ons);
	
	return 0;
}