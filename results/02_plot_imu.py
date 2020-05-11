#!/usr/bin/python
# Requirements: 
# sudo apt-get install python-argparse

import os
import sys
import numpy as np
import math
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

file_result = os.path.abspath('./result1') + '/imu.txt'

def plot_imu():
    ###    load data    ###
    traj_time = np.loadtxt(file_result, usecols=(1))
    traj_time_rel = traj_time - traj_time[0]
    traj_acc = np.loadtxt(file_result, usecols=(2, 3, 4))
    traj_gyro = np.loadtxt(file_result, usecols=(5, 6, 7))

    ###    plot acc   ###
    # fig1, ax1 = plt.subplots(figsize=(6, 3))
    # ax1.plot(traj_time_rel, traj_acc[:,0], linewidth=1.0, color='r', label='x')
    # ax1.plot(traj_time_rel, traj_acc[:,1] * 10, linewidth=1.0, color='g', label='y')
    # ax1.plot(traj_time_rel, traj_acc[:,2], linewidth=1.0, color='b', label='z')
    # ax1.set_xlabel('t [s]', fontsize=10)
    # ax1.set_ylabel('position [m]', fontsize=10)
    # ax1.tick_params(labelsize=9)
    # ax1.legend(loc='upper right', fontsize=8, edgecolor='w')
    # ax1.grid(linestyle="--")

    fig2, (ax21, ax22, ax23) = plt.subplots(3, 1, figsize=(6, 3.5), sharex=True)
    ## x
    ax21.plot(traj_time_rel, traj_acc[:,0], linestyle='-', linewidth=1.0, color='b')
    ax21.set_ylabel('roll [deg]', fontsize=10)
    ax21.tick_params(labelsize=9)
    ax21.grid(linestyle="--")
    ## y
    ax22.plot(traj_time_rel, traj_acc[:,1] * 10, linestyle='-', linewidth=1.0, color='b')
    ax22.set_ylabel('pitch [deg]', fontsize=10)
    ax22.tick_params(labelsize=9)
    ax22.grid(linestyle="--")
    ## z
    ax23.plot(traj_time_rel, traj_acc[:,2], linestyle='-', linewidth=1.0, color='b')
    ax23.set_ylabel('yaw [deg]', fontsize=10)
    ax23.set_xlabel('t [s]', fontsize=10)
    ax23.tick_params(labelsize=9)
    ax23.grid(linestyle="--")

    ###    plot gyro   ###
    fig2, ax2 = plt.subplots(figsize=(6, 3))
    ax2.plot(traj_time_rel, traj_gyro[:,0], linewidth=1.0, color='r', label='x')
    ax2.plot(traj_time_rel, traj_gyro[:,1], linewidth=1.0, color='g', label='y')
    ax2.plot(traj_time_rel, traj_gyro[:,2], linewidth=1.0, color='b', label='z')
    ax2.set_xlabel('t [s]', fontsize=10)
    ax2.set_ylabel('position [m]', fontsize=10)
    ax2.tick_params(labelsize=9)
    ax2.legend(loc='upper right', fontsize=8, edgecolor='w')
    ax2.grid(linestyle="--")


if __name__=="__main__":
    plot_imu()

    plt.show()
