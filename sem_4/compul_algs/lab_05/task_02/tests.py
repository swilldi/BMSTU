from GaussIntegral import gauss_integral_by_N, gauss_integral
from SimpsonIntegral import simpson_integral_by_N, simpson_integral
from interpolation import newton_polynomial2D
from reader import read_data

alpha, beta, a, b = 1, 4, 0, 2
EPS = 1e-5

I_data = read_data()
f = lambda x, y: newton_polynomial2D(I_data, x, y, 2)
phi = lambda x: alpha * x**2
psi = lambda x: beta * x**2


def compute(outer, inner, N_outer, N_inner, deg_outer=3, deg_inner=3):
    """outer/inner ∈ {'G', 'S'} — Гаусс или Симпсон."""
    if inner == "G":
        F = lambda x: gauss_integral_by_N(lambda y: f(x, y), phi(x), psi(x), deg_inner, N_inner)
    else:
        F = lambda x: simpson_integral_by_N(lambda y: f(x, y), phi(x), psi(x), N_inner)

    if outer == "G":
        return gauss_integral_by_N(F, a, b, deg_outer, N_outer)
    return simpson_integral_by_N(F, a, b, N_outer)


F_simpson_auto = lambda x: simpson_integral(lambda y: f(x, y), phi(x), psi(x), EPS)
I_ref = gauss_integral(F_simpson_auto, a, b, 3, EPS)
print(f"Эталон (автошаг, Гаусс[deg=3]/Симпсон, eps={EPS}):")
print(f"    I_ref = {I_ref:.8f}")
print()
print("Замечание о смысле N в таблицах:")
print("  для Симпсона  N = количество УЗЛОВ сетки (нечётное ≥3)")
print("  для Гаусса    N = количество ПОДЫНТЕРВАЛОВ, каждый с degree=3 узлами")
print()


# === Таблица 1. Сравнение 4 методов по N ===
# Outer-Inner: G-G, G-S, S-G, S-S, Gauss degree = 3 для обоих направлений
# N - нечётные, чтобы Симпсон работал (N узлов ⇒ N-1 интервалов, чётное)
N_values = [3, 5, 9, 17, 33, 65]

# Считаем один раз, переиспользуем для всех трёх таблиц
results = {}
for N in N_values:
    results[N] = {
        "G-G": compute("G", "G", N, N),
        "G-S": compute("G", "S", N, N),
        "S-G": compute("S", "G", N, N),
        "S-S": compute("S", "S", N, N),
    }

methods = ["G-G", "G-S", "S-G", "S-S"]

print("=" * 78)
print("Таблица 1а.  Значения интеграла,  N_outer = N_inner = N,  Gauss degree = 3")
print(f"{'N':>5} | " + " | ".join(f"{m:>13}" for m in methods))
print("-" * 78)
for N in N_values:
    print(f"{N:>5} | " + " | ".join(f"{results[N][m]:>13.8f}" for m in methods))
print(f"{'ref':>5} | " + " | ".join(f"{I_ref:>13.8f}" for _ in methods))
print()

print("=" * 78)
print("Таблица 1б.  Абсолютная погрешность |I − I_ref|")
print(f"{'N':>5} | " + " | ".join(f"{m:>13}" for m in methods))
print("-" * 78)
for N in N_values:
    print(f"{N:>5} | " + " | ".join(f"{abs(results[N][m] - I_ref):>13.2e}" for m in methods))
print()

print("=" * 78)
print("Таблица 1в.  Относительная погрешность |I − I_ref| / |I_ref|")
print(f"{'N':>5} | " + " | ".join(f"{m:>13}" for m in methods))
print("-" * 78)
for N in N_values:
    print(f"{N:>5} | " + " | ".join(
        f"{abs(results[N][m] - I_ref) / abs(I_ref):>13.2e}" for m in methods))
print()


# === Таблица 2. Влияние степени Гаусса (G-G, фиксированный N) ===
N_fix = 9
gauss_degrees = [2, 3, 4, 5]
print("=" * 78)
print(f"Таблица 2.  Метод G-G, N_outer = N_inner = {N_fix}, varying degree")
print(f"{'deg':>5} | {'I':>13} | {'|I - I_ref|':>14}")
print("-" * 40)
for deg in gauss_degrees:
    I_GG = compute("G", "G", N_fix, N_fix, deg, deg)
    print(f"{deg:>5} | {I_GG:>13.8f} | {abs(I_GG - I_ref):>14.2e}")
print()


# === Таблицы 3-6. Перекрёстные N_outer × N_inner для каждого метода ===
def print_cross_table(label, outer, inner, N_values, deg_outer=3, deg_inner=3):
    print("=" * 78)
    print(f"{label}  (N_outer × N_inner)")
    header = f"{'N_o\\N_i':>10} |" + "".join(f" {n:>11}" for n in N_values)
    print(header)
    print("-" * len(header))
    for N_o in N_values:
        row = [compute(outer, inner, N_o, N_i, deg_outer, deg_inner) for N_i in N_values]
        print(f"{N_o:>10} |" + "".join(f" {v:>11.6f}" for v in row))
    print(f"{'ref':>10} |" + "".join(f" {I_ref:>11.6f}" for _ in N_values))
    print()


print_cross_table("Таблица 3.  Метод G-G (Гаусс deg=3 / Гаусс deg=3)", "G", "G", N_values)
print_cross_table("Таблица 4.  Метод G-S (Гаусс deg=3 / Симпсон)",   "G", "S", N_values)
print_cross_table("Таблица 5.  Метод S-G (Симпсон / Гаусс deg=3)",   "S", "G", N_values)
print_cross_table("Таблица 6.  Метод S-S (Симпсон / Симпсон)",       "S", "S", N_values)
