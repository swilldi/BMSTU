# Сложение и вычитание вещественных чисел в 4-й системе счисления.

def parts_num(num: str) -> (int, float):
    """Функция принимает на вход число и возвращает его целую и дробную части"""
    num = str(num).lstrip("-").split(".")
    if len(num) == 2:
        return num[0], num[1]
    else:
        return num[0], "0"

def greeter_them(num_1: (str, str), num_2: (str, str)) -> bool:
    # проверяем по длине целой части
    if len(num_1[0]) > len(num_2[0]):
        return True
    elif len(num_1[0]) < len(num_2[0]):
        return False

    # проверяем целую часть
    for digit_1, digit_2 in zip(num_1[0], num_2[0]):
        # print(digit_1, digit_2)
        if digit_1 > digit_2:
            return True
        elif digit_1 < digit_2:
            return False

    # проверяем дробную часть
    for digit_1, digit_2 in zip(num_1[1], num_2[1], strict=True):
        # print(digit_1, digit_2)
        if digit_1 > digit_2:
            return True
        elif digit_1 < digit_2:
            return False

    # длину дробной части
    if len(num_1[1]) > len(num_2[1]):
        return True
    elif len(num_1[1]) < len(num_2[1]):
        return False

    # числа равны
    return True


def sum_in_4(num_1: str, num_2: str) -> str:
    num_1 = parts_num(num_1)
    num_2 = parts_num(num_2)

    max_len_int = max(len(num_1[0]), len(num_2[0]))
    max_len_drob = max(len(num_1[1]), len(num_2[1]))

    num_1, num_2 = map(lambda x: (x[0].rjust(max_len_int, "0"), x[1].ljust(max_len_drob, "0")), (num_1, num_2))

    new_num = ""
    overflow = 0

    for i in range(max_len_drob - 1, -1, -1):
        digit_1 = int(num_1[1][i])
        digit_2 = int(num_2[1][i])

        digit = digit_1 + digit_2 + overflow
        overflow = 0
        if digit >= 4:
            overflow = 1
            digit -= 4

        new_num = str(digit) + new_num

    new_num = "." + new_num

    for i in range(max_len_int - 1, -1, -1):
        digit_1 = int(num_1[0][i])
        digit_2 = int(num_2[0][i])

        digit = digit_1 + digit_2 + overflow
        overflow = 0
        if digit >= 4:
            overflow = 1
            digit -= 4

        new_num = str(digit) + new_num

    if overflow:
        new_num = str(overflow) + new_num
    return f"{float(new_num):g}"


def substract_in_4(num_1: str, num_2: str) -> str:
    num_1 = parts_num(num_1)
    num_2 = parts_num(num_2)

    is_positive_num = greeter_them(num_1, num_2)
    if not is_positive_num:
        num_1, num_2 = num_2, num_1

    max_len_int = max(len(num_1[0]), len(num_2[0]))
    max_len_drob = max(len(num_1[1]), len(num_2[1]))

    num_1, num_2 = map(lambda x: (x[0].rjust(max_len_int, "0"), x[1].ljust(max_len_drob, "0")), (num_1, num_2))

    new_num = ""
    overflow = False

    for i in range(max_len_drob - 1, -1, -1):
        digit_1 = int(num_1[1][i])
        digit_2 = int(num_2[1][i])

        digit = digit_1 - digit_2

        if overflow:
            digit -= 1
            overflow = False

        if digit < 0:
            overflow = True
            digit += 4

        new_num = str(digit) + new_num

    new_num = "." + new_num

    for i in range(max_len_int - 1, -1, -1):
        digit_1 = int(num_1[0][i])
        digit_2 = int(num_2[0][i])

        digit = digit_1 - digit_2

        if overflow:
            digit -= 1
            overflow = False

        if digit < 0:
            overflow = True
            digit += 4

        new_num = str(digit) + new_num

    if not is_positive_num:
        new_num = "-" + new_num
    return f"{float(new_num):g}"


