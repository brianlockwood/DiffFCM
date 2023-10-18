import sys
sys.path.append(r'./build/lib')
import mesh_python

import numpy as np

import matplotlib.pyplot as plt

import math

Xs = np.linspace(0, 1, 100)
Ys = np.linspace(0, 1, 100)

[X, Y] = np.meshgrid(Xs, Ys)

def function(x, y):
    # return x + y
    return -3.0*math.pow(x,4) + 5.0*math.pow(y,4) + x*x*x - y*y*y + x*y + 3*x*x*y + 6*x*y*y + 10

Z = mesh_python.fit2D(11, 11, 4, X, Y, function)

Zexact = np.zeros_like(X)
for i in range(X.shape[0]):
    for j in range(X.shape[1]):
        Zexact[i,j] = function(X[i,j], Y[i,j])

fig = plt.figure()
ax = plt.axes(projection='3d')

ax.contour3D(X,Y,Z, 50)
#ax.contour3D(X,Y,Zexact, 50)
plt.show()