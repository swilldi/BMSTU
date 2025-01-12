# Дудырев Дмитрий ИУ7-12Б
# Программа принимает две матрицы A и B и формирует третью матрицу С – произведение A и B
# Вывод матриц A, B, C

from module import *

# Ввод размеров матрицы A и формирование матрицы
amount_row_A = input_length("Введите количество строк матрицы A: ")
amount_col_A = input_length("Введите количество столбцов матрицы A: ")
matrix_A = input_matrix(amount_row_A, amount_col_A, "float")

# Ввод размеров матрицы B и формирование матрицы
print()
amount_row_B = input_length("Введите количество строк матрицы B: ")
amount_col_B = input_length("Введите количество столбцов матрицы B: ")
matrix_B = input_matrix(amount_row_B, amount_col_B, "float")

# Вывод матриц A и B
output_matrix(matrix_A, "Matrix_A")
output_matrix(matrix_B, "Matrix_B")

# Проверка на возможность умножения
if amount_col_A == amount_row_B:
    # создание матрицы произведения
    matrix_C = [[0] * amount_col_B for _ in range(amount_row_A)]

    # заполнение матрицы произведения
    for row in range(amount_row_A):
        for col in range(amount_col_B):
            num = sum([matrix_A[row][i] * matrix_B[i][col] for i in range(amount_col_A)])
            matrix_C[row][col] = num

    # вывод полученной матрицы
    output_matrix(matrix_C, "Matrix_C")
else:
    print("Матрицы нельзя перемножить, так как количество столбцов A не равно количеству строк B")


