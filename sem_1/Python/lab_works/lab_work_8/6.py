# Дудырев Дмитрий Сергеевич ИУ7-12Б
# Программа принимает на вход размеры матрицы, далее элементы матрицы
# транспонирование введенной матрицы
# Вывод измененной матрицы

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

# транспонирование матрицы
for row in range(length_side):
    for col in range(row):
        matrix[row][col], matrix[col][row] = matrix[col][row], matrix[row][col]


# Вывод матрицы в виде таблицы
print()
length_table_cell = math.ceil(length_row_max / length_side) + 5
for row in matrix:
    for num in row:
        print(f"{num:^{length_table_cell}g}", end=" ")
    print()
