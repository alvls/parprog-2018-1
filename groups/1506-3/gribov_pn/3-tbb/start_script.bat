rem Скрипт запуска генератора тестов в папку (25 тестов), программы сортировки сгенерированных файлов, 
rem программы доверительной сортировки и программы проверки (все выходные файлы ложатся в папку tests)
rem Вторым параметром у Solution.exe указывается число потоков (если не указывать, их число взято будет по умполчанию)
mkdir tests
FOR /L %%i IN (1,1,25) DO start /wait .\Omp_Lab1_GribovPN\x64\Release\Generator.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait .\Omp_Lab1_GribovPN\x64\Release\Solution.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait .\Omp_Lab1_GribovPN\x64\Release\TrueSolution.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait .\Omp_Lab1_GribovPN\x64\Release\Checker.exe %%i
rem FOR /L %%i IN (1,1,25) DO start /wait Viewer.exe %%i.ans rem & timeout /t 1 /nobreak>nul