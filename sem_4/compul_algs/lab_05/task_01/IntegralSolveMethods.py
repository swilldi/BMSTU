import numpy as np

# N – число отрезков
def trapezoidal_integral(f, a, b, N):
    h = (b - a) / N
    I = (f(a) + f(b)) / 2

    x = a + h
    for _ in range(1, N):
        I += f(x)
        x += h

    I *= h
    return I

# N – число отрезков
def simpson_integral(f, a, b, N):
    if N % 2 != 0:
        print("N нечетное")
        return None

    h = (b - a) / N
    x_values = [a + i * h for i in range(0, N + 1)]
    I = 0

    for i in range(0, N // 2):
        I += f(x_values[2 * i]) + 4 * f(x_values[2 * i + 1]) + f(x_values[2 * i + 2])

    I *= h / 3
    return I

# N – число отрезков
def gauss3_integral(f, a, b, N):
    A = (5/9, 8/9, 5/9)
    t = (-np.sqrt(3/5), 0, np.sqrt(3/5))

    for i in
    half_ba_sum = (b + a) / 2
    half_ba_diff = (b - a) / 2
    I = 0
    for i in range(3):
        x = half_ba_diff * t[i] + half_ba_sum
        I += A[i] * f(x)

    I *= half_ba_diff
    return I

