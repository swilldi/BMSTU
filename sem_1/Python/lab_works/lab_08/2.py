# Дудырев Дмитрий Сергеевич ИУ7-12Б
# Программа принимает на вход размеры матрицы, далее элементы матрицы
# Поиск первой строки с максимальным количеством отрицательных элементов
# Поиск первой строки с минимальным количеством отрицательных элементов
# Перестановка местами строк найденных строк
# Вывод измененной матрицы

import math

eps = 1e-8
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

# поиск строк с минимальным и максимальным количеством отрицательных чисел
index_row_min = index_row_max = -1
amount_number_max = 0
amount_number_min = number_of_columns + 1
for i in range(number_of_rows):
    amount = 0
    for num in matrix[i]:
        if num < 0:
            amount += 1

    if amount == 0:
        continue

    # индекс строки с максимальным количеством
    if amount_number_max < amount:
        amount_number_max = amount
        index_row_max = i
        continue

    # индекс строки с минимальным количеством
    if amount_number_min > amount:
        amount_number_min = amount
        index_row_min = i
        continue


# Меняем местами строки
if index_row_min == -1 and index_row_min == -1:
    print("В матрице отсутствуют отрицательные элементы")
elif index_row_min == -1:
    print("В матрице одна строка с отрицательными элементами")
else:
    matrix[index_row_min], matrix[index_row_max] = matrix[index_row_max], matrix[index_row_min]

# Вывод матрицы в виде таблицы
print()
length_table_cell = math.ceil(length_row_max / number_of_columns) + 5
for row in matrix:
    for num in row:
        print(f"{num:^{length_table_cell}g}", end=" ")
    print()
