import numpy as np
from GaussIntegral import gauss_integral
from SimpsonIntegral import simpson_integral
from interpolation import newton_polynomial2D
from reader import read_data

EPS = 1e-5

I_data = read_data()
f = lambda x, y: newton_polynomial2D(I_data, x, y, 2)

phi = lambda x: alpha * x**2
psi = lambda x: beta * x**2
F_simpson = lambda x: simpson_integral(lambda y: f(x, y), phi(x), psi(x), EPS)
F_gauss = lambda x: gauss_integral(lambda y: f(x, y), phi(x), psi(x), 3, EPS)

# alpha = float(input())
# beta = float(input())
# a = float(input())
# b = float(input())

alpha = 1
beta = 4
a = 0
b = 2

# print(simpson_integral(F_simpson, a, b, EPS))
print(gauss_integral(F_simpson, a, b, 3, EPS))
