from subprocess import Popen, PIPE
from sys import argv
from os import listdir

exe_path         = "../build/bin/checker"
binary_files_dir = "tests/"
log_file_path    = "checker_result.txt"

def check(in_file_name):
    comand = "./" + exe_path + " " + binary_files_dir + in_file_name + " " + log_file_path 
    proc = Popen(comand, shell=True, stdout=PIPE, stderr=PIPE)
    proc.wait()

files = listdir(binary_files_dir)

for file in files:
    check(file)
