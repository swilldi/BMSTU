# Метод прогонки для поиска значенич ci
def proaching_method(coef_values: list[dict[str,float]]):
    N = len(coef_values)

    # прямой проход: вычисление прогоночных коэфициентов alpha и beta
    alpha_values = [0 for _ in range(N + 1)]
    beta_values = [0 for _ in range(N + 1)]
    for i in range(2, N + 1):
        coef = coef_values[i - 1]
        a, b, d, f = coef["a"], coef["b"], coef["d"], coef["f"]

        alpha_values[i] = d / (b - a * alpha_values[i - 1])
        beta_values[i] = (f - a * beta_values[i - 1]) / (b - a * alpha_values[i - 1])

    # обратный проход: вычисление ci
    c_values = [0 for _ in range(N + 1)]
    for i in range(N - 1, 0, -1):
        c_values[i] = alpha_values[i] * c_values[i + 1] + beta_values[i]

    return c_values


def interval_indexes(values: list[float], target_value: float) -> tuple[int, int]:
    # if target_value <= values[0]:
    #     return 0, 1  # левый край
    # if target_value >= values[-1]:
    #     return len(values) - 2, len(values) - 1  # правый край
    for ind, value in enumerate(values):
        if value > target_value:
            return ind - 1, ind
    return len(values) - 2, len(values) - 1

def spline(table: list[tuple[float, float]], target_x: float) -> float:
    N = len(table)
    x_values = [value[0] for value in table]
    y_values = [value[1] for value in table]

    # поиск интервала в котором находиться target_x
    ind, _ = interval_indexes(x_values, target_x)

    # вычисление шагов
    h_values = [x_values[i + 1] - x_values[i] for i in range(N - 1)]


    # Формирование коэфициентов A, B, D, F для i = 1...N для метода прогонки
    proaching_coef_values: list[dict[str, float]] = list([{"a": 0.0, "b": -1, "d": 0.0, "f": 0.0}])
    for i in range(1, N - 1):
        cur_coef = {
            "a": h_values[i - 1],
            "b": 2 * (h_values[i - 1] + h_values[i]),
            "d": h_values[i],
            "f": 3 * ((y_values[i + 1] - y_values[i]) / h_values[i] - (y_values[i] - y_values[i - 1]) / h_values[i - 1])
        }
        proaching_coef_values.append(cur_coef)

    # Вычисление ci, i = 0...N+1
    c_values = proaching_method(proaching_coef_values)
    c_values[1] = 2
    # print("c: ", c_values)
    # print("h: ", h_values)


    a = y_values[ind]
    b =  (y_values[ind + 1] - y_values[ind]) / h_values[ind] - h_values[ind] * (c_values[ind + 1] + 2 * c_values[ind]) / 3
    c = c_values[ind]
    d = (c_values[ind + 1] - c_values[ind]) / (3 * h_values[ind])
    dx = target_x - x_values[ind]

    return a + b * dx + c * dx**2 + d * dx**3

def spline2D(table: list[tuple[float, float, float]], target_x: float, target_y: float) -> float:
    y_values = sorted({y for _, y, _ in table})
    u_values = []

    for fixed_y in y_values:
        xz_values = [(x, z) for x, y, z in table if y == fixed_y]
        u_values.append(spline(xz_values, target_x))

    z = spline(list(zip(y_values, u_values)), target_y)
    return z



