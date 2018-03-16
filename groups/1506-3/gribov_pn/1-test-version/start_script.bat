rem скрипт запуска генератора тестов в папку (25 тестов), программы сортировки сгенерированных файлов, 
rem программы доверительной сортировки и программы проверки (все выходные файлы ложатся в папку tests)
FOR /L %%i IN (1,1,25) DO start /wait Generator.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait Solution.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait TrueSolution.exe %%i
FOR /L %%i IN (1,1,25) DO start /wait Checker.exe %%i
rem FOR /L %%i IN (1,1,25) DO start /wait Viewer.exe %%i.ans rem & timeout /t 1 /nobreak>nul