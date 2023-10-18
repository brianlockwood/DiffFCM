import sys
sys.path.append(r'./build/lib')
import bspline_python as basis

import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-1.0, 1.0, 100)

y = np.zeros_like(x)

p = 9
n = p + 1

for j in range(n):
    for i in range(x.size):
        y[i] = basis.eval(p, j, x[i])

#    print(y)

    plt.plot(x,y)
    plt.show()