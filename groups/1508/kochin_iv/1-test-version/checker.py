import subprocess
from os import listdir
from os.path import isfile, join
import config
import reader
import writer
import logging

open('result.txt', 'w').close()
logging.basicConfig(filename='result.txt', level=logging.DEBUG)

def pixel_checker(p1, p2):
    # my filter and OpenCV has a 3 difference in each channel
    tmp = [abs(int(x) - int(y)) for x, y in zip(p1, p2)]
    if tmp[0] > 100 or tmp[1] > 100 or tmp[2] > 100:
        return False
    return True

# get all file names in folder and counts
input_binares = [f for f in listdir(config.checker_binares_dir) if isfile(join(config.checker_binares_dir, f)) and f != "README.md"]
answer_binares = [f for f in listdir(config.checker_answers_dir) if isfile(join(config.checker_answers_dir, f)) and f != "README.md"]

for i in range(0, len(input_binares)):
    try:
        answ = reader.read_binary(config.checker_answers_dir + answer_binares[i])

        # exec program with algorithm with current test input
        subprocess.check_call([config.linear_version_path, "./tests/" + input_binares[i]])
        res = reader.read_binary("bin.out") #read output

        h, w, c = res.shape
        cnt = 0
        # check each pixel
        for y in range(0, h):
            for x in range(0, w):
                if not pixel_checker(res[y,x],answ[y,x]): 
                    cnt += 1

        if cnt < 1: 
            logging.info('test{}: AC. Results are equal.'.i)
        else:
            logging.error('test{}: WA. Output is not correct.'.i)

    except BaseException:
        logging.warning('test{}: PE. Presentation Error'.format(i))
