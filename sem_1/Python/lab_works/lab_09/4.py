# Дудырев Дмитрий ИУ7-12Б
# Программа принимает матрицу D и список I
# В списке R запоминает максимальные значения строк матрицы D
# определяет средне арифметическое списка R
# Выводит матрицу D и списки I, R, средне арифметическое

from module import *

# Ввод матрицы D
amount_row = input_length("Введите количество строк матрицы: ")
amount_col = input_length("Введите количество столбцов матрицы: ")
matrix = input_matrix(amount_row, amount_col, "float")

# Ввод списка I
length_I = input_length("Введите длину списка I: ")
while length_I > amount_row:
    print()
    length_I = input_length("Введите длину списка I: ")
list_I = [input_int("Введите номер строки (начиная с 1): ") for _ in range(length_I)]

# Формирование списка R
list_R = [max(matrix[row-1]) for row in list_I]
# Средне арифметическое
arithmetic_mean = sum(list_R) / length_I

# Вывод матрицы, списков, средне ариметического
output_matrix(matrix)
print(
    f"""
Список I: {list_I}
Список R: {list_R}
Среднее арифметическое: {arithmetic_mean:g}
    """
)

