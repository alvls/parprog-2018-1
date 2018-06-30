import subprocess
import sys
import os

try:
    os.makedirs('tests')
except Exception:
    print('folder exist')
try:
    os.makedirs('tests\\20tests')
except Exception:
    print('folder exist')

numTest = 20
output = 'tests\\20tests\\'

for i in range(0, numTest):
    subprocess.call(['generator.exe', output+str(i)+'.in', output+str(i)+'.ans', str(i)], stdout=subprocess.PIPE, shell = True) 
print('tests created')