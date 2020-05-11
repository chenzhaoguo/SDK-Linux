#!/usr/bin/python
# Requirements: 
# sudo apt-get install python-argparse

import os
import sys
import numpy as np
import re

file_object = open('result13/result_13.txt','rU')

def save_position():
    f = open('result13/position.txt','w')
    for line in file_object:
        g = re.search("slam", line)
        if g:
            f.writelines(line)
    file_object.close()


def save_imu():
    f = open('result/imu.txt','w')
    for line in file_object:
        g = re.search("imu", line)
        if g:
            f.writelines(line)
    file_object.close()


if __name__=="__main__":
    save_position()
    # save_imu()
