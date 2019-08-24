# -*- coding: utf-8 -*-
"""
Created on Mon Aug  5 13:07:48 2019

@author: MAHDI
"""
import numpy as np
import matplotlib.pyplot as plt
import sys

def GetY(equation, xval):
    Y = 0.0
    for i in range(len(equation)):
        Y = Y + xval ** i * equation[i]
    return Y
sys.stdout= open('input.txt','w')
eq =[ 1,-2,3,-4,5,-6]
x = np.linspace(0,2*np.pi, 500, endpoint=True)
#x = np.append(x , np.linspace(10.5,20,30))
print(len(x))
for i in x:
    print(i,np.sin(i))