from pprint import *
# numerator
# denominator

amount_col = amount_row = 4

matrix = [
    [-2, 1, 3, 2],
    [3, 0, -1, 2],
    [-5, 2, 3, 0],
    [4, -1, 2, -3]
]

multiplier_matrix = 1
multiplier_row = {i:1 for i in range(amount_row)}
for col in range(amount_col):

    multiplier_matrix *= matrix[col][col]
    for i in range(amount_col-1, col-1, -1):
        matrix[col][i] /= matrix[col][col]

    # находим множители чтобы привести числа стобца к 1-це
    for row in range(col+1, amount_row):
        if matrix[row][col] == 0:
            continue

        divider = matrix[row][col]
        if divider == 0:
            divider = 1
        multiplier_matrix *= divider
        for i_col in range(amount_col):
            matrix[row][i_col] /= divider
            matrix[row][i_col] -= matrix[col][i_col]



pprint(matrix)
print(multiplier_matrix)



