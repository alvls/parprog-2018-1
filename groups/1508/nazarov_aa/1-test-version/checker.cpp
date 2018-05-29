#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

enum verdict {NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private:
    FILE * bur;
public:
    enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
    result(bool read = false) {
        if (read) bur = fopen("result.txt", "r"); else bur = fopen("result.txt", "w");
    }
    ~result() { fclose(bur); }

    void write_type(ext_cls t) { fwrite(&t, sizeof(t), 1, bur); }

    void write_verdict(verdict v) {
        write_type(ext_cls::VERDICT);
        fwrite(&v, sizeof(v), 1, bur);
    }

    void write_message(string str) {
        cout << str << endl;
        write_type(ext_cls::MESSAGE);
        int l = str.size();
        fwrite(&l, sizeof(l), 1, bur);
        fwrite(&str[0], sizeof(str[0]), 1, bur);
    }

    void write_time(long long x) {
        cout << "time: " << x << endl;
        write_type(ext_cls::TIME);
        fwrite(&x, sizeof(x), 1, bur);
    }

    void write_memory(unsigned long long x) {
        write_type(ext_cls::MEMORY);
        fwrite(&x, sizeof(x), 1, bur);
    }
} checker_result;


int main(int argc,char* argv[]) {
    if (argc != 4) {
        std::cout << "use '" << argv[0] << "[source file] [result file] [answer file]'" << std::endl;
        return 1;
    }

    FILE * file_source = fopen(argv[1], "rb");
    FILE * file_res = fopen(argv[2], "rb");
    FILE * file_ans = fopen(argv[3], "rb");

    int N_source, N_ans, N_res;
    double res_time, ans_time;
    fread(&N_source, sizeof(N_source), 1, file_source);
    fread(&res_time, sizeof(res_time), 1, file_res);
    fread(&ans_time, sizeof(ans_time), 1, file_ans);
    fread(&N_ans, sizeof(N_ans), 1, file_ans);
    fread(&N_res, sizeof(N_res), 1, file_res);

    if (N_source != N_ans) {
        checker_result.write_message("PE. size of source matrix is not equal size of answer matrix");
        checker_result.write_verdict(verdict::PE);
        return 0;
    }
    if (N_source != N_res) {
        checker_result.write_message("PE. size of source matrix is not equal size of result matrix");
        checker_result.write_verdict(verdict::PE);
        return 0;
    }

    int * J_ans = new int[N_source + 1];
    int * J_res = new int[N_source + 1];

    fread(J_ans, sizeof(*J_ans), N_source + 1, file_ans);
    fread(J_res, sizeof(*J_res), N_source + 1, file_res);
    
    int *I_ans = new int[J_ans[N_source]];
    int *I_res = new int[J_res[N_source]];
    double *ans = new double[J_ans[N_source]];
    double *res = new double[J_res[N_source]];

    fread(I_ans, sizeof(*I_ans), J_ans[N_source], file_ans);
    fread(ans, sizeof(*ans), J_ans[N_source], file_ans);
    fread(I_res, sizeof(*I_res), J_res[N_source], file_res);
    fread(res, sizeof(*res), J_res[N_source], file_res);

    for (int i = 0; i < N_source + 1; i++) {
        if (J_ans[i] != J_res[i]) {
            checker_result.write_message("WA. J array is not equal");
            checker_result.write_verdict(verdict::WA);
            return 0;
        }
    }

    for (int i = 0; i < J_res[N_source]; i++) {
        if (I_ans[i] != I_res[i]) {
            checker_result.write_message("WA. I array is not equal");
            checker_result.write_verdict(verdict::WA);
            return 0;
        }
    }

    double diff = 0.0;
    for (int i = 0; i < J_ans[N_source]; i++)
        diff += (ans[i] - res[i]) * (ans[i] - res[i]);

    if (diff < 1e-6) {
        checker_result.write_message("AC. Numbers are equal.");
        checker_result.write_verdict(verdict::AC);
    } 
    else {
        checker_result.write_message("WA. Output is not correct");
        checker_result.write_verdict(verdict::WA);
    }

    checker_result.write_time(res_time * 1e7);

    fclose(file_res);
    fclose(file_ans);
    fclose(file_source);
    
    return 0;
}