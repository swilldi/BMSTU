from math import ceil


def index_point(table: list[tuple[float, float]], target_x: float) -> int:
    ind = 0

    # поиск первого числа больше target_x
    while ind + 1 < len(table) and table[ind][0] < target_x:
        ind += 1

    # проверка наибольшего числа, которое меньше target_x
    if ind > 0:
        cur_diff = abs(table[ind][0] - target_x)
        prev_diff = abs(table[ind - 1][0] - target_x)
        if prev_diff < cur_diff:
            ind -= 1

    return ind


def environment_of_point(
    table: list[tuple[float, float]], target_x: float, points_count: int
) -> list[tuple[float, float]]:
    central_index = index_point(table, target_x)

    start_ind = central_index - points_count // 2
    end_ind = central_index + ceil(points_count / 2)

    if start_ind < 0:
        end_ind += -start_ind
        start_ind = 0

    if end_ind > len(table):
        start_ind -= end_ind - len(table)
        end_ind = len(table)

    start_ind = max(start_ind, 0)
    return table[start_ind:end_ind]


def divided_difference(x1: float, x2: float, y1: float, y2: float) -> float:
    return (y1 - y2) / (x1 - x2)


def newton_polynomial(
    table: list[tuple[float, float]], target_x: float, degree: int
) -> float:
    degree = min(degree, len(table) - 1)
    env = environment_of_point(table, target_x, degree + 1)
    coef = [env[0][1]]

    y_values = [y for _, y in env]
    for i in range(degree, 0, -1):
        x_ind_shift = degree + 1 - i
        for j in range(i):
            x1, x2 = env[j][0], env[j + x_ind_shift][0]
            y1, y2 = y_values[j], y_values[j + 1]
            y_values[j] = divided_difference(x1, x2, y1, y2)
        coef.append(y_values[0])

    x = 1.0
    y = 0.0
    for i in range(len(env)):
        y += coef[i] * x
        x *= target_x - env[i][0]

    return y


def newton_polynomial2D(
    table: list[tuple[float, float, float]], target_x: float, target_y: float, degree: int
) -> float:
    x_values = []
    for x, _, _ in table:
        if x not in x_values:
            x_values.append(x)

    xv_values = []
    for cur_x in x_values:
        yz_values = [(y, z) for x, y, z in table if x == cur_x]
        y_degree = min(degree, len(yz_values) - 1)
        xv_values.append((cur_x, newton_polynomial(yz_values, target_y, y_degree)))

    x_degree = min(degree, len(xv_values) - 1)
    return newton_polynomial(xv_values, target_x, x_degree)
