import subprocess
numTest = 20
testinput = 'tests\\' + str(numTest) + 'tests'
for i in range(numTest):
    subprocess.call(['matrix_multiplication.exe', testinput, str(i)], stdout=subprocess.PIPE, shell = True)
    
        
for i in range(numTest):
    subprocess.call(['checker.exe', testinput, str(i)], stdout=subprocess.PIPE, shell = True)   
