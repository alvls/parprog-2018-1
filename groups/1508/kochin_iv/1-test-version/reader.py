import array
import struct
import cv2 as cv
import numpy as np
from config import *

def read_binary(name = binary_output_default):
    fin = open(name, "rb")
    w = struct.unpack('i', fin.read(4))[0] # read an int width 
    h = struct.unpack('i', fin.read(4))[0] # read an int height

    values = array.array('d')
    values.fromfile(fin, w * h * 3)

    blank_image = np.zeros((h,w,3), np.uint8)
    for y in range(0, h):
        for x in range(0, w):
            blank_image[y, x, 0] = values[y * w * 3 + x * 3] # save R
            blank_image[y, x, 1] = values[y * w * 3 + x * 3 + 1] # save G
            blank_image[y, x, 2] = values[y * w * 3 + x * 3 + 2] # save B
    return blank_image

def main():
    cv.imshow('image', read_binary())
    cv.waitKey(0)

if __name__ == "__main__":
    main()
