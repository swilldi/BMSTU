# Дудырев Дмитрий Сергеевич ИУ7-12Б
# Программа принимает на вход размеры матрицы, далее элементы матрицы
# Поиск максимального элемента на главной диагональю и минимального под побочной
# Вывод максимального, минимального значений и самой матрицы

import math

eps = 1e-8
length_row_max = 0

# ввод количества строк
length_side = float(input("Введите размер квадратной матрицы: "))
while abs(length_side - int(length_side)) > eps or length_side <= 0:
    print("Число должно быть целым положительным ")
    length_side = float(input("Введите размер квадратной матрицы: "))
else:
    length_side = int(length_side)



# формирование матрицы
matrix = [None] * length_side

# заполнение матрицы
for row in range(length_side):
    print(f"Введите элементы {row + 1}-й строки через пробел: ", end="")
    # ввод полной строки матрицы
    row_elements = input().strip()
    length_row = len(row_elements)
    row_elements = row_elements.split()
    # проверка количества элементов
    while len(row_elements) != length_side:
        print("Количество элементов должно быть равно количеству колонок\n"
              f"Введите элементы {row + 1}-й строки через пробел: ", end="")
        row_elements = input().strip()
        length_row = len(row_elements)
        row_elements = row_elements.split()

    matrix[row] = list(map(float, row_elements))

    # определение максимальной длины строки для форматирования вывода
    if length_row > length_row_max:
        length_row_max = length_row
print()

# Определение максимального числа над главной диагональю и минимального под побочной
if length_side >= 3:
    value_max = matrix[1][-1]
    value_min = matrix[-1][-1]
    for row in range(length_side):
        for col in range(length_side - 1, row, -1):
            # число над главной диагональю
            num_main = matrix[row][col]
            if value_max < num_main:
                value_max = num_main

            # число под побочной диагональю
            num_additional = matrix[-(row + 1)][col]
            if value_min > num_additional:
                value_min = num_additional
    print(f"Максимальное значение над главной диагональю: {value_max}\n"
          f"Минимальное значение под побочной диагональю: {value_min}")
else:
    print("В данной матрице все числа принадлежать диагонали")


# Вывод матрицы в виде таблицы
print()
length_table_cell = math.ceil(length_row_max / length_side) + 5
for row in matrix:
    for num in row:
        print(f"{num:^{length_table_cell}g}", end=" ")
    print()

