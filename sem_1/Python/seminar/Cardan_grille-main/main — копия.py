from random import randint
from math import ceil, sqrt
from matrix_func import *

st = input("Введите строку: ")
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
    elif x == 3:
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

# шаблон шифровки
code_matrix_key = [[1 if el == 0 else 0 for el in row] for row in matrix]
# запись шаблона в файл
with open("key.txt", "w") as file:
    for row in code_matrix_key:
        for el in row:
            file.write(str(el))
        file.write("\n")

# создаем матрицу, которую будем заполнять символами строки
# На позиции нулей martix в cardan_m записываем по очереди size**2 символов из строки
# потом поворачиваем matrix и повторяем ещё 3 раза
cardan_m = [[0] * 2 * size for _ in range(2 * size)]
st_i = 0
st_is_end = False
# стопе а как мы отслеживаем длину строки... ладушки потом разберемся.
for _ in range(4):
    for row in range(size * 2):
        for col in range(size * 2):
            if matrix[row][col] == 0:
                cardan_m[row][col] = st[st_i]
                st_i += 1
                if st_i == len(st):
                    st_is_end = True
                    break
        if st_is_end:
            break
    if st_is_end:
        break
    # крутим вертим и тд =)
    rotate(matrix)

# записывает защифрованную матрицу
with open("coded_matrix.txt", "w") as file:
    for row in cardan_m:
        for el in row:
            file.write(str(el))
        file.write("\n")


# надо записать строки матрицы в файл в виде целых чисел

# считываем матрицу-ключ
key_matrix = [[0 for _ in range(2 * size)] for _ in range(2 * size)]
with open("key.txt", "r") as file:
    for row in range(size * 2):
        line = file.readline()
        for col in range(size * 2):
            key_matrix[row][col] = line[col]

# расшифровка
# файл с целыми числами, которые являются двоичной записью строк матрицы ключа
encode_text = open("encode_text.txt", "w")
encode_key_matrix = [[el for el in row if el != "\n"] for row in file.readline("coded_matrix.txt")]


