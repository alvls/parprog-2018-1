import subprocess
numTest = 20
output = 'tests\\' + str(numTest) + 'tests'
for i in range(numTest):
    subprocess.call(['generator.exe', output, str(i)], stdout=subprocess.PIPE, shell = True) 
