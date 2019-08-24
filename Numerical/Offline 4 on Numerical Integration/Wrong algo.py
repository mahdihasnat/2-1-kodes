# -*- coding: utf-8 -*-
"""
Created on Mon Aug  5 08:32:21 2019

@author: MAHDI
"""
import numpy as np
import matplotlib.pyplot as plt


def Trap(h, f0, f1):
    return h*(f0+f1)/2.0


def Simp13(h, f0, f1, f2):
    return 2*h*(f0+4*f1+f2)/6.0


def Simp38(h, f0, f1, f2, f3):
    return 3*h*(f0+3*(f1+f2)+f3)/8.0


class LabelFlag:
    TrapFlag = False
    Simp13Flag = False
    Simp38Flag = False
    xTicks = list()
    xLabels = list()

def PlotTrap(x0, x1, f0, f1):
    x = np.array([x0, x1, x1, x0])
    y = np.array([0.0, 0.0, f1, f0])
    if LabelFlag.TrapFlag == False:
        plt.fill(x, y, '#6dc6f2', label='Trapizoid Method')
        LabelFlag.TrapFlag = True
    else:
        plt.fill(x, y, '#6dc6f2', label=None)


def GetY(equation, xval):
    Y = 0.0
    for i in range(len(equation)):
        Y = Y + xval ** i * equation[i]
    return Y


def DrawPolinomial(equation, mycolor,mylabel, min_x, max_x):
    x = np.linspace(min_x, max_x, 100, endpoint=True)
    y = GetY(equation, x)
# =============================================================================
#     print(x)
#     print(y)
# =============================================================================
    x = np.append(x, [max_x])
    y = np.append(y, [0])
    x = np.append([min_x], x)
    y = np.append([0], y)
    plt.fill(x, y, mycolor,label=mylabel)


def PlotSimp13(x0, x1, x2, f0, f1, f2):
    a = [[1, x0, x0*x0], [1, x1, x1*x1], [1, x2, x2*x2]]
    b = [f0, f1, f2]
    equation = np.linalg.solve(a, b)
#    print(equation)
    if LabelFlag.Simp13Flag == False:
        LabelFlag.Simp13Flag = True
        DrawPolinomial(equation, '#a8ffae', 'Simpson 1/3 Method', x0, x2)
    else:
        DrawPolinomial(equation, '#a8ffae', None, x0, x2)

def PlotSimp38(x0, x1, x2, x3, f0, f1, f2, f3):
    a = [[1, x0, x0**2, x0**3],
         [1, x1, x1**2, x1**3],
         [1, x2, x2**2, x2**3],
         [1, x3, x3**2, x3**3]]
    b = [f0, f1, f2, f3]
    equation = np.linalg.solve(a, b)
#    print(equation)
    if LabelFlag.Simp38Flag == False:
        LabelFlag.Simp38Flag = True
        DrawPolinomial(equation, '#ffa2a1', 'Simpson 3/8 Method', x0, x3)
    else:
        DrawPolinomial(equation, '#ffa2a1', None, x0, x3)


def TickTrap(x0, x1):
    LabelFlag.xTicks = np.append(LabelFlag.xTicks  , (x0+x1)/2.0 )
    LabelFlag.xLabels = np.append(LabelFlag.xLabels  , 'Trapizoid' )


def TickSimp13(x0, x1):
    LabelFlag.xTicks = np.append(LabelFlag.xTicks  , (x0+x1)/2.0 )
    LabelFlag.xLabels = np.append(LabelFlag.xLabels  , 'Simpson 1/3' )
#    plt.xticks([(x0+x1)/2.0], ['Simpson 1/3'] , rotation=20)


def TickSimp38(x0, x1):
    LabelFlag.xTicks = np.append(LabelFlag.xTicks  , (x0+x1)/2.0 )
    LabelFlag.xLabels = np.append(LabelFlag.xLabels  , 'Simpson 3/8' )
#    plt.xticks([(x0+x1)/2.0], ['Simpson 3/8'] , rotation=20)


def Area(points):
    x = [point[0] for point in points]
    y = [point[1] for point in points]
    n = len(x)
    plt.scatter(x, y, alpha=1, s=10, c='black')
    Trapcnt = 0
    Simp13cnt = 0
    Simp38cnt = 0
    ans = 0.0
    h = x[1]-x[0]
    k = 1
    for i in range(1, n):
        if i == n-1:
            hf = -h
        else:
            hf = x[i+1]-x[i]
#        print(" hf =  ",hf, ' k = ;' , k, ' ans = ' ,ans , ' i = ' , i)
        if abs(hf - h) < 0.001:
            if k == 3:
                ans = ans + Simp13(h, y[i-3], y[i-2], y[i-1])
                PlotSimp13(x[i-3], x[i-2], x[i-1], y[i-3], y[i-2], y[i-1])
                TickSimp13(x[i-3], x[i-2])
                TickSimp13(x[i-2], x[i-1])
                Simp13cnt = Simp13cnt + 2
                k = k-1
            else:
                k = k+1
        else:
            if k == 1:
                ans = ans + Trap(h, y[i-1], y[i])
                PlotTrap(x[i-1], x[i],  y[i-1], y[i])
                TickTrap(x[i-1],x[i])
                Trapcnt = Trapcnt + 1
            elif k == 2:
                ans = ans + Simp13(h, y[i-2], y[i-1], y[i])
                PlotSimp13(x[i-2], x[i-1], x[i], y[i-2], y[i-1], y[i])
                TickSimp13(x[i-2], x[i-1])
                TickSimp13(x[i-1], x[i])
                Simp13cnt = Simp13cnt + 2
            else:
                ans = ans + Simp38(h, y[i-3], y[i-2], y[i-1], y[i])
                PlotSimp38(x[i-3], x[i-2], x[i-1], x[i],
                           y[i-3], y[i-2], y[i-1], y[i])
                TickSimp38(x[i-3], x[i-2])
                TickSimp38(x[i-2], x[i-1])
                TickSimp38(x[i-1], x[i])
                Simp38cnt = Simp38cnt + 3
            k = 1
        h = hf
    print('Trapeziod:', Trapcnt, 'intervals')
    print('1/3 rule:', Simp13cnt, 'intervals')
    print('3/8 rule:', Simp38cnt, 'intervals')
    print()
    return ans


def SetLegend():
    plt.xticks(LabelFlag.xTicks,LabelFlag.xLabels, rotation=90)
    plt.legend()
#    plt.show()
    
    pass

if __name__ == '__main__':
    file = open('input.txt', 'r+')
    n = int(file.readline())
#    print(n)
    points = [list(map(float, line.split(' '))) for line in file.readlines()]
#    print(points)
    
    print('Integral value:', Area(points))
    SetLegend()
# =============================================================================
#     PlotSim13(0,1,5,10,20,40)
#     PlotSim38(0,1,5,10,10,20,40,60)
# =============================================================================
    