# Дудырев Дмитрий ИУ7-12Б
# Даны два целочисленных списка A и B
# Сформировать матрицу M в которой
# m_i_j = a_i * b_j

from math import isqrt
from module import *

# Получение длины списка A
length_A = input_length("Введите длину списка A: ")
# Заполнение списка A
list_A = [input_int(f"Введите {i+1}-й элемент: ") for i in range(length_A)]

print("-" * 25)

# Получение длины списка B
length_B = input_length("Введите длину списка B: ")
# Заполнение списка B
list_B = [input_int(f"Введите {i+1}-й элемент: ") for i in range(length_B)]

# Список количества полных квадратов
list_S = []
matrix = [[0] * length_A for _ in range(length_B)]

# Формирование матрицы
for i in range(length_A):
    # количество полных квадратов в строке
    amount_full_sqrt = 0
    for j in range(length_B):
        m = list_A[i] * list_B[j]
        matrix[j][i] = m
        # проверка на полный квадрат
        if isqrt(m):
            amount_full_sqrt += 1
    list_S.append(amount_full_sqrt)

# Вывод матрицы
output_matrix(matrix)

