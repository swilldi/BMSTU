# Дудырев Дмитрий ИУ7-12Б
# Программа запрашивает у пользователя начало и конец отрезка интегрирования
# и два варианта разбиения участка(N1, N2).
# Программа вычисляет приближенное значение интеграла при помощи:
# Метод 1: правых прямоугольников
# Метод 2: трапеций
# Выводит таблицу с полученными результатами
# Определяет и выводим название наиболее точного метода
# Запрашивает значение точности
# Вычисляет количество участков разбитие необходимое менее точному методу чтобы его достичь данной точности
# вычисляется по формуле |I(N) - I(2N)| < eps

from module import *


# функция
def f(x):
    return x ** 2
    # return (x ** 2 - 3 * x) / (x + 1)


# первообразная функции
def F(x):
    return x**3 / 3
    # return x ** 3 / 3 - 1.5 * x**2
    # return (x+1)**2 / 2 - 5 * (x + 1) + 4 * log(abs(x + 1), e)


# Ввод начала и конца отрезка
start_segment = input_number("Введите начальное значение отрезка: ")
end_segment = input_number("Введите конечное значение отрезка: ")

# Ввод количества участков для разбития
section_count_1 = input_number("Введите количество участков разбиения 1: ", int)
section_count_2 = input_number("Введите количество участков разбиение 2: ", int)

# значение интеграла по функции
I1_N1 = method_right_rectangles(f, start_segment, end_segment, section_count_1)
I1_N2 = method_right_rectangles(f, start_segment, end_segment, section_count_2)
I2_N1 = method_trapezoids(f, start_segment, end_segment, section_count_1)
I2_N2 = method_trapezoids(f, start_segment, end_segment, section_count_2)

# Таблица рассчитанных значений
print_table(
    "Рассчитанные значения",
    ["Метод\Участков", str(section_count_1), str(section_count_2)],
    ["Пр прямоугольников", "Трапеций"],
    I1_N1, I1_N2, I2_N1, I2_N2
)

# Значение интеграла по первообразной функции
integral = F(end_segment) - F(start_segment)

# Погрешности при использовании первого метода
abs_I1_N1, relative_I1_N1 = calculate_errors(I1_N1, integral)
abs_I1_N2, relative_I1_N2 = calculate_errors(I1_N2, integral)
# Погрешности при использовании второго метода
abs_I2_N1, relative_I2_N1 = calculate_errors(I2_N1, integral)
abs_I2_N2, relative_I2_N2 = calculate_errors(I2_N2, integral)

# Таблица погрешностей первого метода
print_table(
    "Погрешности метода правых прямоугольников",
    ["Участков\Тип", "Абсолютная", "Относительная %"], [str(section_count_1), str(section_count_2)],
    abs_I1_N1, relative_I1_N2, abs_I1_N2, relative_I1_N2
)
# Таблица погрешностей первого метода
print_table(
    "Погрешности метода трапеций",
    ["Участков\Тип", "Абсолютная", "Относительная %"], [str(section_count_1), str(section_count_2)],
    abs_I2_N1, relative_I2_N1, abs_I2_N2, relative_I2_N2
)

# минимальна погрешность
min_error = min(abs_I1_N1, relative_I1_N2, abs_I1_N2, relative_I1_N2,
                abs_I2_N1, relative_I2_N1, abs_I2_N2, relative_I2_N2)
# определения метода с минимальной погрешностью
if min_error in [abs_I1_N1, relative_I1_N2, abs_I1_N2, relative_I1_N2]:
    better_method = method_right_rectangles
    better_method_name = "Правых прямоугольников"
    worse_method = method_trapezoids
    worse_method_name = "Трапеций"
else:
    better_method = method_trapezoids
    better_method_name = "Трапеций"
    worse_method = method_right_rectangles
    worse_method_name = "Правых прямоугольников"

print("Наиболее точный метод: " + better_method_name, end="\n\n")

# Ввод числа точности
eps = input_number("Введите значение точности: ")
# Определения максимального
section_count = 1
# вычисление интегралов менее точным методом
I1 = worse_method(f, start_segment, end_segment, section_count)
I2 = worse_method(f, start_segment, end_segment, 2 * section_count)
# поиск необходимого кол-во отрезков
while abs(I1 - I2) >= eps:
    section_count *= 2
    I1 = I2
    I2 = worse_method(f, start_segment, end_segment, 2 * section_count)
# вывод необходимого количества отрезков и значение интеграла при данном количестве отрезков
print(f"Для достижения необходимой точности методом {worse_method_name} необходимо {section_count} отрезков\n"
      f"Результат вычисления {worse_method(f, start_segment, end_segment, section_count):.6g}")

