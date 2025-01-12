# Константа для проверки равенства дробных чисел
EPS = 1e-8
# Константа дополнительного "свободного" места в таблице вывода
ADD_SPACE = 5

# Ввод числа обозначающего длину
# Принимает на вход сообщение, которое будет выводиться пользователю
# Будет запрашивать ввод числа, пока оно не будет целым положительным
def input_length(mes) -> int:
    num = float(input(mes))
    while abs(num - int(num)) > EPS or num <= 0:
        print("Длина – целое положительное число")
        num = float(input(mes))
    return int(num)

# Ввод целого числа
# Принимает на вход сообщение, которое будет выводиться пользователю
# Будет запрашивать ввод числа, пока оно не будет целым
def input_int(mes) -> int:
    num = float(input(mes))
    while abs(num - int(num)) > EPS:
        print("Элемент – целое число")
        num = float(input(mes))
    return int(num)

# Ввод символа
# Принимает на вход сообщение, которое будет выводиться пользователю
# Будет запрашивать ввод строки, пока её длина не равна 1
def input_char(mes) -> str:
    char = input(mes)
    while len(char) != 0:
        print("Элемент – один символ")
        char = input(mes)
    return char


# Ввод матрицы
# Принимает на вход размеры матрицы и тип вводимых данных
# Заполняет матрицу запрашивая данные у пользователя
def input_matrix(amount_row: int, amount_col: int = None, elements_type=None):
    if amount_col is None:
        amount_col = amount_row

    # заполнение матрицы
    matrix = [[0] * amount_col for _ in range(amount_row)]
    for row in range(amount_row):
        print(f"--Ввод {row + 1}-й строки--")
        for col in range(amount_col):
            element_mes = f"Введите {col + 1}-й элемент: "

            # проверка типа вводимых данных
            if elements_type == "int":
                matrix[row][col] = input_int(element_mes)
            elif elements_type == "float":
                matrix[row][col] = float(input(element_mes))
            elif elements_type == "char":
                matrix[row][col] = input_char(element_mes)
            else:
                matrix[row][col] = input()

    return matrix

# Вывод матрицы
# Принимает на вход матрицу и (опционально) текст выводимый над ней
# Ищет длину максимального элемента
# Выводит отформатированную матрицу
def output_matrix(matrix, text="MATRIX"):
    # размеры матрицы
    amount_row = len(matrix)
    amount_col = len(matrix[0])

    # размеры ячейки таблицы
    cell_size = 0
    for row in matrix:
        for el in row:
            cell_size = max(cell_size, len(str(el)))
    cell_size += ADD_SPACE

    # ширина матрицы
    table_width = (cell_size + 1) * amount_col - 1

    # верхний заголовок таблицы
    print(f"\n{text:^{table_width + 2}}\n" +
          "|" + "–" * table_width + "|", sep="")
    # вывод матрицы
    for i in range(amount_row):
        print("|", end="")
        for el in matrix[i]:
            print(f"{el:^{cell_size}}|", end="")
        print()

