import subprocess
numTest = 20
testinput = 'tests\\' + str(numTest) + 'tests'
for i in range(numTest):
    subprocess.call(['binaryToTxt.exe', testinput, str(i)], stdout=subprocess.PIPE, shell = True)
