import struct
import cv2 as cv
import numpy as np
from config import *
from array import *

def save_to_binary(img, name = binary_input_default):
    bin_array = array('d')
    h, w, c = img.shape

    with open(name, 'wb') as f:
        f.write(struct.pack('i', w)) # write an int width 
        f.write(struct.pack('i', h)) # write an int height

        for y in range(0, h):
            for x in range(0, w):
                bin_array.append(img[y, x, 0]) # R channel
                bin_array.append(img[y, x, 1]) # G
                bin_array.append(img[y, x, 2]) # B
        bin_array.tofile(f)


# read image by OpenCV
def main():
    save_to_binary(cv.imread(test_image_path, cv.IMREAD_COLOR))

if __name__ == "__main__":
    main()
