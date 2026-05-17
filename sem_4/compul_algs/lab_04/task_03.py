import numpy as np
import matplotlib.pyplot as plt

def progonka(B, F):
    N = len(B) + 1

    B = [0] + B
    F = [0] + F

    delta_y = [0] * (N + 1)
    alpha = [0] * N
    beta = [0] * N

    # прямой ход
    for i in range(1, N):
        d = alpha[i - 1] + B[i]

        alpha[i] = -1 / d
        beta[i] = (F[i] + beta[i - 1]) / d

    # обратный ход
    for i in range(N - 1, 0, -1):
        delta_y[i] = alpha[i] * delta_y[i + 1] + beta[i]

    return delta_y[1:-1]


def f(x, y0, y1, y2, h):
    return y0 - 2 * y1 + y2 - y1**3 * h**2 - x**2 * h**2

def solve_b(y, h):
    return -2 - 3 * y**2 * h**2

def start_y_func(x):
    return 2 * x + 1

EPS = 1e-3
def criterion(y_values, delta_y):
    err = [np.abs(delta_y[i] / (y_values[i] + delta_y[i])) for i in range(len(y_values))]
    return max(err) > EPS

def solve_diff_eq(x_values):
    N = len(x_values) - 1
    y_values = [start_y_func(x) for x in x_values]

    B_values = []
    F_values = []
    for i in range(1, N):
        B_values.append(solve_b(y_values[i], step))
        F_values.append(-f(x_values[i], *y_values[i-1:i+2], step))

    delta_y = progonka(B_values, F_values)

    s = 0
    while criterion(y_values[1:-1], delta_y) and s < 100:
        s += 1
        for i in range(1, N):
            y_values[i] += delta_y[i - 1]

        for i in range(1, N):
            B_values[i - 1] = solve_b(y_values[i], step)
            F_values[i - 1] = -f(x_values[i], *y_values[i - 1:i + 2], step)

        delta_y = progonka(B_values, F_values)

    print(s)
    print("delta_y", delta_y)
    print("y_values", y_values)
    return y_values

N = 20

for N in range(2, 30):
    print(f"N: {N}; s: ", end="")
    step = 1 / N
    x_values = [step * i for i in range(N + 1)]
    y_values = solve_diff_eq(x_values)

# plt.plot(x_values, y_values)
# plt.legend()
# plt.show()
