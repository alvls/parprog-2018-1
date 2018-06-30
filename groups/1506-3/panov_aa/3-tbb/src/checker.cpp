#include <cstdio>
#include <cmath>
#include <string>
#include "../include/mymatrix.h"
using namespace std;
// Используется для взаимодействия с тестирующей системой
////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checker может устанавливать вот эти три вердикта:
AC = Accepted = Решение выдаёт корректный результат на данном тесте
WA = Wrong Answer = Решение выдаёт некорректный результат на данном тесте
PE = Presentation Error = Ошибка формата выходных данных
// Остальные вердикты checker не может устанавливать
NO = No verdict = Вердикт отсутствует
CE = Compilation Error = Ошибка компиляции
ML = Memory Limit Exceeded = Превышено ограничение по памяти
TL = Time Limit Exceeded = Превышено ограничение по времени работы
RE = Runtime Error = Ошибка времени исполнения программы
IL = Idle Limit Exceeded = Превышено время простоя (бездействия) программы
DE = Deadly Error = Ошибка тестирующей системы
*/
enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class Result
{
private:
    FILE * bur;
public:
    enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
    Result(string path)
    {
        bur = fopen(path.c_str(), "w");
    }
    ~Result() 
    { 
        fclose(bur);
    }
    void write_type(ext_cls t) 
    { 
        fwrite(&t, sizeof(t), 1, bur);
    }
    // Сообщить тестирующей системе, что решение получило один из вердиктов verdict
    void write_verdict(verdict v)
    {
        write_type(ext_cls::VERDICT); 
        fwrite(&v, sizeof(v), 1, bur);
    }
    void write_message(string str)
    {
        write_type(ext_cls::MESSAGE); 
        int len = str.size(); 
        fwrite(&len, sizeof(len), 1, bur);
        fwrite(&str[0], sizeof(str[0]), len, bur);
    }
    // Сообщить тестирующей системе время работы программы участника,
    // вычисленное с помощью before_code
    void write_time(double x)
    {
        string s = "\n";
        s += std::to_string(x);
        s += " sec";
        fwrite(&s[0], sizeof(s[0]), s.size(), bur);
    }
    // Сообщить тестирующей системе, память затребованную программой участника
    void write_memory(unsigned long long x)
    {
        write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
    }
};

int main(int argc, char * argv[])
{
	string result;
	string userAnswer;
	string trueAnswer;
	
    if (argc > 1)
    {
		result = argv[1];
        if (argc > 2)
        {
			userAnswer = argv[2];
			if (argc > 3)
				trueAnswer = argv[3];
        }
    }


    Result checker_result(result);

    // Открываем ответ участника, файл выходных данных c ответом жюри
    FILE * buo = fopen(userAnswer.c_str(), "rb");
    FILE * bua = fopen(trueAnswer.c_str(), "rb");
    int n;
	// Считываем  матрицу жюри
	fread(&n, sizeof(n), 1, bua);
	// Выделяем память для матрицы ответа жюри и ответа участника
	Matrix ans(n, n), res(n, n);
	fread(ans.getP(), sizeof(*ans.getP()), n * n, bua);

    double ans_time, res_time;
    // Считываем время работы программы участника и матрицу участника
    fread(&res_time, sizeof(res_time), 1, buo);
    fread(res.getP(), sizeof(*res.getP()), n * n, buo);

    // Вычисляем ошибку, как квадрат нормы разности решений
    double diff = 0.0;
    for (int i = 0; i < n * n; i++)
        diff += (ans.vv[i] - res.vv[i]) * (ans.vv[i] - res.vv[i]);
    // Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно.
    if (diff < 1e-6)
    {
        checker_result.write_message("AC. Numbers are equal.\n");
        checker_result.write_verdict(verdict::AC);
    }
    else
    {
        checker_result.write_message("WA. Output is not correct.\n");
        checker_result.write_verdict(verdict::WA);
    }
    checker_result.write_time(res_time);
    fclose(bua);
    fclose(buo);
    return 0;
}