import subprocess
import sys
import os

try:
    os.makedirs('tests')
except Exception:
    print('folder exist')
output = 'tests\\big_tests\\'
try:
    os.makedirs('tests\\big_tests\\')
except Exception:
    print('folder exist')
print('print size matrix')
size = int(input())

subprocess.call(['generator.exe', output+str(size)+'.in', output+str(size)+'.ans', str(size)], stdout=subprocess.PIPE, shell = True) 
print('test created')