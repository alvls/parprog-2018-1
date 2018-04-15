del time.txt
del res.txt
copy NUL time.txt
copy NUL result.txt
for /L %%i in (0,1,99) do (	
	generator %1 test	
	ompsolver test res %2 >> time.txt	
	checker res
	type result.txt >> res.txt
	echo.>> res.txt
)
sortAndTime.rb
