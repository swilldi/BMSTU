# Дудырев Дмитрий ИУ7-12Б
# Программа принимает квадратную матрицу выводит её
# Поворачивает матрицу на 90 градусов по часовой стрелку выводит её
# Поворачивает матрицу на 90 градусов против часовой стрелку выводит её

from module import *

# Получение длины списка A
length_side = input_length("Введите длину квадратной матрицы: ")
# формирование матрицы
matrix = input_matrix(length_side, length_side, "int")
# Вывод исходной матрицы
output_matrix(matrix)

half_diagonal = length_side // 2 if length_side % 2 == 0 else length_side // 2 + 1
# поворот матрицы влево
for row in range(half_diagonal):
    for col in range(row, length_side - (row + 1)):
        # запоминаем исходные данные
        left_top = matrix[col][row]
        left_bottom = matrix[-(row + 1)][col]
        right_bottom = matrix[-(col + 1)][-(row + 1)]
        right_top = matrix[row][-(col + 1)]

        # заменяем в матрице
        matrix[col][row] = left_bottom
        matrix[row][-(col + 1)] = left_top
        matrix[-(col + 1)][-(row + 1)] = right_top
        matrix[-(row + 1)][col] = right_bottom

# Вывод повернутой влево матрицы
output_matrix(matrix)

# поворот матрицы вправо
for row in range(half_diagonal):
    for col in range(row, length_side - (row + 1)):
        # запоминаем исходные данные
        left_top = matrix[col][row]
        left_bottom = matrix[-(row + 1)][col]
        right_bottom = matrix[-(col + 1)][-(row + 1)]
        right_top = matrix[row][-(col + 1)]

        # заменяем в матрице
        matrix[col][row] = right_top
        matrix[-(row + 1)][col] = left_top
        matrix[-(col + 1)][-(row + 1)] = left_bottom
        matrix[row][-(col + 1)] = right_bottom

# # Вывод повернутой вправо матрицы
output_matrix(matrix)
