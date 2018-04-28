#!/bin/bash
printf "compiling generator\n"
g++ -O3 ./Test/generator.cpp -o ./Test/gen
printf "compiling typer\n"
g++ -O3 ./Test/typer.cpp -o ./Test/t
printf "compiling main program\n"
g++ -O3 ./Test/before_code.cpp -fopenmp -ltbb -o ./Test/b
printf "compiling viewer\n"
g++ -O3 ./Test/viewer.cpp -o ./Test/v
printf "done\n"
