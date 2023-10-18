import sys
sys.path.append(r'./build/lib')
import gauss_quadrature_python

print(gauss_quadrature_python.integrate1D(5))
print(gauss_quadrature_python.integrate2D(5))
print(gauss_quadrature_python.integrate3D(5))