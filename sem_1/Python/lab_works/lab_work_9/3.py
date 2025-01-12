# Дудырев Дмитрий ИУ7-12Б
# Программа принимает две матрицы A и B
# Считает в столбцах А количество элементов больших средне арифметического того же столбца B
# Выводит полученные значения
# Умножает столбцы B на соответсвующее количество элементов больший средне арифметического в столбцах A
# Выводит преобразованную матрицу B

from module import input_length, input_matrix, output_matrix


def col_arithmetic_mean(matrix, col) -> float:
    summa = 0
    for row in range(len(matrix)):
        summa += matrix[row][col]

    return summa / amount_col

# Ввод количества столбцов в матрицах
amount_col = input_length("Введите количество столбцов матриц: ")

# формирование матрицы A
amount_row_A = input_length("Введите количество строк матрицы A: ")
matrix_A = input_matrix(amount_row_A, amount_col, "float")

# формирование матрицы B
amount_row_B = input_length("Введите количество строк матрицы B: ")
matrix_B = input_matrix(amount_row_B, amount_col, "float")


output_matrix(matrix_A, "Matrix A")
output_matrix(matrix_B, "Matrix B")

more_arithmetic_mean = [0] * amount_col
# подсчет количества элементов в столбце A больших средне арифметического в B
for col in range(amount_col):
    arith_mean = col_arithmetic_mean(matrix_B, col)

    # кол-во чисел, которые больше ср.арифметического
    amount = 0
    for row in range(amount_row_A):
        if matrix_A[row][col] > arith_mean:
            amount += 1
    more_arithmetic_mean[col] = amount


# вывод количества чисел из А больше средне арифметического из В для каждого столбца
info = "1-я строка – номер колонки\n2-я срока кол-во элементов > ср.ариф. в этой колонке"
output_matrix([list(range(1, amount_col + 1)), more_arithmetic_mean], info)


for col in range(amount_col):
    if more_arithmetic_mean[col] == 0:
        continue

    for row in range(amount_row_B):
        matrix_B[row][col] *= more_arithmetic_mean[col]

output_matrix(matrix_B, "Matrix B")


