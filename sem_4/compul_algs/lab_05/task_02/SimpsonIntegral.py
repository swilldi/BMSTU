def simpson_integral(f, a, b, eps, verbose=False):
    # N – кол-во интервалов
    def solve(N):
        h = (b - a) / N
        x_values = [a + i * h for i in range(N + 1)]

        I = 0
        for i in range(N // 2):
            I += f(x_values[2 * i]) + 4 * f(x_values[2 * i + 1]) + f(x_values[2 * i + 2])

        I *= h / 3
        return I

    if verbose:
        print(f"[simpson] a={a}, b={b}, eps={eps}")

    N = 2
    I_N = solve(N)
    if verbose:
        print(f"[simpson] N={N:>4}  I={I_N:.8f}")
    N *= 2
    I_2N = solve(N)
    if verbose:
        print(f"[simpson] N={N:>4}  I={I_2N:.8f}")
    while abs(I_N - I_2N) > eps * abs(I_2N):
        I_N = I_2N

        N *= 2
        I_2N = solve(N)
        if verbose:
            print(f"[simpson] N={N:>4}  I={I_2N:.8f}")

    if verbose:
        print(f"[simpson] сошлось при N={N}")
    return I_2N
