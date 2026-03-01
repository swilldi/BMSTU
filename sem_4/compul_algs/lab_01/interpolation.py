from math import ceil

def index_point(table: list[tuple[float, float]], target_x: float) -> int:
    ind = 0
    diff = table[0][0] - target_x

    # поиск первого числа больше target_x
    while diff < 0:
        ind += 1
        diff = table[ind][0] - target_x

    # проверка предыдущего значени
    if ind > 0:
        prev_diff = abs(table[ind - 1][0] - target_x)
        if prev_diff < diff:
            ind -= 1

    return ind

def environment_of_point(table: list[tuple[float, float]], target_x: float, n: int) -> list[tuple[float, float]]:
    central_index = index_point(table, target_x)

    start_ind = central_index - n // 2
    end_ind = central_index + ceil(n / 2)

    if start_ind < 0:
        end_ind += abs(start_ind)
        start_ind = 0
    elif end_ind >= len(table):
        start_ind -= end_ind - len(table)
        end_ind = len(table)

    return table[start_ind:end_ind]

def divided_difference(x1, x2, y1, y2):
    return (y1 - y2) / (x1 - x2)


def newton_polynomial(table: list[tuple[float, float]], target_x: float, n: int) -> float:
    '''
    :param table: (x, y)
    :param target_x:
    :param n: степень полина
    :return: значение функции в точке x
    '''

    # вычисление коэфициентов
    env = environment_of_point(table, target_x, n + 1)
    coef = [env[0][1]]

    y_values = [y for x, y in env]
    for i in range(n, 0, -1):
        x_ind_shift = n + 1 - i
        for j in range(i):
            x1, x2 = env[j][0], env[j + x_ind_shift][0]
            y1, y2 = y_values[j], y_values[j + 1]
            y_values[j] = divided_difference(x1, x2, y1, y2)
        coef.append(y_values[0])
        print(f"[{i}] -> {y_values[:i]}")

    # Вычисление полинома
    x, y = 1, 0
    for i in range(len(env)):
        y += coef[i] * x
        x *= (target_x - env[i][0])

    return y

def newton_polynomial2D(table: list[tuple[float, float, float]], target_x: float, target_y: float, n: int) -> float:
    '''

    :param table: (x, y, z)
    :param target_x:
    :param target_y:
    :param n:
    :return:
    '''

    x_values = []
    y_values = []
    for x, y, _ in table:
        if x not in x_values:
            x_values.append(x)
        if y not in y_values:
            y_values.append(y)


    xv_values = []
    for cur_x in x_values:
        yz_values = [(y, z) for x, y, z in table if x == cur_x]
        xv_values.append((cur_x, newton_polynomial(yz_values, target_y, n)))

    return newton_polynomial(xv_values, target_x, n)



f = lambda x, y: 2 * x**2 + (y - 4)*3 + 3

t = [(x, y, f(x, y)) for x in range(1, 20) for y in range(1, 20)]
n = 3

x, y = 13.5, 4.2

np_res = newton_polynomial2D(t, x, y, n)
res = f(x, y)

print(f"np: {np_res}\nres: {res}")

