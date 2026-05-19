from pprint import pprint
from collections.abc import Callable

import numpy as np
from numpy import log, sin, cos, abs, linalg, sqrt

MAX_S = 1e6
# MAX_S = 6

def f1(x, y):
    return 20 *  log(x - y) - x - y - 6

def f1x(x, y):
    return 20 / (x - y) - 1

def f1y(x, y):
    return -20 / (x - y) - 1



def f2(x, y):
    return 20 * sin(0.7 * (x - y)) + 7 * (x + y)

def f2x(x, y):
    return 14 * cos(0.7 * (x - y)) + 7

def f2y(x, y):
    return -14 * cos(0.7 * (x - y)) + 7



def find_root(start_value: tuple, criterion: Callable[[dict], bool]) -> dict:
    s = 0
    x, y = start_value
    A = np.array([
        [f1x(x, y), f1y(x, y)],
        [f2x(x, y), f2y(x, y)]
    ])


    F = np.array([f1(x, y), f2(x, y)])

    state = {
        "x": x, "y": y,
        "f1": F[0], "f2": F[1],
        "dx": np.inf, "dy": np.inf,
        "s": s
    }
    while criterion(state) and s < MAX_S:
        s += 1
        delta = linalg.solve(A, -F)

        x += delta[0]
        y += delta[1]

        F = np.array([f1(x, y), f2(x, y)])

        state = {
            "x": x, "y": y,
            "f1": F[0], "f2": F[1],
            "dx": delta[0], "dy": delta[1],
            "s": s
        }

    return state


def criterion_abs_f(state: dict) -> bool:
    return max(abs(state["f1"]), abs(state["f2"])) > EPS

def criterion_abs_d(state: dict) -> bool:
    return max(abs(state["dx"]), abs(state["dy"])) > EPS

def criterion_sqr_f(state: dict) -> bool:
    f1, f2 = state["f1"], state["f2"]
    return sqrt(f1**2 + f2**2) > EPS

def criterion_sqr_d(state: dict) -> bool:
    dx, dy = state["dx"], state["dy"]
    return sqrt(dx**2 + dy**2) > EPS

def criterion_rel_d(state: dict) -> bool:
    x, dx = state["x"], state["dx"]
    y, dy = state["y"], state["dy"]

    x_err = abs(dx / (x + dx))
    y_err = abs(dy / (y + dy))

    if np.isnan(x_err) or np.isnan(y_err):
        return True

    return max(x_err, y_err) > EPS

EPS = 1e-8
START_VALUE_1 = (-0.5, -1.7)
START_VALUE_2 = (-0.6, -1.8)
START_VALUE_3 = (-1, -2)



def run_test(start_value):
    x, y = start_value
    A = np.array([
        [f1x(x, y), f1y(x, y)],
        [f2x(x, y), f2y(x, y)]
    ])

    titles = ["x", "y", "f1", "f2", "dx", "dy", "s"]
    crit = [
        ("max(dx, dy) > eps", criterion_abs_d),
        ("max(f1, f2) > eps", criterion_abs_f),
        ("sqrt(dx^2 + dy^2) > eps", criterion_sqr_d),
        ("sqrt(f1^2 + f2^2) > eps", criterion_sqr_f),
        ("abs(dx / x^{s+1}) > eps", criterion_rel_d),
    ]
    sep_line = "=" * (len(titles) * (17 + 1) + 27 + 2)

    print(f"x0 = {start_value[0]}, y0 = {start_value[1]}")
    pprint(A)
    print(sep_line)
    print(f"|{"criterion":^27}|", end="")
    for t in titles:
        print(f"{t:^17}|", end="")
    print("\n" + sep_line)

    for c in crit:
        res = find_root(start_value, c[1])
        print(f"|{c[0]:^27}|", end="")
        for t in titles:
            if t == "s":
                print(f"{res[t]:^17}|", end="")
            else:
                print(f"{res[t]:^17e}|", end="")
        print()

    print(sep_line)


run_test(START_VALUE_1)
print("\n")
run_test(START_VALUE_2)
print("\n")
run_test(START_VALUE_3)
print("\n")

print("x0 - y0 > 0")
x = float(input("Введите x0: "))
y = float(input("Введите y0: "))
run_test((x, y))


