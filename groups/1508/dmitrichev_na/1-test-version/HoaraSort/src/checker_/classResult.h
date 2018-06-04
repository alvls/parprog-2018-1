#pragma once

#include <cstdio>
#include <cmath>
#include <string>

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

class result
{
 private:
  FILE * bur;
 public:
   enum ext_cls {
     NO = 1,
     VERDICT,
     MESSAGE,
     TIME,
     MEMORY
   };
   result (bool read = false) {
     if (read)
       bur = fopen("result.txt", "r");
     else bur = fopen("result.txt", "w");
   }
   ~result() {
     fclose (bur);
   }
   void write_type(ext_cls t) {
     fwrite(&t, sizeof (t), 1, bur);
   }
   // Сообщить тестирующей системе, что решение получило один из вердиктов verdict
   void write_verdict(verdict v) {
     write_type(ext_cls::VERDICT);
     fwrite(&v, sizeof (v), 1, bur);
   }
   // Написать сообщение от checker'a пользователю.
   // Например, что решение верное, или неверное.
   // Использовать только латинские буквы и знаки препинания
   void write_message(string str) {
     write_type(ext_cls::MESSAGE);
     int l = str.size ();
     fwrite(&l, sizeof (l), 1, bur);
     fwrite (&str[0], sizeof (str[0]), l, bur);
   }
   // Сообщить тестирующей системе время работы программы участника,
   // вычисленное с помощью before_code
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
  }
checker_result;
