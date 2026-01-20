# принимает функцию, начало и конец отрезка, количество участков разбития
# вычисляет интеграл функции на отрезке методом правых прямоугольников
# возвращает значение интеграла
def method_right_rectangles(func, a, b, section_count) -> float:
    step = abs(a - b) / section_count
    result = 0
    x = a + step
    for _ in range(1, section_count + 1):
        result += func(x)
        x += step
    result *= step
    return result


# принимает функцию, начало и конец отрезка, количество участков разбития
# вычисляет интеграл функции на отрезке методом трапеций
# возвращает значение интеграла
def method_trapezoids(func, a, b, section_count) -> float:
    step = abs(a - b) / section_count
    result = (func(a) + func(b)) / 2
    x = a + step
    for _ in range(section_count - 1):
        result += func(x)
        x += step
    result *= step
    return result


# принимает рассчитанное значение и фактическое
# высчитывает значения абсолютной и относительной погрешностей
# возвращает абсолютную и относительную погрешность
def calculate_errors(calculated_value, actual_value) -> (float, float):
    absolute_error = abs(abs(calculated_value) - abs(actual_value))
    relative_error = absolute_error / abs(actual_value) * 100
    return absolute_error, relative_error


# опционально принимает на вход выводимое сообщение и тип чисел
# будет запрашивать ввод числа, пока введенные данные не будут удовлетворять указанному типу чисел
# возвращает вводимое число
def input_number(msg="Введите число: ", number_type=float):
    while True:
        try:
            num = number_type(input(msg))
        except ValueError:
            if number_type is int:
                print("Введены не корректные данные. Необходимо ввести целое число")
            else:
                print("Введены не корректные данные. Необходимо ввести число")
        else:
            break
    return num


# Принимает название таблицы, значения первой строки, значение первой колонки, данные для таблицы
# Выводит отформатированную таблицу
def print_table(table_name, col_names, row_names, *args):
    space_length = 5
    args = list(map(lambda num: format(num, ".6g"), args))
    cell_length = len(max(max(args, key=len), max(col_names, key=len), key=len)) + space_length
    table_width = 3 * cell_length + 4

    print(
        "\n" + format(table_name, f"'^{table_width}"),
        "|" + "|".join(map(lambda el: format(el, f"^{cell_length}"), col_names)) + "|",
        "-" * table_width,
        "|" + "|".join(map(lambda el: format(el, f"^{cell_length}"), [row_names[0], *args[:2]])) + "|",
        "|" + "|".join(map(lambda el: format(el, f"^{cell_length}"), [row_names[1], *args[2:]])) + "|",

        sep="\n", end="\n\n"
    )
