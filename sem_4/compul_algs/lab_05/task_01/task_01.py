from IntegralSolveMethods import *

f1 = lambda x: abs(x)
f2 = lambda x: abs(x) ** 2
a, b = -1, 1
N_values = [2, 3, 4, 5, 6, 10, 11, 50, 100, 101]

cases = [
    ("k = 1   f(x) = |x|",  f1, 1.0),
    ("k = 2   f(x) = x^2",  f2, 2/3),
]

def rel_error(exact, approx):
    return abs(exact - approx) / abs(exact) * 100

def fmt_err(delta):
    # if delta == 0:
    #     return "точно"
    if delta < 1e-10:
        return "0%"
    if delta < 1e-4:
        return f"{delta:.2e} %"
    if delta < 1.0:
        return f"{delta:.4f} %"
    return f"{delta:.2f} %"

W = 26   # ширина колонки

for title, f, exact in cases:
    print("=" * 86)
    print(f"{title}        точное значение = {exact:.10f}")
    print("=" * 86)
    print(f"{'N':>4} | {'трапеции':^{W}} | {'Симпсон':^{W}} | {'Гаусс-3':^{W}}")
    print("-" * 86)

    for N in N_values:
        I_t = trapezoidal_integral(f, a, b, N)
        I_g = gauss3_integral(f, a, b)
        e_t = fmt_err(rel_error(exact, I_t))
        e_g = fmt_err(rel_error(exact, I_g))

        if N % 2 == 0:
            I_s = simpson_integral(f, a, b, N)
            s_val = f"{I_s:.12f}"
            s_err = f"({fmt_err(rel_error(exact, I_s))})"
        else:
            s_val, s_err = "—", ""

        # строка значений
        print(f"{N:>4} | {I_t:>{W}.12f} | {s_val:>{W}} | {I_g:>{W}.12f}")
        # строка погрешностей под значениями
        print(f"{'':>4} | {'('+e_t+')':>{W}} | {s_err:>{W}} | {'('+e_g+')':>{W}}")
        print("-" * 86)  # пустая строка-разделитель
    print()
