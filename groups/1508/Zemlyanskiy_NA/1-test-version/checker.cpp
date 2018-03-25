#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstdlib>

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

class result {
private:
FILE * bur;

public:
  enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
  result (bool read = false) {
    if (read)
      bur = fopen("result.txt", "r");
    else
      bur = fopen("result.txt", "w");
    }

  ~result() {
    fclose (bur);
  }

  void write_type(ext_cls t) {
    fwrite(&t, sizeof(t), 1, bur);
  }

  // Сообщить тестирующей системе, что решение получило один из вердиктов verdict
  void write_verdict(verdict v) {
    write_type(ext_cls::VERDICT);
    fwrite(&v, sizeof(v), 1, bur);
  }

  // Написать сообщение от checker'a пользователю.
  //
  //Например, что решение верное, или неверное.
  //
  //Использовать только латинские буквы и знаки препинания
  void write_message(string str) {
    write_type(ext_cls::MESSAGE);
    int l = str.size ();
    fwrite(&l, sizeof (l), 1, bur);
    fwrite (&str[0], sizeof (str[0]), l, bur);
  }

  // Сообщить тестирующей системе время работы программы участника,
  //
  //вычисленное с помощью before_code
  // x имеет размерность 100 нс = 10 ^ (-7) сек
  void write_time(long long x) {
    write_type(ext_cls::TIME);
    fwrite(&x, sizeof (x), 1, bur);
  }

  // Сообщить тестирующей системе, память затребованную программой участника
  void write_memory(unsigned long long x) {
    write_type(ext_cls::MEMORY);
    fwrite(&x, sizeof (x), 1, bur);
  }
} checker_result;


int main (int argc, char* argv[]) {
  string start_out_name = "tests/output/";
  string start_ans_name = "tests/";

  string end_out_name = argv[1];
  string end_ans_name = argv[2];

  string out_file_name = start_out_name + end_out_name;
  string ans_file_name = start_ans_name + end_ans_name;

  // Открываем
  FILE* buo = fopen(out_file_name.c_str(), "r");
  FILE* bua = fopen(ans_file_name.c_str(), "r");

  // if(argc != 3) {
  //   cout << "Can't start the programm" << endl;
  //   cout << "Please enter the arguments" << endl;
  //   cout << "Like this: ./checker [output] [answer]" << endl;
  //   exit(-1);
  // }

  // if(buo == NULL || bua == NULL) {
  //   cout << "Can't open one of files" << endl;
  //   exit(-1);
  // }

  int n;

  double ans_time;
  double res_time;

  fread(&res_time, sizeof(res_time), 1, buo);
  fread(&n, sizeof(n), 1, buo);


  // Выделяем память для массива ответа и ответа участника
  int* ans = new int[n];
  int* res = new int[n];

  // Считываем время работы программы и массив
  fread(res, sizeof(*res), n, buo);
  fread(&ans_time, sizeof(ans_time), 1, bua);
  fread(&n, sizeof(n), 1, bua);
  fread(ans, sizeof(*ans), n, bua);

  // Вычисляем ошибку, как квадрат нормы разности решений
  int diff = 0;
  for (int i = 0; i < n; i++)
    diff += (ans[i] - res[i]);

  // Проверяем, что ошибка мала,
  if (diff < 1) {
    checker_result.write_message("AC. Numbers are equal.");
    checker_result.write_verdict(verdict::AC);
  }
  else {
    checker_result.write_message("WA. Output is not correct.");
    checker_result.write_verdict(verdict::WA);
  }

  // Записываем время в правильной размерности (интервалы по 100 нс = 10 ^ (-7) сек).
  checker_result.write_time(res_time * 1e7);

  fclose(bua);
  fclose(buo);

  return 0;
}
