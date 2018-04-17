import subprocess
import sys
start = 0
numTest = 20
output = 'tests\\' + str(numTest) + 'tests'

if len(sys.argv) > 1:
	numTest = int(sys.argv[1])
	
for i in range(start, numTest):
    subprocess.call(['generator.exe', output, str(i)], stdout=subprocess.PIPE, shell = True) 
