from random import randint
from math import ceil, sqrt
from matrix_func import *

st = input()
size = int(sqrt(ceil(len(st))**2))
start_matrix = [[row * col for row in range(1, size+1)] for col in range(1, size + 1)]
matrix = [[0] * 2 * size for _ in range(2 * size)]

# Крутим матрицы и вставляем их в наши чертверти
for row in range(size):
    for col in range(size):
        matrix[row][col] = start_matrix[row][col]

rotate(start_matrix)
for row in range(size):
    for col in range(size):
        matrix[row][col+size] = start_matrix[row][col]

rotate(start_matrix)
for row in range(size):
    for col in range(size):
        matrix[row+size][col+size] = start_matrix[row][col]

rotate(start_matrix)
for row in range(size):
    for col in range(size):
        matrix[row+size][col] = start_matrix[row][col]
# Выводим получившуюся матрицу
print_matrix(matrix)

# Выбираем один квадрат и зануляем там число
for num in range(1, size**2 + 1):
    x = randint(1, 4)

    if x == 1:
        for row in range(size):
            for col in range(size):
                if matrix[row][col] == num:
                    matrix[row][col] = 0
                    break
    elif x == 2:
        for row in range(size):
            for col in range(size, size * 2):
                if matrix[row][col] == num:
                    matrix[row][col] = 0
                    break
    elif x == 2:
        for row in range(size, size * 2):
            for col in range(size, size * 2):
                if matrix[row][col] == num:
                    matrix[row][col] = 0
                    break
    else:
        for row in range(size, size * 2):
            for col in range(size):
                if matrix[row][col] == num:
                    matrix[row][col] = 0
                    break

# создаем матрицу, которую будем заполнять символами строки
# На позиции нулей martix в cardan_m записываем по очереди size**2 символов из строки
# потом поворачиваем matrix и повторяем ещё 3 раза
cardan_m = [[0] * 2 * size for _ in range(2 * size)]
st_i = 0
# стопе а как мы отслеживаем длину строки... ладушки потом разберемся.
for _ in range(4):
    for row in range(size * 2):
        for col in range(size * 2):
            if matrix[row][col] == 0:
                cardan_m[row][col] = st[st_i]
                st_i += 1
    rotate(matrix)

