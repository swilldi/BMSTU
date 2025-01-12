eps = 1e-8

# размер матрицы
length_side = float(input("Введите размер квадратной матрицы: "))
while abs(length_side - int(length_side)) > eps or length_side < 0:
    print("Размер должен быть целым положительным")
    length_side = float(input("Введите размер квадратной матрицы: "))
length_side = int(length_side)

# формирование матрицы
matrix = [None] * length_side
for row in range(length_side):
    numbers = list(map(int, input(f"Введите {row + 1}-ю строку матрицы через пробел: ").strip().split()))
    if len(numbers) != length_side:
        print("Количество элементов должно равняться размеру матрицы")
        numbers = list(map(int, input(f"Введите {row + 1}-ю строку матрицы через пробел: ").strip().split()))
    matrix[row] = numbers.copy()

print("исходная")
for row in matrix:
    for num in row:
        print(f"{num:^10}", end=" ")
    print()

if length_side < 3:
    print("В крыльях ничего нет =(")
else:

    for col in range(length_side // 2):
        for row in range(col + 1, length_side - (col + 1)):
            matrix[row][col], matrix[row][-(col + 1)] = matrix[row][-(col + 1)], matrix[row][col]

print("итоговая")
for row in matrix:
    for num in row:
        print(f"{num:^10}", end=" ")
    print()

