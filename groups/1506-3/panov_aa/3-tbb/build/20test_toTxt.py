import subprocess
import os
numTest = 20
testinput = 'tests\\20tests\\'
for i in range(0, numTest):
    subprocess.call(['binaryToTxt.exe', testinput+str(i)+'.in', testinput+str(i)+'.txt', testinput+str(i)+'.ans', testinput+str(i)+'.ans.txt'], stdout=subprocess.PIPE, shell = True)
    print('matrix A, B, res bin to txt '+str(i))
