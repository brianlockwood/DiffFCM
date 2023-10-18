import sys
sys.path.append(r'./build/lib')
import mesh_python

import numpy as np

import math

def test_LinearFit():

    Xs = np.linspace(0, 1, 100)
    Ys = np.linspace(0, 1, 100)

    [X, Y] = np.meshgrid(Xs, Ys)

    def function(x, y):
        return x + y

    Z = mesh_python.fit2D(11, 11, 1, X, Y, function)

    error = 0.0
    for i in range(X.shape[0]):
        for j in range(X.shape[1]):
            error += math.pow(function(X[i,j], Y[i,j]) - Z[i,j],2)

    print(error)

    assert error < 1e-12

def test_QuadraticFit():

    Xs = np.linspace(0, 1, 100)
    Ys = np.linspace(0, 1, 100)

    [X, Y] = np.meshgrid(Xs, Ys)

    def function(x, y):
        return x*x + y*y

    Z = mesh_python.fit2D(11, 11, 2, X, Y, function)

    error = 0.0
    for i in range(X.shape[0]):
        for j in range(X.shape[1]):
            error += math.pow(function(X[i,j], Y[i,j]) - Z[i,j],2)

    print(error)

    assert error < 1e-12

def test_CubicFit():

    Xs = np.linspace(0, 1, 100)
    Ys = np.linspace(0, 1, 100)

    [X, Y] = np.meshgrid(Xs, Ys)

    def function(x, y):
        return x*x*x - y*y*y + x*y + 3*x*x*y + 6*x*y*y + 10

    Z = mesh_python.fit2D(11, 11, 3, X, Y, function)

    error = 0.0
    for i in range(X.shape[0]):
        for j in range(X.shape[1]):
            error += math.pow(function(X[i,j], Y[i,j]) - Z[i,j],2)

    print(error)

    assert error < 1e-12

def test_QuarticFit():

    Xs = np.linspace(0, 1, 100)
    Ys = np.linspace(0, 1, 100)

    [X, Y] = np.meshgrid(Xs, Ys)

    def function(x, y):
        return -3.0*math.pow(x,4) + 5.0*math.pow(y,4) + x*x*x - y*y*y + x*y + 3*x*x*y + 6*x*y*y + 10

    Z = mesh_python.fit2D(11, 11, 4, X, Y, function)

    error = 0.0
    for i in range(X.shape[0]):
        for j in range(X.shape[1]):
            error += math.pow(function(X[i,j], Y[i,j]) - Z[i,j],2)

    print(error)

    assert error < 1e-12
