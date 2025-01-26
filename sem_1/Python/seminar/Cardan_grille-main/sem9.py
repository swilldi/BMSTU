# 1
'''
Решётка Кардано
'''
from random import randint
from math import sqrt, ceil

def rotate_counterclockwise(M, n):
    for i in range(n // 2):
        for j in range(i, n - 1 - i):
            M[i][j], M[j][n - 1 - i], M[n - 1 - i][n - j - 1], M[n - j - 1][i] = \
                M[j][n - 1 - i], M[n - 1 - i][n - j - 1], M[n - j - 1][i], M[i][j]
    return M

def rotate_clockwise(M, n):
    for i in range(n // 2):
        for j in range(i, n - 1 - i):
            M[j][n - 1 - i], M[n - 1 - i][n - j - 1], M[n - j - 1][i], M[i][j] =\
                M[i][j], M[j][n - 1 - i], M[n - 1 - i][n - j - 1], M[n - j - 1][i]
    return M

def print_matrix(matrix):
    """Выводит матрицу"""
    n = len(matrix)
    for i in range(n):
        for j in range(n):
            print(f"{matrix[i][j]:^11.4g}", end='')
        print()

def matrix_rotating(matrix):
    n = len(matrix)
    new_matrix = [[0]*2*n for i in range(2*n)]
    for k in range(4):
        for i in range(n):
            for j in range(n):
                new_matrix[i][j] = matrix[i][j]
        new_matrix = rotate_counterclockwise(new_matrix, 2 * n)
    return new_matrix

def make_null(matrix, num, r_1, r_2):
    for i in r_1:
        for j in r_2:
            if matrix[i][j] == num:
                matrix[i][j] = 0


def matrix_make_nulls(matrix):
    """Занулить по одному рандомному числу"""
    n = len(matrix)

    for s in range(n):
        l = s + 1
        num = randint(0, 3)
        if num == 0:
            make_null(matrix, l, range(n), range(n))
        elif num == 1:
            make_null(matrix, l, range(n), range(n, n*2))
        elif num == 2:
            make_null(matrix, l, range(n, n*2), range(n))
        else:
            make_null(matrix, l, range(n, n*2), range(n, n*2))


# размер кв матриц
n = int(input())
M = [[i+1+j*n for i in range(n)] for j in range(n)]
A = matrix_rotating(M)

print_matrix(A)
matrix_make_nulls(A)


print('_________________________________________________')
for i in range(2*n):
    for j in range(2*n):
        if A[i][j] == 0:
            A[i][j] = 1
        else:
            A[i][j] = 0
for i in range(2*n):
    for j in range(2*n):
        print('{:^11.4g}'.format(A[i][j]), end='')
    print()
'''
А - шаблон
st = 'стих'
в выколотые элементы записать n**2 букв
'''
st = ' Лукоморья дуб зеленый, златая цепь на дубе том. И днем, и ночь кот ученный'
len_st = len(st)
n = ceil(sqrt(len_st) / 2)
st = st + (4 * n ** 2 - len(st)) * ' '
S = [[0] * 4 * n ** 2 for i in range(4 * n ** 2)]
o = 0
for k in range(4):
    for i in range(2 * n):
        for j in range(2 * n):
            if A[i][j] == 1:
                S[i][j] = st[o]
                o += 1
    A = rotate_clockwise(A, 2*n)
print('_________________________________________________')
for i in range(2*n):
    for j in range(2*n):
        print('{:^11}'.format(S[i][j]), end='')
    print()
# N = math.ceil(len(st) ** 0.5)

# Закодировать в виде двоичного кода 1 - число, 0 - 0
with open("key.txt", 'w') as file_1:
    for i in range(n*2):
        num = int(''.join(map(str, A[i])), 2)
        file_1.write(f'{num}\n')
print('__________________________________________________')
for i in range(2*n):
    for j in range(2*n):
        print('{:^11.4g}'.format(A[i][j]), end='')
    print()

with open("enc.txt", 'w') as file_2:
    for i in range(2*n):
        for j in range(2*n):
            file_2.write(S[i][j])
