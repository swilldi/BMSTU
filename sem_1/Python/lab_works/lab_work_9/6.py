# Дудырев Дмитрий ИУ7-12Б
# Ввод матрицы символов
# Замена регистра всех согласных на заглавный, а гласных на строчный
# Вывод матрицы до и после преобразования

from module import input_length, input_matrix, output_matrix

vowels_letters = "AEIOUY"
consonants_letters = "bcdfghjklmnpqrstvwxz"

# Ввод размером матрицы
amount_row = input_length("Введите количество строк матрицы: ")
amount_col = input_length("Введите количество столбцов матрицы: ")
# Ввод матрицы
matrix = input_matrix(amount_row, amount_col, "char")

# Вывод изначальной матрицы
output_matrix(matrix)

# строчные согласные -> заглавные согласные
# строчные согласные -> строчные гласные
for row in range(amount_row):
    for col in range(amount_col):
        char = matrix[row][col]
        if char in vowels_letters:
            matrix[row][col] = matrix[row][col].lower()
        elif char in consonants_letters:
            matrix[row][col] = matrix[row][col].upper()

# Вывод преобразованной матрицы
output_matrix(matrix)


