#!/usr/bin/python
# Requirements: 

import os
import sys
import numpy as np
import math
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# file_result = os.path.abspath('./result7') + '/position.txt'
# file_result = os.path.abspath('./result12') + '/position.txt'
# file_result = os.path.abspath('./result23') + '/result23.txt'

# file_result = os.path.abspath('./result_12') + '/result121.txt'
# file_result = os.path.abspath('./result_13') + '/result131.txt'
file_result = os.path.abspath('./result_13') + '/result134.txt'

def plot_position():
    ###    load data    ###
    traj_time = np.loadtxt(file_result, usecols=(1))
    # traj_time_rel = traj_time
    traj_time_rel = traj_time - traj_time[0]
    traj_position = np.loadtxt(file_result, usecols=(2, 3, 4))

    ###    plot trajectory    ###
    # fig1 = plt.figure(num=1, figsize=(6, 4))
    # ax1 = fig1.gca(projection='3d')
    # ax1.plot(traj_position[:,0], traj_position[:,1], traj_position[:,2], linestyle='-', linewidth=1.0, color='b', label='trajectory')
    # ax1.plot([traj_position[0, 0]], [traj_position[0, 1]], [traj_position[0, 2]], 'o', markersize=5, color='r', label='start point')
    # ax1.plot([traj_position[len(traj_position)-1, 0]], [traj_position[len(traj_position)-1, 1]], [traj_position[len(traj_position)-1, 2]], '^', markersize=6, color='r', label='end point')
    # ax1.set_xlabel('x [m]', fontsize=8)
    # ax1.set_ylabel('y [m]', fontsize=8)
    # ax1.set_zlabel('z [m]', fontsize=8)
    # ax1.set_ylim(-0.8, 0.8)
    # ax1.set_zlim(-0.8, 1.5)
    # ax1.tick_params(labelsize=7)
    # ax1.legend(loc='upper right', fontsize=7, edgecolor='w')
    # ax1.grid(linestyle="--")

    ###    plot trajectory x y z    ###
    fig2, ax2 = plt.subplots(figsize=(3.0, 3.5))
    ax2.plot(traj_time_rel, traj_position[:,0], linewidth=1.0, color='r', label='x')
    ax2.plot(traj_time_rel, traj_position[:,1], linewidth=1.0, color='g', label='y')
    ax2.plot(traj_time_rel, traj_position[:,2], linewidth=1.0, color='b', label='z')
    ax2.set_xlabel('t [s]', fontsize=8)
    ax2.set_ylabel('position [m]', fontsize=8)
    ax2.tick_params(labelsize=7)
    ax2.legend(loc='upper right', fontsize=7, edgecolor='w')
    ax2.grid(linestyle="--")
    fig2.savefig("./xyz_traj.png", dpi=300, bbox_inches="tight")

    ###    plot trajectory x y    ###
    # fig3, ax3 = plt.subplots(figsize=(6, 3))
    # ax3.plot(traj_position[:,0], traj_position[:,1], linewidth=1.0, color='b')
    # ax3.set_xlabel('x [m]', fontsize=10)
    # ax3.set_ylabel('y [m]', fontsize=10)
    # ax3.set_ylim(-0.8, 0.8)
    # ax3.grid(linestyle="--")


def plot_euler():
    ###    load data    ###
    traj_time = np.loadtxt(file_result, usecols=(1))
    traj_time_rel = traj_time - traj_time[0]
    traj_euler_deg = np.loadtxt(file_result, usecols=(5, 6, 7))
    # traj_euler_rad = traj_euler_deg * math.pi / 180

    fig4, (ax41, ax42, ax43) = plt.subplots(3, 1, figsize=(3, 3.5), sharex=True)
    ## roll
    ax41.plot(traj_time_rel, traj_euler_deg[:,0], linestyle='-', linewidth=1.0, color='b')
    ax41.set_ylabel('roll [deg]', fontsize=8)
    ax41.tick_params(labelsize=7)
    ax41.grid(linestyle="--")
    ## pitch
    ax42.plot(traj_time_rel, traj_euler_deg[:,1], linestyle='-', linewidth=1.0, color='b')
    ax42.set_ylabel('pitch [deg]', fontsize=8)
    ax42.tick_params(labelsize=7)
    ax42.grid(linestyle="--")
    ## yaw
    ax43.plot(traj_time_rel, traj_euler_deg[:,2], linestyle='-', linewidth=1.0, color='b')
    ax43.set_ylabel('yaw [deg]', fontsize=8)
    ax43.set_xlabel('t [s]', fontsize=8)
    ax43.tick_params(labelsize=7)
    ax43.grid(linestyle="--")
    fig4.savefig("./rpy.png", dpi=300, bbox_inches="tight")
    

if __name__=="__main__":
    plot_position()
    # plot_euler()

    plt.show()
