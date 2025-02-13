# Сложение и вычитание вещественных чисел в 4-й системе счисления.


def parts_num(num: str) -> (int, float):
    """Функция принимает на вход число и возвращает его целую и дробную части"""
    num = str(num).lstrip("-").split(".")
    if len(num) == 2:
        return int(num[0]), float("0." + num[1])
    else:
        return int(num[0]), 0.0

def converter_to_10(num_4: str) -> int:
    """
    СС - система счисления
    Функция принимает на вход строку в 4-й СС и возвращает число в 10-й СС
    """
    cur_degree = 0
    for i in range(len(num_4)):
        if num_4[i] == ".":
            break
        cur_degree = i

    num = 0
    for digit in num_4:
        if digit != ".":

            num += int(digit) * 4**cur_degree
            cur_degree -= 1

    return num

def converter_from_10(num_n: int, n: int) -> str:
    """Переводитьь число из 10 системы счисления в n-ю систему счисления"""
    full_part, drob_part = parts_num(str(num_n))
    num = ""

    # перевод целой части
    while full_part:
        num = str(full_part % n) + num
        full_part //= n

    # перевеод дробной части
    if drob_part:
        num += "."

        for _ in range(5):
            drob_part *= n
            full, drob = parts_num(drob_part)

            drob_part = drob
            num += str(full)

    return num.rstrip("0") if num_n >= 0 else "-" + num.rstrip("0")

def command_plus(num_1: str, num_2: str) -> str:
    "Функция принимает два числа и возвращает их сумму"
    num_1 = converter_to_10(num_1)
    num_2 = converter_to_10(num_2)
    return converter_from_10(num_1 + num_2, 4)

def command_minus(num_1: str, num_2: str) -> str:
    "Функция принимает два числа и возвращает результат вычитания второго из первого"
    num_1 = converter_to_10(num_1)
    num_2 = converter_to_10(num_2)
    return converter_from_10(num_1 - num_2, 4)





