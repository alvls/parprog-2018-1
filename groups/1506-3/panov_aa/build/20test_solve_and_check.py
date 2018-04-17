import sys
import subprocess	

numThread = ''	
start = 0
numTest = 20

if len(sys.argv) > 1:	
	numThread = sys.argv[1]
	if len(sys.argv) > 2:
		numTest = int(sys.argv[2])		
		if len(sys.argv) > 3:
			start = int(sys.argv[3])

testinput = 'tests\\' + str(20) + 'tests'
for i in range(start, numTest):
        subprocess.call(['matrix_multiplication.exe', testinput, str(i), numThread], stdout=subprocess.PIPE, shell = True)
    
        
for i in range(start, numTest):
         subprocess.call(['checker.exe', testinput, str(i)], stdout=subprocess.PIPE, shell = True)
