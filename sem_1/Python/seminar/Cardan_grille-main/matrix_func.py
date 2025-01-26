def rotate(matrix):
    size = len(matrix)
    for i in range(size // 2):
        for j in range(i, size // 2 + 1):
            left_top = matrix[j][i]
            left_bottom = matrix[-(i + 1)][j]
            right_top = matrix[i][-(j + 1)]
            right_bottom = matrix[-(j + 1)][-(i + 1)]

            matrix[j][i], matrix[-(i + 1)][j] = left_bottom, right_bottom
            matrix[i][-(j + 1)], matrix[-(j + 1)][-(i + 1)] = left_top, right_top

def print_matrix(matrix):
    cell_size = find_cell_size(matrix)
    print("-" * ((len(matrix) + 1) * cell_size - 2))
    for row in matrix:
        print("|", end="")
        for num in row:
            print(f"{num:^{cell_size}}|", end="")
        print()
    print("-" * ((len(matrix) + 1) * cell_size - 2))

def input_matrix(row_count, col_count=None, t=str):
    if col_count is None:
        col_count = row_count

    matrix = [[0] * col_count for _ in range(row_count)]
    for row in range(row_count):
        print(f"--СТРОКА {row+1}--")
        for col in range(col_count):
            matrix[row][col] = t(input(f"[{col+1}]: "))
    return matrix

def find_cell_size(matrix):
    cell_size = 0
    for row in matrix:
        for num in row:
            cell_size = max(cell_size, len(str(num)))
    return cell_size + 5