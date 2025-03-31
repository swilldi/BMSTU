# Дудырев Дмитрий Сергеевич ИУ7-12Б
# Программа принимает на вход размеры матрицы, далее элементы матрицы
# Поиск стобца с минимальной и максимальной суммами элементов
# Меняем данные стобцы местами
# Вывод измененной матрицы

import math

eps = 1e-8
index_max = index_min = -1
sum_min = math.inf
sum_max = -math.inf
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
              f"Введите элементы {row + 1}-й строки через пробел: ", end="", sep="")
        row_elements = input().strip()
        length_row = len(row_elements)
        row_elements = row_elements.split()

    matrix[row] = list(map(float, row_elements))

    # определение максимальной длины строки для форматирования вывода
    if length_row > length_row_max:
        length_row_max = length_row
print()

# поиск максимальной и минимальной суммы и индекса данных стобцов
for col in range(number_of_columns):
    sum_col = 0
    for row in range(number_of_rows):
        sum_col += matrix[row][col]

    # индекс столбца с максимальной суммой
    if sum_col > sum_max:
        sum_max = sum_col
        index_max = col
    # индекс столбца с минимальной суммой
    if sum_col < sum_min:
        sum_min = sum_col
        index_min = col

# Меняем столбцы местами
for row in range(number_of_rows):
    matrix[row][index_max], matrix[row][index_min] = matrix[row][index_min], matrix[row][index_max]

# Вывод матрицы в виде таблицы
print()
length_table_cell = math.ceil(length_row_max / number_of_columns) + 5
for row in matrix:
    for num in row:
        print(f"{num:^{length_table_cell}g}", end=" ")
    print()
