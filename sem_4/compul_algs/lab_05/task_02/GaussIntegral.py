import numpy as np
LEGANDRO_LEFT, LEGANDRO_RIGHT = -1, 1

EPS = 1e-6

def polynom_legandro(t, n):
    if n == 0:
        return 1
    if n == 1:
        return t

    l = 0
    l_prev = t
    l_prev_prev = 1
    for i in range(2, n + 1):
        l = 1 / i * ((2 * i - 1) * t * l_prev - (i - 1) * l_prev_prev)
        l_prev_prev = l_prev
        l_prev = l

    return l

def get_legandro_intervals_with_roots(degree):
    N = degree + 1
    if N % 2 != 0:
        N += 1

    h = (LEGANDRO_RIGHT - LEGANDRO_LEFT) / (N - 1)
    x_values = [LEGANDRO_LEFT + i * h for i in range(N)]

    sign_change_intervals = []
    while len(sign_change_intervals) != degree:
        sign_change_intervals.clear()
        for x1, x2 in zip(x_values[:-1], x_values[1:]):
            if polynom_legandro(x1, degree) * polynom_legandro(x2, degree) <= 0:
                sign_change_intervals.append((x1, x2))

        N *= 2
        h = (LEGANDRO_RIGHT - LEGANDRO_LEFT) / (N - 1)
        x_values = [LEGANDRO_LEFT + i * h for i in range(N)]

    return sign_change_intervals

def find_root_dihodomia(f, a, b):
    c = (b + a) / 2

    fa = f(a)
    fc = f(c)

    while abs(b - a) > EPS * max(1, abs(c)):
        if fa * fc < 0:
            b = c
        else:
            a = c
            fa = fc

        c = (b + a) / 2
        fc = f(c)

    return c


def gauss_integral(f, a, b, degree, eps, verbose=False):
    sign_change_intervals = get_legandro_intervals_with_roots(degree)
    roots = [find_root_dihodomia(lambda t: polynom_legandro(t, degree), *interval) for interval in
             sign_change_intervals]

    # Матрица корней в степенях от 0 до N - 1
    T = [[r ** k for r in roots] for k in range(degree)]
    F = [2 / (k + 1) if k % 2 == 0 else 0 for k in range(degree)]
    # Решение матричного уравнения для получения весовых коэф-ов
    A = np.linalg.solve(T, F)

    if verbose:
        print(f"[gauss] a={a}, b={b}, degree={degree}, eps={eps}")
        print(f"[gauss] корни P_{degree}: {[round(r, 6) for r in roots]}")
        print(f"[gauss] веса:        {[round(float(ai), 6) for ai in A]}")

    def solve(N):
        h = (b - a) / N
        I = 0
        for i in range(N):
            x0, x1 = a + h * i, a + h * (i + 1)
            convert_to_x = lambda t: (x1 - x0) / 2 * t + (x1 + x0) / 2
            I += (x1 - x0) / 2 * sum([Ai * f(convert_to_x(t)) for t, Ai in zip(roots, A)])

        return I


    N = 2
    I_N = solve(N)
    if verbose:
        print(f"[gauss] N={N:>4}  I={I_N:.8f}")
    N *= 2
    I_2N = solve(N)
    if verbose:
        print(f"[gauss] N={N:>4}  I={I_2N:.8f}")
    while abs(I_N - I_2N) > eps * abs(I_2N):
        I_N = I_2N

        N *= 2
        I_2N = solve(N)
        if verbose:
            print(f"[gauss] N={N:>4}  I={I_2N:.8f}")

    if verbose:
        print(f"[gauss] сошлось при N={N}")
    return I_2N