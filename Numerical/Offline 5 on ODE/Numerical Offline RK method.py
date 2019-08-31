  # -*- coding: utf-8 -*-
"""
Created on Sun Aug 25 19:14:27 2019

@author: Browsing
"""
import numpy as np
import matplotlib.pyplot as plt

def f(x, y):
    return (x+20.0*y)*np.sin(x*y)
#    return 3*x

def RK2(startX , startY , endX , h , a2):
    a1 = 1.0- a2
    p1 = 0.5/a2
    q11 = 0.5/a2
    x = list()
    y = list()
    while startX <= endX:
        x.append(startX)
        y.append(startY)
        k1 = f(startX , startY)
        k2 = f(startX +p1 *h , startY + q11 * k1 * h)
        startY = startY + (a1 * k1 + a2 * k2 ) * h
        startX = startX + h
    return x,y

def Euler(startX , startY , endX , h ):
    x = list()
    y = list()
    while startX <= endX:
        x.append(startX)
        y.append(startY)
        startY = startY + f(startX , startY ) * h
        startX = startX + h
    return x,y

def Heun( startX , startY , endX , h ):
    return RK2(startX , startY , endX , h , 0.5 )


def MidPoint( startX , startY , endX , h ):
    return RK2(startX , startY , endX , h , 1.0 )


def Ralston( startX , startY , endX , h ):
    return RK2(startX , startY , endX , h , 2.0/3.0 )

def RK4(startX , startY , endX , h):
    x = list()
    y = list()
    while startX <= endX:
        x.append(startX)
        y.append(startY)
        k1 = f(startX, startY)
        k2 = f( startX + 0.5 * h , startY + 0.5 * k1 * h)
        k3 = f(startX + 0.5 * h , startY +  0.5 * k2 * h)
        k4 = f(startX + h , startY + k3* h )
        startY = startY + (k1 + 2 *k2 + 2* k3 + k4 ) * h /6.0
        startX = startX + h
    return x,y

def SubPlot1(startX , startY , endX , hs , Title , func ):
    
    plt.title(Title)
    for h in hs:
        x , y = func(startX , startY , endX , h)
#        plt.ylim(-200.0 , 200.0)
        plt.plot(x,y , label = "h = %f"%(h))
    plt.legend()


def SubPlot2(startX , startY , endX , h , Title ):
    plt.title(Title)
    x,y= Euler(startX , startY , endX , h )
    plt.plot( x, y , label = "Euler method")
    
    x,y= Heun(startX , startY , endX , h )
#    plt.ylim(-200.0 , 200.0)
    plt.plot( x, y , label = "Heun's Method")
    
    x,y= MidPoint(startX , startY , endX , h )
#    plt.ylim(-200.0 , 200.0)
    plt.plot( x, y , label = "Midpoint Method")
   
    x,y= Ralston(startX , startY , endX , h )
#    plt.ylim(-200.0 , 200.0)
    plt.plot( x, y , label = "Ralston’s Method")
    
    x,y= RK4(startX , startY , endX , h )
#    plt.ylim(-200.0 , 200.0)
    plt.plot( x, y , label = "4th order RK Method")
    
    plt.legend()
    
def Plot1(startX , startY , endX , hs):
    plt.figure(1,[10,10] )
    SubPlot1(startX,startY , endX , hs , "Euler Method" ,Euler )
    plt.figure(2,[10,10] )
    SubPlot1(startX,startY , endX , hs , "Heun's Method" ,Heun )
    plt.figure(3,[10,10] )
    SubPlot1(startX,startY , endX , hs , "Midpoint Method" ,MidPoint )
    plt.figure(4,[10,10] )
    SubPlot1(startX,startY , endX , hs , "Ralston’s Method" ,Ralston )
    plt.figure(5,[10,10] )
    SubPlot1(startX,startY , endX , hs , "4th order RK Method" ,RK4 )

def Plot2(startX , startY , endX , hs):
    
    for i in range( len(hs) ):
        plt.figure(i+6,[10, 10])
        h=hs[i]
        SubPlot2(startX , startY , endX , h , "h = %f"%(h)   )
    
if __name__ == '__main__':
#    print(RK2(0.0 , 1.0 , 10.0 , 0.5 , 0.5))
    
    Plot1(0.0 , 4.0 , 10.0 ,[0.01, 0.05, 0.1, 0.5 ])
    Plot2(0.0 , 4.0 , 10.0 ,[0.01, 0.05, 0.1, 0.5 ])
