import sys
import os
import shutil

arg_1 = sys.argv[1]

os.system(r'g++ before_code.cpp -o build -std=c++11 -ltbb -fopenmp')

for i in range(13):
	os.system(r'./build'+' '+ str(i) +' ' + str(i) + '.ans'+' '+ arg_1)
	os.system(r'./viewer'+' '+str(i)+'.ans'+' '+str(i)+'.txt')
