# -*- coding: utf-8 -*-
"""
Created on Sat Jul 13 00:25:40 2019

@author: MAHDI
"""
import sys
import numpy as np


def PrintSqMatrix(a, n):
    for i in range(n):
        for j in range(n-1):
            print("%.4f" % (a[i][j]), end=' ')
        print("%.4f" % (a[i][n-1]))
    return

 
def PrintColumnMatrix(mat, n):
    for i in range(n):
        print("%.4f" % (mat[i]))
    return


def DecomposeLU(a, n):
    n=int(n)
    l = np.eye(n)
    u = np.array(a)
#    print('l += ' ,l,a )
#    print(a[0][0])
    for k in range(n):
        for i in range(k+1, n):
# =============================================================================
#             if np.abs(u[k][k])<=1e-10:
#                 return 0
# =============================================================================
            factor = u[i][k]/u[k][k]
            l[i][k] = factor
            for j in range(n):
                u[i][j] = u[i][j]-factor*u[k][j]
# =============================================================================
#     print(l)
#     print(u)
#     print(a)
#
# =============================================================================
    return (l, u)


def Forwardsubstitution(l, b, n):
    y = np.zeros(n)
# =============================================================================
#     print(y)
#     print(b)
# =============================================================================
    for i in range(n):
        sum = 0.0
        for j in range(0, i):
            sum += l[i][j]*y[j]
        y[i] = (b[i]-sum)/l[i][i]
    return y


def Backwardsubstitution(u, y, n):
    x = np.zeros(n)
# =============================================================================
#     print(y)
#     print(b)
# =============================================================================
    for i in range(n-1, -1, -1):
        sum = 0.0
        for j in range(i+1, n):
            sum += u[i][j]*x[j]
        x[i] = (y[i]-sum)/u[i][i]
    return x


def Nosolution():
    print("No unique solution")
    return


def CheckSolution(u, n):
    for i in range(n):
        non_zero=False
        for j in range(n):
            if abs(u[i][j]) >= 1e-12:
                non_zero=True
                break
        if non_zero == False :
            return False
    for i in range(n):
        if abs(u[i][i])<=1e-12:
            return False
    return True


def Main():
    inp = open('in1.txt')
    sys.stdout = open('out1.txt', 'w')
    N = int(inp.readline())
#    print(n)
    A = [list(map(float, inp.readline().strip().split(' '))) for i in range(N)]
    A = np.array(A)
    B = [float(inp.readline()) for i in range(N)]
    B = np.array(B)

# =============================================================================
#     print(A)
#     print(b)
# =============================================================================

    # input taken

    L, U = DecomposeLU(A, N)
    PrintSqMatrix(L, N)
    print()
    PrintSqMatrix(U, N)
    print()

    if CheckSolution(U, N) is False:
        Nosolution()
        return

#    print('shape of b',b.shape)
    Y = Forwardsubstitution(L, B, N)
    PrintColumnMatrix(Y, N)
    print()
    X = Backwardsubstitution(U, Y, N)
    PrintColumnMatrix(X, N)
    return


if '__main__' == __name__:
    Main()