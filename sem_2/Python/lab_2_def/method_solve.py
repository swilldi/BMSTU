import sympy as sm

def find_root(str_func, a, b, eps):
    # str_func = "sin(x)"
    # a = -1
    # b = 1
    # eps = 1e-4

    x_symbol = sm.symbols("x")
    func = sm.simplify(str_func)
    func_d1 = func.diff(x_symbol)
    func_d2 = func_d1.diff(x_symbol)

    f = lambda x: func.subs(x_symbol, x)
    f_d1 = lambda x: func_d1.subs(x_symbol, x)
    f_d2 = lambda x: func_d2.subs(x_symbol, x)

    if f(a) * f_d2(a) > 0:
        x = a
    else:
        x = b

    while abs(f(x) / f_d1(x)) > eps:
        x = x - f(x) / f_d1(x)

    print(x.evalf())