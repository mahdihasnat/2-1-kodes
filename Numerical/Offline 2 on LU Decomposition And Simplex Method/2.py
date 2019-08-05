# -*- coding: utf-8 -*-
"""
Created on Sat Jul 13 08:16:00 2019

@author: MAHDI
"""
import numpy as np

def GetHeader(nvar, ncons):
    header = list()
    header.append(' Z')
    for i in range(nvar):
        header.append('X'+str(i+1))
    for i in range(ncons):
        header.append('S'+str(i+1))
    header.append('Sol')
    header.append('Intercept')
    return header
def GetBasic(nvar, ncons):
    Basic =[0]
    for i in range(nvar+1,nvar+ncons+1):
        Basic.append(i)
    return Basic

def PrintTable(nvar , ncons,table,Header,Basic):
    print('Basic    ',end='')
    for i in Header : 
        print(i,end='       ')
    print()
    for i in range(ncons+1):
        print(Header[Basic[i]],end='   ')
        for j in range (nvar+ncons+2):
            print('%8.2f'%(table[i][j]), end= ' ')
        if i != 0:
            print('%8.2f'%(table[i][nvar+ncons+2]), end= ' ')
        print()
        
def GaussJordan(totalBasic,totalColumn,table,pivotBasic,pivotcolumn):
    div= table[pivotBasic][pivotcolumn]
    for i in range(totalColumn):
        table[pivotBasic][i]= table[pivotBasic][i]/div
    for i in range(totalBasic):
        if i != pivotBasic:
            factor = table[i][pivotcolumn]
            for j in range(totalColumn):
                table[i][j] = table[i][j]- factor* table[pivotBasic][j]

def GetTable(nvar, ncons, z, constraints):
    table = np.zeros((ncons+1, nvar+ncons+3))
#    print(table)
    # assign for objective function
    table[0][0] = 1.0
    for i in range(nvar):
        table[0][i+1] = - z[i]

    # now assign every constraing function
    for i in range(ncons):
        table[i+1][nvar+i+1] = 1.0
        for j in range(nvar):
            table[i+1][j+1] = constraints[i][j]
        table[i+1][nvar+ncons+1] = constraints[i][nvar]
        
#    print(table)
    return table
# =============================================================================
# def IsOptimal(nvar,ncons,table):
#     for i in range(1,nvar+ncons+1):
#         if table[0][i] < 0.0:
#             return False
#     return True
# =============================================================================
def GetNonBasic(nvar):
    return np.array([i for i in range(1,nvar+1)])


def SelectEnteringVariableIndex(nvar , nonbasic,table ):
    k = 0
    for i in range(1,nvar):
        if table[0][nonbasic[i]] < table[0][nonbasic[k]]:
            k= i
    return k


def CalculateIntercept(nvar,ncons,table,Basic,non_basic,enteringvar):
    for i in range(ncons):
        table[i+1][nvar+ncons+2]=table[i+1][nvar+ncons+1]/table[i+1][non_basic[enteringvar]]


def GetLeavingVar(nvar , ncons , table ):
    k= -1
    for i in range (1, ncons+1):
#        print (" i= ",i," tab = ",np.abs(table[i][nvar+ncons+2])," k= ",k," tab= ",np.abs(table[k][nvar+ncons+2]))
        if  table[i][nvar+ncons+2] >=0  and ( k==-1 or  table[i][nvar+ncons+2] < table[k][nvar+ncons+2] ):
            k=i
    return k


def Main():
    inp = open('in2.txt')
    Z = np.array(list(map(float, inp.readline().split(' '))))
#    print(Z)
    N = Z.size
    Constraints = list()
    for inpline in inp:
        Constraints.append(list(map(float, inpline.split(' '))))
    Constraints= np.array(Constraints)
    M= len(Constraints)
    Header = GetHeader(N,M)
    Basic = GetBasic(N,M)
#    print("Basic = ",Basic)
    
    Table = GetTable(N,M,Z,Constraints)
#    PrintTable(N,M,Table,Header,Basic)

    NonBasic= GetNonBasic(N)
#    print(NonBasic)

    step= 1
    
    EnteringVarIndex= SelectEnteringVariableIndex(N,NonBasic,Table)
    while Table[0][NonBasic[EnteringVarIndex]] <= 0 :
# =============================================================================
#         if step >= 10 :
#             break
# =============================================================================
        print("###  Step no: ",step)
        print("BAsic ",Basic)
        print("Non basic",NonBasic)
        
        print(" Entering Variable ",NonBasic[EnteringVarIndex])
        CalculateIntercept(N,M,Table,Basic,NonBasic,EnteringVarIndex)
        PrintTable(N,M,Table,Header,Basic)
        LeavingVar= GetLeavingVar(N,M,Table)
        print('leaving var = ',Basic[LeavingVar])
        
        GaussJordan(M+1,N+M+2,Table,LeavingVar,NonBasic[EnteringVarIndex])
        for i in range(M+1):
            Table[i][N+M+2]=0
        
        print("After Gauss Jordan Elemination ")
        PrintTable(N,M,Table,Header,Basic)
        print()
        print()

        NonBasic[EnteringVarIndex], Basic [LeavingVar] =Basic [LeavingVar] ,NonBasic[EnteringVarIndex] 

        step= step+1
        EnteringVarIndex= SelectEnteringVariableIndex(N,NonBasic,Table)
    print('##########    SOLUTION    ##########')
    print("BAsic ",Basic)
    print("Non basic",NonBasic)
    PrintTable(N,M,Table,Header,Basic)
    
    print()
    print()
    
    for i in range(N):
        is_basic= False
        for j in range(1,M+1):
            if Basic[j]==i+1:
                is_basic= True
                break

        if is_basic :
            print('X'+str(i+1),' = %.2f'%(Table[j][-2]),sep='')
        else :
            print('X'+str(i+1),' = 0.0')
    
    print()
    print()
    print('Zmax = %.2f'%(Table[0][-2]))

    

if __name__ == '__main__':
    Main()
