from collections.abc import Callable

import numpy as np


def mid_integral(a, b, f: Callable[[float], float]) -> tuple[float, int]:
    def solve(n):
        step = (b - a) / n
        x = a + step / 2
        res = 0
        while x < b:
            print(res, f(x), (x - a) // step)
            res += f(x)
            x += step

        res *= step
        return res

    N = 2
    res_N = solve(N)
    res_twoN = solve(2 * N)
    print(res_N, N)
    print(res_twoN, 2 * N)
    while abs(res_N - res_twoN) > 1e-8:
        N *= 2
        res_N = res_twoN
        res_twoN = solve(2 * N)
        print(res_twoN, 2 * N)

    return res_twoN, 2 * N


print(mid_integral(0, 10, np.sin))

