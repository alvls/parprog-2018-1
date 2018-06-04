for /l %%i in (0,1,15) do (
 for /l %%j in (1,1,4) do checker %%i %%i_%%j.tbb %%i.ans
)
for /l %%i in (17,1,20) do (
 for /l %%j in (1,1,4) do checker %%i %%i_%%j.tbb %%i.ans
)
for /l %%i in (0,1,15) do (
 for /l %%j in (1,1,4) do checker %%i %%i_%%j.omp %%i.ans
)
for /l %%i in (17,1,20) do (
 for /l %%j in (1,1,4) do checker %%i %%i_%%j.omp %%i.ans
)
for /l %%j in (1,1,4) do checker 16 16_%%j.omp 16_%%j.omp
pause