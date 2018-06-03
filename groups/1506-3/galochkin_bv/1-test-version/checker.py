import subprocess
from os import listdir
from os.path import isfile, join
import config
import reader
import writer
import logging
from sys import stdout
open('result.txt', 'w').close() # clar log
logging.basicConfig(filename='result.txt', level=logging.DEBUG)

# Print iterations progress
def printProgressBar (iteration, total, prefix = 'Progress', suffix = 'Complete', decimals = 1, length = 50, fill = '#'):
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print '{} |{}| {}% {}'.format(prefix, bar, percent, suffix)

def pixel_checker(p1, p2):
    # my filter and OpenCV has a 1 difference in each channel
    tmp = [abs(int(x) - int(y)) for x, y in zip(p1, p2)]
    if tmp[0] > 1 or tmp[1] > 1 or tmp[2] > 1:
        return False
    return True

def main():
    # get all file names in folder and counts
    input_binares = [f for f in listdir(config.checker_binares_dir) if isfile(join(config.checker_binares_dir, f)) 
                      and not ".ans" in f and f != "README.md"]
    answer_binares = [f for f in listdir(config.checker_answers_dir) if isfile(join(config.checker_answers_dir, f))
                      and ".ans" in f and f != "README.md"]
    # check files count equals
    if len(input_binares) != len(answer_binares):
        print "Inputs files and answers different quantity!"
        return
    # check files names
    for i in range(0, len(input_binares)):
        if answer_binares[i].split('.')[0] != input_binares[i]:
            print "Inputs and answers has different names!"
            return

    for i in range(0, len(input_binares)):
        try:
            answ, t = reader.read_binary(False, config.checker_answers_dir + answer_binares[i])

            # exec program with algorithm with current test input
            subprocess.check_call([config.linear_version_path, "1", "1", "./tests/" + input_binares[i]])
            res, t = reader.read_binary(True, "image.out") #read output

            h, w, c = res.shape
            cnt = 0
            # check each pixel
            for y in range(0, h):
                for x in range(0, w):
                    if not pixel_checker(res[y,x],answ[y,x]): 
                        cnt += 1

            # percentage of "bad" pixels
            per = (float(cnt)/(w*h))*100

            if per < 0.001: 
                logging.info('test{}: AC. Results are equal. Time: {:.3f}s. Bad {:.1f}% {}/{}'.format(i, t, per, cnt, w*h))
            else:
                logging.error('test{}: WA. Output is not correct. Time: {:.3f}s. Bad {:.1f}% {}/{}'.format(i, t, per, cnt, w*h))

            printProgressBar(i, len(input_binares))

        except BaseException:
            logging.warning('test{}: PE. Presentation Error'.format(i))

if __name__ == "__main__":
    main()
