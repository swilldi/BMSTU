def input_matrix(n, k=None):
    if k is None:
        k = n
    matrix = [[0 for __ in range(k)] for _ in range(n)]
    for row in range(n):
        print(f"Ввод строки {row}")
        for col in range(k):
            matrix[row][col] = int(input(f"Введите {col} эл: "))
    return matrix


row, col = int(input("Введите кол-во строк: ")), int(input("Введите кол-во столбцов: "))
matrix = input_matrix(row, col)

with open("def_dir/matrix.txt", "w") as f:
    for line in matrix:
        f.write(" ".join(map(str, line)) + "\n")

diag_sum = 0
for i in range(row):
    diag_sum += matrix[i][i]
print(diag_sum)

with open("def_dir/matrix_2.txt", "w") as f:
    for i in range(row):
        for j in range(col):
            if i == j:
                f.write(str(diag_sum) + " ")
            else:
                f.write(str(matrix[i][j]) + " ")
        f.write("\n")

include_matrix = [matrix[i][j] for i in range(row) for j in range(col)]

