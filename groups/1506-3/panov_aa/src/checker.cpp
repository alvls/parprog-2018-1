#include <cstdio>
#include <cmath>
#include <string>
#include "../include/matrix.h"
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
string path_result = "";
string output = "result.txt";
class result
{
private:
    FILE * bur;
public:
    enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
    result(bool read = false)
    {
        if (read) bur = fopen((path_result + output).c_str(), "r"); else bur = fopen((path_result + output).c_str(), "w");
    }
    ~result() { fclose(bur); }
    void write_type(ext_cls t) { fwrite(&t, sizeof(t), 1, bur); }
    // Сообщить тестирующей системе, что решение получило один из вердиктов verdict
    void write_verdict(verdict v)
    {
        write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
    }
    // Написать сообщение от checker'a пользователю.
    // Например, что решение верное, или неверное.
    // Использовать только латинские буквы и знаки препинания
    void write_message(string str)
    {
        write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
        fwrite(&str[0], sizeof(str[0]), l, bur);
    }
    // Сообщить тестирующей системе время работы программы участника,
    // вычисленное с помощью before_code
    // x имеет размерность 100 нс = 10 ^ (-7) сек
    void write_time(long long x)
    {
        write_type(ext_cls::TIME); fwrite(&x, sizeof(x), 1, bur);
    }
    // Сообщить тестирующей системе, память затребованную программой участника
    void write_memory(unsigned long long x)
    {
        write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
    }
} checker_result;

int main(int argc, char * argv[])
{
    string path = "";
    string number = "";
    string output = "result.txt";
    string input = "matr";
    string extensionIn = ".in";
    string extensionOutAnswer = ".ans";
    string extensionOutUserAnswer = ".user.ans";
    if (argc > 1)
    {
        path = argv[1];
        path_result = path;
        if (argc > 2)
        {
            path_result = argv[2];
        }
    }
    // Открываем файл входных данных, ответ участника, файл выходных данных c ответом жюри
    FILE * bui = fopen((path + input + number + extensionIn).c_str(), "rb");
    FILE * buo = fopen((path + input + number + extensionOutUserAnswer).c_str(), "rb");
    FILE * bua = fopen((path + input + number + extensionOutAnswer).c_str(), "rb");
    int n;
    // Считываем размерность матриц
    fread(&n, sizeof(n), 1, bui);
    // Выделяем память для матрицы ответа жюри и ответа участника
    Matrix ans(n, n), res(n, n);

    double ans_time, res_time;
    // Считываем время работы программы участника и матрицу участника
    fread(&res_time, sizeof(res_time), 1, buo);
    fread(res.getP(), sizeof(*res.getP()), n * n, buo);
    // Считываем время работы программы и матрицу жюри
    //fread(&ans_time, sizeof(ans_time), 1, bua);
    fread(&n, sizeof(n), 1, bua);
    fread(ans.getP(), sizeof(*ans.getP()), n * n, bua);
    // Вычисляем ошибку, как квадрат нормы разности решений
    double diff = 0.0;
    for (int i = 0; i < n * n; i++)
        diff += (ans.vv[i] - res.vv[i]) * (ans.vv[i] - res.vv[i]);
    // Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно.
    if (diff < 1e-6)
    {
        checker_result.write_message("AC. Numbers are equal.");
        checker_result.write_verdict(verdict::AC);
    }
    else
    {
        checker_result.write_message("WA. Output is not correct.");
        checker_result.write_verdict(verdict::WA);
    }
    // Записываем время в правильной размерности (интервалы по 100 нс = 10 ^ (-7) сек).
    checker_result.write_time(res_time * 1e7);
    fclose(bua);
    fclose(buo);
    return 0;
}