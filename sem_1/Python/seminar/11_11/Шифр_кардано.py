import math

def rotate(matrix):
    length_side = len(matrix)
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

def print_matrix(matrix):
    for row in matrix:
        print("|",end="")
        for num in row:
            print(f"{num:^5}|", end="")
        print()



# encode_string = input("Введите строку для кодирования: ")
# length = math.ceil(math.sqrt(len(encode_string)))
length = int(input())
matrix = [[0] * length for _ in range(length)]
for row in range(length):
    for col in range(length):
        matrix[row][col] = int(input())

result = [[0 for i in range(length * 2)] for j in range(length * 2)]
for i in range(length):
    for j in range(length):
        result[i][j] = matrix[i][j]
rotate(matrix)

for i in range(length):
    for j in range(length, 2 * length):
        result[i][j] = matrix[i][j - length]
rotate(matrix)

for i in range(length, 2 * length):
    for j in range(length, 2 * length):
        result[i][j] = matrix[i - length][j - length]

rotate(matrix)
for i in range(length, 2 * length):
    for j in range(length):
        result[i][j] = matrix[i - length][j]

print_matrix(result)

# случайным образом зануляем одну из каждый цифр 1-9

from random import randint
for i in range(length*length):
    num = randint(0, 3)
    if num == 0:
        matrix[i // length - 1][i % length - 1] = 0
    elif num == 1:
        matrix[i // length - 1][i % length - 1] = 0
    elif num == 2:
        matrix[length + i // length - 1][length + i % length - 1] = 0
    else:
        matrix[length + i // length - 1][i % length - 1] = 0

print_matrix(matrix)


# в общем план
"""
1) вводим матрицу
2) делаем поворот по часовой конектим - 4 раза
3) 
"""






