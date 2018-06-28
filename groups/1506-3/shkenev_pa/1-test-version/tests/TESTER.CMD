@ECHO OFF

SetLocal EnableDelayedExpansion

set testsdir=.\
set exedir=..\release\

FOR %%i IN (%testsdir%*.PNG) DO (
	set name=%%~i
	set name=!name:.PNG=!
	echo !name!
	%exedir%typer.exe !name!.PNG !name!
	%exedir%solver.exe !name! !name!.ans
	%exedir%checker.exe !name!.ans !name!.model
	REM %exedir%viewer.exe !name!.ans !name!.ans.PNG
)
