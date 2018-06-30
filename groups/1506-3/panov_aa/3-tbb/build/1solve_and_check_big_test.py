import sys
import subprocess	
import os

print('print num threads')
numThread = int(input())

print('print size matrix')
size = int(input())

testinput = 'tests\\big_tests\\'
if os.path.exists(testinput):
    number = str(size)
    thread = str(numThread)
    subprocess.call(['matrix_multiplication.exe', testinput+number+'.in', testinput+number+' '+thread+'.user.ans'], stdout=subprocess.PIPE, shell = True)
    print('test solved')
    subprocess.call(['checker.exe', testinput+number+'.res.txt', testinput+number+' '+thread+'.user.ans', testinput+'\\'+number+'.ans'], stdout=subprocess.PIPE, shell = True)
