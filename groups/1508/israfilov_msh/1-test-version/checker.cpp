#include <iostream>
#include <chrono>

// Используется для взаимодействия с тестирующей системой
//////////////////////////////////////////////////////////////////////////////////////////
// Checker может устанавливать вот эти три вердикта:
/* AC = Accepted = Решение выдаёт корректный результат на данном тесте
 * WA = Wrong Answer = Решение выдаёт некорректный результат на данном тесте
 * PE = Presentation Error = Ошибка формата выходных данных*/
// Остальные вердикты checker не может устанавливать
/* NO = No verdict = Вердикт отсутствует
 * CE = Compilation Error = Ошибка компиляции
 * ML = Memory Limit Exceeded = Превышено ограничение по памяти
 * TL = Time Limit Exceeded = Превышено ограничение по времени работы
 * RE = Runtime Error = Ошибка времени исполнения программы
 * IL = Idle Limit Exceeded = Превышено время простоя (бездействия) программы
 * DE = Deadly Error = Ошибка тестирующей системы*/

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result
{
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

    ~result() { fclose (bur); }

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
    void write_message(std::string str) {
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
} checker_result;

int main(int argc, char * argv[]) {
    double res_time, userAnswerX, userAnswerY, userAnswerErr, answerX, answerY, answerErr;

    if (argc == 0) {
        std::cout << "Error: No files" << std::endl;
        return 0;
    }

    std::string userAnswerFileName = argv[1]+std::string(".usans");
    std::string answerFileName = argv[1]+std::string(".ans");

    FILE * userAnswerFile = fopen(userAnswerFileName.c_str(), "rb");
    FILE * answerFile = fopen(answerFileName.c_str(), "rb");

    if (userAnswerFile == NULL || answerFile == NULL) {
        std::cout << "Error: Files cannot opened!" << std::endl;
        return 0;
    }

    fread(&userAnswerX, sizeof(userAnswerX), 1, userAnswerFile);
    fread(&userAnswerY, sizeof(userAnswerY), 1, userAnswerFile);
    fread(&userAnswerErr, sizeof(userAnswerErr), 1, userAnswerFile);

    fread(&answerX, sizeof(answerX), 1, answerFile);
    fread(&answerY, sizeof(answerY), 1, answerFile);
    fread(&answerErr, sizeof(answerErr), 1, answerFile);

    fread(&res_time, sizeof(res_time), 1, userAnswerFile);

    if ((userAnswerErr == 1 && answerErr == 1) || (userAnswerErr != 1 && answerErr != 1)) {
        if (answerErr != 0) {
            double diff = (answerX - userAnswerX) * (answerX - userAnswerX) +
                          (answerY - userAnswerY) * (answerY - userAnswerY);

            if (diff < 1e-6) {
                checker_result.write_message ("AC. Numbers are equal.");
                checker_result.write_verdict (verdict::AC);

            }
            else {
                checker_result.write_message ("WA. Output is not correct.");
                checker_result.write_verdict (verdict::WA);
            }
        }
        else {
            checker_result.write_message ("AC. Incorrect task.");
            checker_result.write_verdict (verdict::AC);
        }
    }
    else {
        checker_result.write_message ("WA. Output is not correct.");
        checker_result.write_verdict (verdict::WA);
    }

    checker_result.write_time (res_time * 1e7);

    fclose(answerFile);
    fclose(userAnswerFile);

    return 0;
}
