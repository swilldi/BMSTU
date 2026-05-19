from collections.abc import Callable
import numpy as np

EPS1 = 1e-5
EPS2 = 1e-5
EPS = 1e-5

def mid_integral(a, b, f: Callable[[float], float]) -> float:
    def solve(n):
        step = (b - a) / n
        x = a + step / 2
        res = 0
        for _ in range(n):
            # print(res, f(x), (x - a) // step)
            res += f(x) * step
            x += step

        # res *= step
        return res

    N = 2
    res_N = solve(N)
    res_twoN = solve(2 * N)
    # print(res_N, N)
    # print(res_twoN, 2 * N)
    s = 0
    while abs(res_N - res_twoN) > abs(res_N) * EPS1 + EPS2:
        s += 1
        N *= 2
        res_N = res_twoN
        res_twoN = solve(2 * N)
        # print(res_twoN, 2 * N)
    # print(f"a: {a}, b: {b}, s: {s}")

    return res_twoN


def f(x):
    return 2 / np.sqrt(2 * np.pi) * mid_integral(0, x, lambda t: np.exp(-(t**2) / 2))

def dehodomia(F) -> float:
    # Начальные органичения поиска корня
    a = 0
    b = 10

    c = a + (b - a) / 2

    fc = f(c) - F
    fa = f(a) - F
    while abs(b - a) > EPS * max(1, abs(c)):
        if fa * fc < 0:
            b = c
        else:
            a = c
            fa = fc

        c = a + (b - a) / 2
        fc = f(c) - F

    return c

# print(mid_integral(0, 10, np.sin))
test_case = [
    (0.1, 0.12566135),
    (0.25, 0.31863936),
    (0.5, 0.67448975),
    (0.6827, 1.0),
    (0.9545, 2.0),
    (0.9973, 3.0),
    (0.9999, 3.89059189)
]

for F, result in test_case:
    cur_result = dehodomia(F)
    print(f"dehodomia = {cur_result}, correct_result = {result} – (отн.ошибка: {abs(cur_result - result) / result:e}, абс.ошибка: {abs(cur_result - result):e})")

F = float(input("Введите значение функции: "))
print("x = ", dehodomia(F))
