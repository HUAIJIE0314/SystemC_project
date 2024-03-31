#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 28 21:41:44 2024

@author: jay
"""

import numpy as np
from numpy import fft
import matplotlib.pyplot as plt
import math
import random

# ================= generate the input signal =================
N = 64

sample_rate = 32


N = 640

sample_rate = 32*5



sample_period = 1 / sample_rate

t_arr = np.arange(0, N*sample_period, sample_period)


freq_list = [100, 110, 120, 130, 140, 150, 160, 170, 180, 200, 1800, 2000, 2500]
freq_list = [100, 1800, 2000, 2500]
freq_list = [2, 10, 13, 23, 37, 43, 53, 67, 71, 93]
freq_list = [2, 53, 97, 107]
freq_list = [2, 53]

for idx in range(len(freq_list)):
    freq = freq_list[idx]
    
    if idx == 0:
        out = np.uint32(2**25 * (1 + np.sin(2 * np.pi * freq * t_arr)))
    else:
        out += np.uint32(2**25 * (1 + np.sin(2 * np.pi * freq * t_arr)))

plt.figure()
plt.plot(t_arr[0:], out[0:])
plt.title('input data')




f = open('firData', 'w+')
for i in range(len(out)):
    f.write('0'*(8-len(hex(out[i, ])[2:])) + hex(out[i, ])[2:] + '\n')
f.close()



def FIR(arrIn, stage):
    
    N = len(arrIn)
    
    coef = 1 / stage
    
    print('coef = ', coef)
    
    outArr = np.array([])
    
    for i in range(N):
        avgArr = []
        print()
        for j in range(stage+1):
            index = i - j
            
            if index < 0:
                data = 0
            else:
                data = int(arrIn[index] * coef)
            
            if(i==0):print('data = ', data, 'index = ', index)
            avgArr.append(data)
        
        avg = sum(avgArr)
        
        if(i==0):print('avg = ', avg)
        
        outArr = np.append(outArr, avg)
        
            #print(index)
        #print()
        
    return outArr.astype(np.uint32)
    


def FIR_FixedPoint(arrIn, stage):
    
    N = len(arrIn)
    
    coef = int(2**16* (1/(stage+1))) #for 1/16
    
    #print('coef = ', coef)
    
    outArr = np.array([])
    
    for i in range(N):
        avgArr = []
        #print()
        for j in range(stage+1):
            index = i - j
            
            if index < 0:
                data = 0
            else:
                data = int(arrIn[index] * coef)
            
            #if(i==0):print('data = ', data, 'index = ', index)
            avgArr.append(data)
        
        avg = sum(avgArr) // 2**16
        
        #if(i==0):print('avg = ', avg)
        
        outArr = np.append(outArr, avg)
        
        
    return outArr.astype(np.uint32)


result = FIR_FixedPoint(out, 16)
plt.figure()
plt.plot(t_arr[0:], result[0:])
plt.title('after FIR')


f = open('goldenData', 'w+')
for i in range(len(out)):
    f.write('0'*(8-len(hex(result[i, ])[2:])) + hex(result[i, ])[2:] + '\n')
f.close()