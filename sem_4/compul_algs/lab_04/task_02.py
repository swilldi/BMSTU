from collections.abc import Callable

import numpy as np


def mid_integral(a, b, f: Callable[[float], float]) -> float:
    def solve(n):
        step = (b - a) / n
        x = a + step / 2
        res = 0
        while x < b:
            # print(res, f(x), (x - a) // step)
            res += f(x)
            x += step

        res *= step
        return res

    N = 2
    res_N = solve(N)
    res_twoN = solve(2 * N)
    # print(res_N, N)
    # print(res_twoN, 2 * N)
    while abs(res_N - res_twoN) > 1e-8:
        N *= 2
        res_N = res_twoN
        res_twoN = solve(2 * N)
        # print(res_twoN, 2 * N)

    return res_twoN


# print(mid_integral(0, 10, np.sin))

EPS = 1e-8
def f(x):
    return 2 / np.sqrt(2 * np.pi) * mid_integral(0, x, lambda t: np.exp(-(t**2) / 2))

def dehodomia(F, a, b) -> float:
    fa = f(a) - F
    fb = f(b) - F
    if fa * fb > 0:
        return np.nan

    c = a + (b - a) / 2
    fc = f(c) - F

    while (abs(c) > 1e-10 and abs((b - a) / c) > EPS) or (abs(c) <= 1e-10 and abs(b - a) > EPS):
        if fa * fc <= 0:
            b = c
        else:
            a = c
            fa = fc

        c = a + (b - a) / 2
        fc = f(c) - F

    return c


#  TODO добавить тесты
