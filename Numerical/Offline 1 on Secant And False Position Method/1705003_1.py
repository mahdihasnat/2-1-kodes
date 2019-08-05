# -*- coding: utf-8 -*-
"""
Created on Sat May 18 23:37:22 2019

@author: MAHDI
"""
import numpy as np
import matplotlib.pyplot as plt

def myfunction( x , iterations):
    """ using tylor series 
    x must be in range (-1,1]
    """
    if x<=-1.0 or x >1.0 :
        raise ValueError("x not in range (-1,1] ")
    
    
    ans=0.0
    multiply = -x
    for i in range(1,iterations+1):
        #print("i= ",i, " x= ",x," ans ",ans," multiply ",multiply)
        ans+=x/i
        x*=multiply
    return ans


def plotfunctionb() :
    x= np.arange(1,-1,-.1,dtype=np.float)
    #print(x)
    plt.figure(1)
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.plot(x,np.log(1+x),label="Built-in log(x)",linewidth=.5)
    plt.legend(loc="lower right")
    
    
def plotfunctionc() :
    terms=[1, 3, 5, 20, 50]
    x= np.arange(1,-1,-.1,dtype=np.float)
    plt.figure(1)
    for term in terms:
        y=np.array( [myfunction(i,term) for i in x ])
        plt.plot(x,y,label="Term = "+str(term),linewidth=.5)
    plt.legend(loc="lower right")

def getRelativeApproxError(approx , actual):
    return np.abs((actual-approx)/actual,dtype=np.float)

def ploterror():
    
    xvalues=list()
    yvalues=list()
    x=0.5
    ans=0.0
    multiply = -x
    actual=np.log(1.5)
    for i in range(1,50+1):
        #print("i= ",i, " x= ",x," ans ",ans," multiply ",multiply)
        ans+=x/i
        xvalues.append(i)
        yvalues.append(getRelativeApproxError(ans,actual))
        x*=multiply
    
    xvalues=np.array(xvalues)
    yvalues=np.array(yvalues)
    plt.figure(2)
    plt.xlabel("Terms")
    plt.ylabel("Relative Approx. Error ")
    plt.plot(xvalues,yvalues)
    
    
if __name__ == '__main__':
    
    plotfunctionb()
    plotfunctionc()
    ploterror()
    plt.show()
    #plt.savefig("offline1.pdf")
    
    #x=float(input("Enter x: "))
    #iterations=int(input("Enter total iterations: "))
    #print("ln(1+%.10f)= "%x + "%.10f"%(myfunction(x,iterations )))
    