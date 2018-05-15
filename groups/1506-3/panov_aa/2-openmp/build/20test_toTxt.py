import subprocess
start = 0
numTest = 20
testinput = 'tests\\' + str(numTest) + 'tests'
for i in range(start, numTest):
    subprocess.call(['binaryToTxt.exe', testinput, str(i)], stdout=subprocess.PIPE, shell = True)
