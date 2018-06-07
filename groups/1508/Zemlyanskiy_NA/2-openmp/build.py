import sys
import os
import shutil

arg_1 = sys.argv[1]

os.system(r'g++ before_code.cpp -o before_code -std=c++11 -fopenmp')

for i in range(11):
	os.system(r'./before_code'+' '+ str(i) +' ' + str(i) + '.ans'+' '+ arg_1)
