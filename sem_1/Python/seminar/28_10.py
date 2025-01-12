# """
# Дано 2 масива А и В сформировать 3-й новый массив I, D (общее пересечение, разность). Без set
# """
#
# A = [54, 7, 3, 87, 3, 87, 2]
# B = [54, 7,320947 ,32095, 3, 390973, 4]
#
# A, B = sorted([A, B])
#
# min_length = min(len(A), len(B))
# I = []
# D = []
#
# for i in range(min_length):
#     num = A[i]
#     if num in B and (A.count(num) + B.count(num)) // 2 != I.count(num):
#         I.append(num)
#
#     if num not in B:
#         D.append(num)
#
# print(I, D, sep="\n")


# """
# Дано 2 масива А и В сформировать 3-й новый массив C, I, D (общее, пересечение, разность). Без set
# """
# A = [54, 7, 3, 87, 3, 87, 2]
# B = [54, 7,320947 ,32095, 3, 390973, 4]
#
# C = A + [x for x in B if x not in A]
# I = [num for num in A if num in B]
# D = [num for num in A if num not in B]
#
# print(I)
# print(D)


# '''
# Дан массив из N + 1 целых чисел, который содержит элементы в диапазоне [1, N]
# Найти любое повторяющееся число.
# '''
# # ходим по значениям чисел и умноежаем из на -1
# a = [3, 2, 3, 2, 1, 5]
# ind = a[0]
# while


# """
# Вводим N-размер квадратной матрицы. Сформировать матрицу ввида:
# 1 2 3 4 5
# 2 1 2 3 4
# 3 2 1 2 3
# 4 3 2 1 2
# 5 4 3 2 1
# """
#
# # N = int(input())
# N = 5
# matrix = [[None] * N for _ in range(N)]
#
# for row in range(N):
#     for col in range(N):
#         matrix[row][col] = abs(row - col) + 1
#
# for row in matrix:
#     print("".join(map(str,row)))


# '''
# Вводим N – размер кв матрицы. Сформировать матрицу
# 1 2 4
#   3 5
#     6
# '''
#
# N = 9
# matrix = []
# num = 1
# for col in range(N):
#     list_row = []
#     for row in range(col + 1):
#         list_row.append(num)
#         num += 1
#         if num == N + 1:
#             break
#     matrix.append(list_row)
#     if num == N + 1:
#         break
#
# for col in range(N):
#
#
# 2 * a_1 + 2n - 2 = (a_1 + a_n) * n / 2


'''
Найти max элемент кв матрицы среди элементов раположенных в заштрих облостх + границы
'''

# import random
#
# for i in range(10):
#     print("[", end="")
#     for j in range(10):
#         print(random.randint(1, 100), ", ", sep="", end="")
#     print("]")

N = 10
matrix = [[19, 2, 90, 60, 86, 58, 72, 5, 41, 40],
          [15, 53, 18, 28, 100, 88, 84, 6, 52, 27],
          [46, 18, 74, 93, 29, 78, 51, 6, 36, 11],
          [31, 8, 12, 69, 69, 45, 88, 79, 89, 10],
          [72, 93, 46, 80, 80, 78, 19, 2, 30, 47],
          [87, 95, 20, 25, 9, 3, 5, 52, 64, 70],
          [78, 20, 52, 68, 33, 56, 74, 65, 34, 58],
          [28, 27, 9, 22, 82, 14, 79, 43, 96, 6],
          [61, 87, 34, 97, 15, 91, 26, 89, 97, 76],
          [87, 33, 55, 85, 44, 35, 78, 49, 81, 22]]

left_max = right_max = 0

for col in range(N):
    for row in range(col, N - col):
        left_num = matrix[row][col]
        left_max = max(left_num, left_max)

        right_num = matrix[row][-(col + 1)]
        right_max = max(right_num, right_max)

print(left_max, right_max)


N = 10
matrix = [[19, 2, 90, 60, 86, 58, 72, 5, 41, 40],
          [15, 53, 18, 28, 100, 88, 84, 6, 52, 27],
          [46, 18, 74, 93, 29, 78, 51, 6, 36, 11],
          [31, 8, 12, 69, 69, 45, 88, 79, 89, 10],
          [72, 93, 46, 80, 80, 78, 19, 2, 30, 47],
          [87, 95, 20, 25, 9, 3, 5, 52, 64, 70],
          [78, 20, 52, 68, 33, 56, 74, 65, 34, 58],
          [28, 27, 9, 22, 82, 14, 79, 43, 96, 6],
          [61, 87, 34, 97, 15, 91, 26, 89, 97, 76],
          [87, 33, 55, 85, 44, 35, 78, 49, 81, 22]]

left_max = right_max = 0

for col in range(N // 2):
    for row in range(col, N - col):
        matrix[row][col] = 0

        matrix[row][-(col + 1)] = 0

for row in matrix:
    print(" ".join(map(str, row)))