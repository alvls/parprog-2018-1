import sys
import subprocess	
import os

numTest = 20
numThread = 1
print('print num threads')
numThread = int(input())
testinput = 'tests\\20tests'
if os.path.exists(testinput):
    
    try:
        os.makedirs('tests\\20tests_result')
    except Exception:
        print('folder exist')
    
    for i in range(0, numTest):
        number = str(i)
        if numThread != 1:
            subprocess.call(['matrix_multiplication.exe', testinput+'\\'+number+'.in', testinput+'_result\\'+number+'.user.ans', str(numThread)], stdout=subprocess.PIPE, shell = True)
        else:
            subprocess.call(['matrix_multiplication.exe', testinput+'\\'+number+'.in', testinput+'_result\\'+number+'.user.ans'], stdout=subprocess.PIPE, shell = True)
        print('solved test '+str(i))
        for i in range(0, numTest):
            subprocess.call(['checker.exe', testinput+'_result\\'+number+'.res.txt', testinput+'_result\\'+number+'.user.ans', testinput+'\\'+number+'.ans'], stdout=subprocess.PIPE, shell = True)
