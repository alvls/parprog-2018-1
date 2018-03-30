from subprocess import Popen, PIPE
from sys import argv

exe_path = argv[1]
save_dir = argv[2]

def generate(size_array, type_test, save_name):
    comand = "./" + exe_path + " " + str(type_test) + " " + str(size_array) + " " + save_dir +  str(save_name)
    proc = Popen(comand, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()
    
sizes = [10, 100, 1000]

count_type = 6;

num_test = 0
for size in sizes:
    for i in range(count_type):
        generate(size, i, str(i) + "_" + str(size))
        num_test += 1
