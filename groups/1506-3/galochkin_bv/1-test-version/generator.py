import struct
import cv2 as cv
import numpy as np
from array import *
from os import listdir
import config
import reader
import writer
import subprocess
import random
from os.path import isfile, join

# get all file names in folder
onlyfiles = [f for f in listdir(config.test_imgs_dir) if isfile(join(config.test_imgs_dir, f)) and f != "README.md"]
for i in range(1, len(onlyfiles)):
    print str(i) + "/" +str(len(onlyfiles) - 1)
    f = onlyfiles[i]
    # read image using OpenCV
    img = cv.imread(config.test_imgs_dir + "/" + f, cv.IMREAD_COLOR)
    if type(img) == type(None):
        continue
    # random resize for more faster processing
    img = cv.resize(img, (128 + random.randrange(0, 256, 1), 128 + random.randrange(0, 256, 1))) 

    # processing by cv
    blur = cv.GaussianBlur(img,(3,3),1,1)

    writer.save_to_binary(img, config.checker_binares_dir + str(i) + "")
    writer.save_to_binary(blur, config.checker_answers_dir + str(i) + ".ans")
    