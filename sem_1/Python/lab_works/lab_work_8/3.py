# Дудырев Дмитрий Сергеевич ИУ7-12Б
# Программа принимает на вход размеры матрицы, далее элементы матрицы
# Поиск стобца с минимальной разницой между модулями сумм положительных и отрицатльных элементов
# Вывод столбца и его индекса

import math

eps = 1e-8
index_col = 0
delta_min = math.inf
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

# поиск минимальной дельты сумм
for col in range(number_of_columns):
    sum_positive = 0
    sum_negative = 0
    # суммирование положительных и отрицательных чисел
    for row in range(number_of_rows):
        num = matrix[row][col]
        if num < 0:
            sum_negative += abs(num)
        else:
            sum_positive += num

    # замена минимальной дельты
    delta = abs(sum_positive - sum_negative)
    if delta < delta_min:
        delta_min = delta
        index_col = col

print(f"Столбец {index_col} имеет наименьшую разницу между суммой положительных и отрицательных чисел: {delta_min}")
for row in range(number_of_rows):
    print(f"{matrix[row][index_col]:g}", end=" ")
print("\n")

# Вывод матрицы в виде таблицы
print()
length_table_cell = math.ceil(length_row_max / number_of_columns) + 5
for row in matrix:
    for num in row:
        print(f"{num:^{length_table_cell}g}", end=" ")
    print()
