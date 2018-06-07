# OpenMP-версия студента Куликовой Светланы Александровны

## Структура сборки

1) Before_code

- before_code.cpp - программа для чтения данных, вызова функции для решения СЛАУ, измерения времени её работы и записи результата в бинарный файл

- sol.cpp - файл реализовывает параллельные функции решения СЛАУ методом сопряженных градиентов

## Команды

1) Before_code [number] [input] [output] - запустить на number потоках, считать СЛАУ из бинарного файла input, решить систему и записать результат в бинарный файл output