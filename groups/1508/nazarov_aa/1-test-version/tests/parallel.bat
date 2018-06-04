for /l %%i in (0,1,20) do (
 for /l %%j in (1,1,4) do omp_solver %%i %%i_%%j.omp %%j
)
for /l %%i in (0,1,20) do (
 for /l %%j in (1,1,4) do tbb_solver %%i %%i_%%j.tbb %%j
)