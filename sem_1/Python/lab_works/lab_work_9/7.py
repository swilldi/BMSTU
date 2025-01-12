# Дудырев Дмитрий ИУ7-12Б
# Ввод трехмерного списка
# Вывод серединного среза по наибольшей стороне

from module import *

# Ввод размером трехмерного списка
length_X = input_length("Введите количество матриц: ")
length_Y = input_length("Введите количество столбцов: ")
length_Z = input_length("Введите количество строк: ")

list_3D = [0] * length_X

# заполнение трехмерного списка
for i in range(length_X):
    list_3D[i] = input_matrix(length_Z, length_Y)
# Вывод введенных матриц
for i in range(length_X):
    output_matrix(list_3D[i], f"Matrix_{i+1}")

# list_3D[X][Z][Y]
if length_X >= length_Y and length_X >= length_Z:
    # x - самая большая => YZ
    # Y – колонки, Z – строки
    matrix_slice = [[list_3D[length_X // 2 - 1][z][y] for y in range(length_Y)] for z in range(length_Z)]
elif length_Y >= length_Z:
    # y – самая большая => XZ
    # X – колонки, Z – строки

    matrix_slice = [[list_3D[x][z][length_Y // 2 - 1] for x in range(length_X)] for z in range(length_Z)]
else:
    # z – самая большая => XY
    # X – колонки, Y – строки
    matrix_slice = [[list_3D[x][length_Z // 2 - 1][y]  for y in range(length_Y)] for x in range(length_X)]

# вывод среза массива
output_matrix(matrix_slice)
