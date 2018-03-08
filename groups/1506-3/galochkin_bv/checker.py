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
    # my filter and OpenCV has a 1 difference in each channel
    tmp = [abs(int(x) - int(y)) for x, y in zip(p1, p2)]
    if tmp[0] > 1 or tmp[1] > 1 or tmp[2] > 1:
        return False
    return True

# get all file names in folder and counts
input_binares = [f for f in listdir(config.checker_binares_dir) if isfile(join(config.checker_binares_dir, f)) and f != "README.md"]
answer_binares = [f for f in listdir(config.checker_answers_dir) if isfile(join(config.checker_answers_dir, f)) and f != "README.md"]

for i in range(0, len(input_binares)):
    try:
        answ, t = reader.read_binary(False, config.checker_answers_dir + answer_binares[i])

        subprocess.check_call([config.linear_version_path, "1", "1", "./tests/" + input_binares[i]])
        res, t = reader.read_binary(True, "image.out") #read output

        h, w, c = res.shape
        cnt = 0
        for y in range(0, h):
            for x in range(0, w):
                if not pixel_checker(res[y,x],answ[y,x]): 
                    cnt += 1

        per = (float(cnt)/(w*h))*100
        print "#" + str(i) + ": " + input_binares[i] + " ~ Bad pixels: " + str(cnt) + "/" + str(w*h) + " "+str(round(per,2)) + "%"

        if cnt < 1:
            logging.info('test{}: AC. Images are equal. Time: {}s'.format(i, t))
        else:
            logging.error('test{}: WA. Output is not correct. Time: {}s'.format(i, t))

    except BaseException:
        logging.warning('test{}: PE. Presentation Error'.format(i))


