# -*- coding: utf-8 -*-
"""
Created on Fri Jul 26 08:20:48 2019

@author: MAHDI
"""
import numpy as np
import matplotlib.pyplot as plt
def GetY(solution , xval):
    Y=0.0
    for i in range(len(solution)):
        Y = Y+ xval**i * solution[i]
    return Y
def DrawPolinomial(solution,mycolor,mylabel):
    x= np.linspace(0.0,11,100)
#    print(x)
    #y=np.array( [GetY(solution,xval) for xval in x])
    y=GetY(solution,x)
#    print(y)
    plt.plot(x,y,color=mycolor,label=mylabel)
def PolinomialRegression(x,y,n,m):
    """
    m= order of polinomial
    """
# =============================================================================
#     if n<m+1:
#         return "impossible"
# =============================================================================
    a=np.zeros((m+1,m+1))
    b=np.zeros((m+1))
#    print(a,b)
    for i in range(m+1):
        sum = np.sum(x**i)
        xid=0
        yid=i
        while yid>=0:
            a[xid][yid]=sum
            xid = xid +1
            yid = yid -1
    for i in range(m+1,m+m+1):
        sum= np.sum(x**i)
        xid=i-m
        yid=m
        while xid<=m:
            a[xid][yid]=sum
            xid = xid +1
            yid = yid -1
#    print(a)
    for i in range(m+1):
        sum = np.sum([(xx**i) * yy for (xx,yy) in zip(x,y) ])
#        print(sum)
        b[i]=sum
#    print(b)
    sol = np.linalg.solve(a,b)
    return sol
def PrintSolution(Solution,x,y):
    print('----------============----------')
    print('Order of polynomial',len(Solution)-1)
    for i in range(len(Solution)):
        print('a',i,' = ',Solution[i],sep='')
    print('Regression coefficient:',RegressionCoefficient(Solution,x,y))
    print('----------============----------')
def RegressionCoefficient(Solution, x,y):
    yavg = np.sum(y) / len(y)
#    print(yavg)
    St = np.sum(np.array([(yval-yavg)*(yval-yavg) for yval in y]))
#    print(St)
    Sr = np.sum(np.array([(yval - GetY(Solution,xval))*(yval - GetY(Solution,xval)) for (xval,yval) in zip(x,y)]))
    return np.sqrt(1.0-Sr/St)

if __name__ == '__main__':
    file = open('data.txt', 'r+')
    data = [list(map(float,line.split(' '))) for line in file.readlines() ]
#    print(data)
    x= [dat[0] for dat  in data]
    y= [dat[1] for dat  in data]
    x=np.array(x)
    y=np.array(y)
    assert(len(x)==len(y))
    n=len(x)
# =============================================================================
#     for i in zip(x,y):
#         print(i)
# =============================================================================
    plt.figure(figsize=(15,15))
    plt.scatter(x,y,s=0.5,color = 'purple',label='original data')
    sol1 = PolinomialRegression(x,y,n,1)
    DrawPolinomial(sol1,'red','First order fit')
    
    sol2 = PolinomialRegression(x,y,n,2)
    DrawPolinomial(sol2,'black','Second order fit')
    
    sol3 = PolinomialRegression(x,y,n,3)
    DrawPolinomial(sol3,'green','Third order fit')
    
    plt.legend(loc='best',title='Curve Fitting Example')
    
# =============================================================================
#     sol100=PolinomialRegression(x,y,n,100)
#     DrawPolinomial(sol100,'pink','100th Order fit')
# =============================================================================
    
    PrintSolution(sol1,x,y)
    PrintSolution(sol2,x,y)
    PrintSolution(sol3,x,y)
#    PrintSolution(sol100,x,y)
# =============================================================================
#     print(sol1)
#     print(RegressionCoefficient(sol1,x,y))
#     
#     print(sol2)
#     print(RegressionCoefficient(sol2,x,y))
#     print(sol3)
#     print(RegressionCoefficient(sol3,x,y))
# =============================================================================
        