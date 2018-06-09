rem скрипт запуска генератора тестов в папку (25 тестов), программы сортировки сгенерированных файлов, 
rem программы доверительной сортировки и программы проверки (все выходные файлы ложатся в папку tests)
rem Вторым параметром вызова у Solution.exe пишется число потоков (или ничего не пишется, если нужно взять их число по умолчанию)
mkdir tests
FOR /L %%i IN (1,1,25) DO start /wait .\Omp_Lab1_GribovPN\x64\Release\Generator.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait .\Omp_Lab1_GribovPN\x64\Release\Solution.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait .\Omp_Lab1_GribovPN\x64\Release\TrueSolution.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait .\Omp_Lab1_GribovPN\x64\Release\Checker.exe %%i
rem FOR /L %%i IN (1,1,25) DO start /wait Viewer.exe %%i.ans rem & timeout /t 1 /nobreak>nul