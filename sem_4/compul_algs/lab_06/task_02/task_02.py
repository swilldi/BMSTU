import numpy
from matplotlib import pyplot as plt

alpha = float(input("Введите альфа: "))
beta = float(input("Введите бета: "))
gamma = float(input("Введите гамма: "))

N = 10
h = 1 / N
x = [i * h for i in range(N + 1)]

A = [0] * (N + 1)
B = [0] * (N + 1)
C = [0] * (N + 1)
F = [0] * (N + 1)
for i in range(N + 1):
    A[i] = 1 + h * x[i]**2
    B[i] = 4 * h * h - 2
    C[i] = 1 - h * x[i]**2
    F[i] = h**2 * (2 * x[i] + numpy.exp(-x[i]))

e = [-2 / (4 * h**2 - 2)] + [0] * N
n = [(h**2 + 2 * h * alpha) / (4 * h**2 - 2)] + [0] * N
for i in range(1, N):
    e[i] = -C[i] / (A[i] * e[i - 1] + B[i])
    n[i] = (F[i] - A[i] * n[i - 1]) / (A[i] * e[i - 1] + B[i])

u = [0] * N + [(F[N] - 2 * C[N] * h * gamma - 2 * n[N - 1]) / (2 * e[N - 1] + B[N] + 2 * h * beta * C[N])]
for i in range(N - 1, -1, -1):
    u[i] = e[i] * u[i + 1] + n[i]



plt.plot(x, u, label='u(x)')
plt.grid(True)
plt.legend()
plt.show()