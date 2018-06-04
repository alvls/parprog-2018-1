del res2.txt
del res4.txt
del res8.txt
for /L %%i in (1,1,20) do (	
	%1 %%i res 2
	checker res
	type result.txt >> res2.txt
	echo.>> res2.txt
)
for /L %%i in (1,1,20) do (	
	%1 %%i res 4
	checker res
	type result.txt >> res4.txt
	echo.>> res4.txt
)
for /L %%i in (1,1,20) do (	
	%1 %%i res 8
	checker res
	type result.txt >> res8.txt
	echo.>> res8.txt
)
