# -*- coding: utf-8 -*-
"""
Created on Sun May 19 01:37:06 2019

@author: MAHDI
"""
import numpy as np
import matplotlib.pyplot as plt

p=3
k=.05

def f(x):
    with np.errstate( divide='ignore', invalid='ignore'):
        return x/(1.0-x)*np.sqrt(2*p/(2+x),dtype=np.float)-k;

def PlotGraph():
    xvalues=np.linspace(-10,10,dtype=np.float,num=101)
    yvalues=f(xvalues)
    plt.figure(1)
    plt.plot(xvalues,yvalues,label="f(x)")
    plt.xlabel("x")
    plt.ylabel("f (x)")
    plt.legend(loc="lower right")
    plt.show()
    

def ApproxErrorBisection(xl,xu):
    return np.abs((xu-xl)/(xu+xl),dtype=np.float)

def Bisection(xl,xu,es,max_iteration):
    xl=float(xl)
    xu=float(xu)
    es=float(es)
    
    if f(xl)*f(xu) >0 :
        raise ValueError("Can't find root ")
    ea=1.1*es+1
    total_iteration=0
    xr=(xl+xu)/2.0
    while max_iteration>=total_iteration and ea > es:
        #print("ea ",ea," xl ",xl," xu ",xu," fxl ",f(xl)," fxu ",f(xu)," gun = ",f(xl)*f(xu))
        total_iteration+=1
        #assert(f(xl)*f(xu)<=0)
        #assert(xl!=xu)
        xr= (xl+xu)/2.0
        if xu+xl!=0.0:
            ea=ApproxErrorBisection(xl,xu)
        test = f(xl)*f(xr)
        if test == 0.0 :
            ea=0
        elif test<0:
            xu=xr
        else :
            xl=xr
    print("Total Iteration Taken",total_iteration,"Approximate Error ",ea)
    return xr

def ApproxErrorOpenMethod(x1,x2):
    return np.abs((x2-x1)/x2,dtype=np.float)

def SecantMethod(x1,x2,es,max_iteration):
    x1=float(x1)
    x2=float(x2)
    es=float(es)
    total_iteration=0
    while True :
        total_iteration+=1
        x1,x2 = x2 , x2-f(x2)*(x1-x2)/(f(x1)-f(x2))
        ea=ApproxErrorOpenMethod(x1,x2)
        if ea <=es or total_iteration >= max_iteration :
            break 
    print("Total Iteration Taken",total_iteration,"Approximate Error ",ea)
    return x2

def FalsePosition(xl,xu,es,max_iteration):
    xl=float(xl)
    xu=float(xu)
    es=float(es)
    
    if f(xl)*f(xu) >0 :
        raise ValueError("Can't find root ")
    ea=1.1*es+1
    total_iteration=0
    xr=xu-f(xu)*(xl-xu)/(f(xl)-f(xu))
    xrold=xr
    while max_iteration>total_iteration and ea > es:
        #print("ea ",ea," xl ",xl," xu ",xu," fxl ",f(xl)," fxu ",f(xu)," gun = ",f(xl)*f(xu))
        total_iteration+=1
        #assert(f(xl)*f(xu)<=0)
        #assert(xl!=xu)
        xr= xu-f(xu)*(xl-xu)/(f(xl)-f(xu))
        if xr!=0.0 and total_iteration>1:
            ea=np.abs((xrold-xr)/xr)
        xrold=xr
        test = f(xl)*f(xr)
        if test == 0.0 :
            ea=0
        elif test<0:
            xu=xr
        else :
            xl=xr
    print("Total Iteration Taken",total_iteration,"Approximate Error ",ea)
    return xr


        

if __name__ == '__main__':
    PlotGraph()
    print("%.70f"%  SecantMethod(-1.9,.9,0.0,100000))

