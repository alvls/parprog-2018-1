# Каталог студента Таламанова Анатолия Евгеньевича

## Структура каталога

- 1-test-version - каталог для размещения файлов тестовой версии
- 2-openmp - каталог для размещения файлов OpenMP-версии
- 3-tbb - каталог для размещения файлов TBB-версии

## Сборка
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
```