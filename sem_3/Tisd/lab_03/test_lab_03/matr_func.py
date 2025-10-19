def input_matrix(n: int, m: int) -> list[list[int]]:
    matrix = [[0] * m for _ in range(n)]
    
    k = 0
    line = input()
    while (k < m * n and line):
            i, j, v = map(int, line.split())
            matrix[i][j] = v
            line = input()

    return matrix

def transp_matrix(mtr):
    n, m = len(mtr), len(mtr[0])
    tr_mtr = [[0] * m for _ in range(n)]
    for i in range(n):
        for j in range(m):
            tr_mtr[i][j] = mtr[j][i]
    return tr_mtr

def mult_row_col(row, col):
    l = len(col)
    res = 0
    for i in range(l):
        res += row[i] * col[i]
    
    return res

def mult_matrix(mtr_a: list[list[int]], mtr_b: list[list[int]]) -> list[list[int]]:
    n, m = len(mtr_a), len(mtr_b[0])
    
    mtr = [[0] * m for _ in range(n)]
    for i in range(n):
        for j in range(m):
            mtr[i][j] = mult_row_col(mtr_a[i], mtr_b[j])
    
    return mtr

def print_coord(mtr):
    for i, row in enumerate(mtr):
        for j, el in enumerate(row):
            if el != 0:
                print(f"{i + 1} {j + 1} {el:3}")

def print_matrix(mtr):
    for i, row in enumerate(mtr):
        for j, el in enumerate(row):
            print(el, end=" ")
        print("")
        

# n, m = map(int, input().split())
# mtr_a = input_matrix(n, m)

# p, q = map(int, input().split())
# mtr_b = transp_matrix(input_matrix(p, q))

# res = mult_matrix(mtr_a, mtr_b)

# print("\nКоординаты")
# print_coord(res)

# print("\nМатрицы")
# print_matrix(res)










