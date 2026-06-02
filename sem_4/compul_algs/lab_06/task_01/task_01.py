def left_diff_proizv(y_n_minus, y_n, h):
    return (y_n - y_n_minus) / h

def right_diff_proizv(y_n, y_n_plus, h):
    return (y_n_plus - y_n) / h

def central_diff_proizv(y_n_minus, y_n_plus, h):
    return (y_n_plus - y_n_minus) / h


def second_runge_left_diff_proizv(y_n_minus2, y_n_minus1, y_n, h):
    dh = left_diff_proizv(y_n_minus1, y_n, h)
    d2h = left_diff_proizv(y_n_minus2, y_n, 2 * h)
    return 2 * dh - d2h

def second_runge_right_diff_proizv(y_n, y_n_plus1, y_n_plus2,  h):
    dh = right_diff_proizv(y_n, y_n_plus1, h)
    d2h = right_diff_proizv(y_n, y_n_plus2, 2 * h)
    return 2 * dh - d2h


def second_diff_proizv(y_n_minus, y_n, y_n_plus, h):
    return (y_n_minus - 2 * y_n + y_n_plus) / h**2


x_values = [1,     2,     3,     4,     5,     6    ]
y_values = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]


# Разностные производные
res_diff_proizv = [None] * len(x_values)
for i in range(len(x_values)):
    if i == 0:
        res_diff_proizv[i] = (y_values[i + 1] - y_values[i]) / (x_values[i + 1] - x_values[i])
    else:
        res_diff_proizv[i] = (y_values[i] - y_values[i - 1]) / (x_values[i] - x_values[i - 1])


# Центральные разностные производные
res_central_diff_proizv = [None] * len(x_values)
for i in range(1, len(x_values) - 1):
    res_central_diff_proizv[i] = central_diff_proizv(y_values[i - 1], y_values[i + 1], x_values[i + 1] - x_values[i - 1])

# 2-я формула рунге
res_second_runge_diff_proizv = [None] * len(x_values)
for i in range(len(x_values)):
    if i <= len(x_values) - 3:
        h = x_values[i+1] - x_values[i]
        res_second_runge_diff_proizv[i] = second_runge_right_diff_proizv(y_values[i], y_values[i+1], y_values[i+2], h)
    else:
        h = x_values[i] - x_values[i-1]
        res_second_runge_diff_proizv[i] = second_runge_left_diff_proizv(y_values[i-2], y_values[i-1], y_values[i], h)

# Замена переменных
res_dir_vars_proizv = []
e = [1 / x for x in x_values]
n = [1 / y for y in y_values]
k_values = [0] * len(n)
for i in range(len(x_values) - 1):
    k_values[i] = (n[i + 1] - n[i]) / (e[i + 1] - e[i])
k_values[-1] = (n[-1] - n[-2]) / (e[-1] - e[-2])
for (x, y, k) in zip(x_values, y_values, k_values):
    res_dir_vars_proizv.append(k * y**2 / x**2)

res_2_diff_proizv = [None] * len(x_values)
for i in range(1, len(x_values) - 1):
    res_2_diff_proizv[i] = second_diff_proizv(y_values[i - 1], y_values[i], y_values[i + 1], x_values[i] - x_values[i - 1])

def result_str(value):
    if value is None:
        return "–––"
    else:
        return value

separator_line = "=" * 65
separator_line_tonkay = "-" * len(separator_line)
print(separator_line)
print(f"|{"x":^5}|{"y":^7}|{"Diff":^7}|{"Center":^8}|{"2-Runge":^9}|{"dir.vars":^10}||{"2 diff":^10}|")
print(separator_line_tonkay)
for i in range(len(x_values)):
    print(f"|{x_values[i]:^5}|"
          f"{y_values[i]:^7}|"
          f"{result_str(res_diff_proizv[i]):^7.3}|"
          f"{result_str(res_central_diff_proizv[i]):^8.3}|"
          f"{result_str(res_second_runge_diff_proizv[i]):^9.3}|"
          f"{result_str(res_dir_vars_proizv[i]):^10.3}||"
          f"{result_str(res_2_diff_proizv[i]):^10.3}|"
          f"")

print(separator_line)