from GaussIntegral import gauss_integral
from SimpsonIntegral import simpson_integral
from interpolation import newton_polynomial2D
from reader import read_data

EPS = 1e-5
DEGREE = 3

# alpha = float(input())
# beta = float(input())
# a = float(input())
# b = float(input())
alpha = 1
beta = 4
a = 0
b = 2

I_data = read_data()
f = lambda x, y: newton_polynomial2D(I_data, x, y, 2)

phi = lambda x: alpha * x**2
psi = lambda x: beta * x**2


# print(f"α={alpha}, β={beta}, a={a}, b={b}, eps={EPS}")
# print(f"Область: x∈[{a}, {b}],  y∈[{alpha}·x², {beta}·x²]")
# print(f"Внутренний интеграл: Симпсон, eps={EPS}")
# print(f"Внешний интеграл:    Гаусс,   degree={DEGREE}, eps={EPS}")
# print("-" * 50)

F_simpson = lambda x: simpson_integral(lambda y: f(x, y), phi(x), psi(x), EPS)
I = gauss_integral(F_simpson, a, b, DEGREE, EPS, verbose=True)
I = simpson_integral(F_simpson, a, b, EPS, verbose=True)

N_values = [2, 4, 16, 64, 1024, 4096]
gauss_degrees = [2, 3, 4, 5]


# print("-" * 50)
# print(f"I = {I:.8f}")
