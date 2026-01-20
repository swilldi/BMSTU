# Дудырев Дмитрий Сергеевич ИУ7-12Б
# Программа принимает на вход размеры матрицы, далее элементы матрицы
# Поиск строки с максимальным количеством нулевых элементов
# Вывод индекс и строку первой строки с наибольшим количеством нулевых элементов

import math

eps = 1e-8
max_number_of_zero = 0
index_row = -1
length_row_max = 0

# ввод количества строк
number_of_columns = float(input("Введите количество колонок: "))
while abs(number_of_columns - int(number_of_columns)) > eps or number_of_columns <= 0:
    print("Число должно быть целым положительным ")
    number_of_columns = float(input("Введите количество колонок: "))
else:
    number_of_columns = int(number_of_columns)

# ввод количества строк
number_of_rows = float(input("Введите количество строк: "))
while abs(number_of_rows - int(number_of_rows)) > eps or number_of_rows <= 0:
    print("Число должно быть целым положительным ")
    number_of_rows = float(input("Введите количество строк: "))
else:
    number_of_rows = int(number_of_rows)

# формирование матрицы
matrix = [None] * number_of_rows

# заполнение матрицы
for row in range(number_of_rows):
    print(f"Введите элементы {row + 1}-й строки через пробел: ", end="")
    # ввод полной строки матрицы
    row_elements = input().strip()
    length_row = len(row_elements)
    row_elements = row_elements.split()
    # проверка количества элементов
    while len(row_elements) != number_of_columns:
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

# поиск строки с минимальным количеством нулевых элементов
for i in range(number_of_rows):
    number_of_zero = matrix[i].count(0)
    if max_number_of_zero < number_of_zero:
        index_row = i
        max_number_of_zero = number_of_zero

if index_row != -1:
    print(f"\nВ {index_row + 1}-й строке наибольшее количество нулевых элементов: {max_number_of_zero}",
          matrix[index_row], sep="\n")
else:
    print("В веденной матрице не нулевых элементов")

# Вывод матрицы в виде таблицы
print()
length_table_cell = math.ceil(length_row_max / number_of_columns) + 5
for row in matrix:
    for num in row:
        print(f"{num:^{length_table_cell}g}", end=" ")
    print()
