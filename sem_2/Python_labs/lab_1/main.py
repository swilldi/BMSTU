# Сложение и вычитание вещественных чисел в 4-й системе
# счисления.

def parts_num(num: str) -> (int, float):
    num = str(num).split(".")
    if len(num) == 2:
        return int(num[0]), float("0." + num[1])
    else:
        return int(num[0]), 0.0

def converter_to_10(num_4: str) -> int:
    point_ind = 0
    for i in range(len(num_4)):
        if num_4[i] == ".":
            point_ind = i
            break

    cur_degree = point_ind - 1

    num_4 = num_4.replace(".", "")
    num = 0
    for digit in num_4:
        num += int(digit) * 4**cur_degree
        cur_degree -= 1

    return num

def convert_from_10(num_n: int, n: int) -> str:
    full_part, drob_part = parts_num(str(num_n))
    num = ""

    while full_part:
        num = str(full_part % n) + num
        full_part //= n

    if drob_part:
        num += "."

        for _ in range(5):
            drob_part *= n
            full, drob = parts_num(drob_part)

            drob_part = drob
            num += str(full)

    return num





