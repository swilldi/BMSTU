# Сложение и вычитание вещественных чисел в 4-й системе
# счисления.

def parts_num(num: str) -> (int, int):
    num = num.strip(".")
    return int(num[0]), int("0." + num[1])

def converter_to_10(num_4: str) -> int:
    num_4 = num_4.replace(".", " ")
    num = 0
    cur_degree = len(num_4) - 1
    for digit in num_4:
        num += digit * 4**cur_degree
        cur_degree -= 1

    return num

def convert_from_10(num_n: int, n: int) -> str:
    num_n = str(num_n.strip("."))

    full_part, drob_part = parts_num(num_n)
    num = ""

    while full_part:
        num += full_part % n
        full_part //= n

    num += ","

    countZero = 0
    for _ in range(5):
        drob_part *= n
        full, drob = parts_num(drob_part)

        drob_part = drob
        num += str(full)






