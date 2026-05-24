import numpy as np

def simpson_integral(f, a, b, eps):
    # N – кол-во интервалов
    def solve(N):
        h = (b - a) / N
        x_values = [a + i * h for i in range(N + 1)]

        I = 0
        print(f"x_values: {x_values}")
        for i in range(N // 2):
            I += f(x_values[2 * i]) + 4 * f(x_values[2 * i + 1]) + f(x_values[2 * i + 2])

        I *= h / 3
        return I

    N = 2
    I_N = solve(N)
    N *= 2
    I_2N = solve(N)
    while abs(I_N - I_2N) > eps * abs(I_2N):
        I_N = I_2N

        N *= 2
        I_2N = solve(N)

    return I_2N


print(simpson_integral(np.sin, -1, 1, 2))
