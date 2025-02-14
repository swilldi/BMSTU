# def str_to_float(num_str, base=10):
#     if '.' not in num_str:
#         return float(int(num_str, base))
#
#     integer_part, fractional_part = num_str.split('.')
#
#     # Целая часть
#     integer = int(integer_part, base)
#
#     # Дробная часть
#     fractional = 0.0
#     for i, char in enumerate(fractional_part, 1):
#         digit = int(char, base)
#         fractional += digit * (base ** -i)
#
#     return integer + fractional



def g():
    a = 0.0
    return f"{a:g}"
print(g())


# import random
#
# symbols = "0123"
# numbers_1 = []
# numbers_2 = []
# for _ in range(100_000):
#     l_1 = random.randint(2, 10)
#     num_1 = "".join(random.choices(symbols, k=l_1))
#     while num_1[0] == "0":
#         num_1 = "".join(random.choices(symbols, k=random.randint(2, 5)))
#     if random.randint(0, 10) > 8:
#         i = random.randint(1, l_1 - 1)
#         num_1 = num_1[:i] + "." + num_1[i:]
#     numbers_1.append(num_1)
#
#     l_2 = random.randint(2, 10)
#     num_2 = "".join(random.choices(symbols, k=l_2))
#     index_point_1 = random.randint(1, l_1 - 1)
#     while num_2[0] == "0":
#         num_2 = "".join(random.choices(symbols, k=random.randint(2, 5)))
#     if random.randint(0, 10) > 8:
#         i = random.randint(1, l_1 - 1)
#         num_2 = num_2[:i] + "." + num_2[i:]
#     numbers_2.append(num_2)
#
# for num_1, num_2 in zip(numbers_1, numbers_2):
#     num_1_10 = str_to_float(num_1, 4)
#     num_2_10 = str_to_float(num_2, 4)
#     s_10 = num_1_10 + num_2_10
#     d_10 = num_1_10 - num_2_10
#
#     s_4 = sum_in_4(num_1, num_2)
#     d_4 = substract_in_4(num_1, num_2)
#     # print(f"{num_1} + {num_2} = {s_4}")
#     # print(f"{num_1} - {num_2} = {d_4}")
#
#     if not(s_10 == str_to_float(s_4, 4)):
#         print("Короче сумма не работает")
#         print(num_1, num_2, s_4)
#         break
#     if not (d_10 == str_to_float(d_4, 4)):
#         print(d_10)
#         print("Короче разница не работает")
#         print(num_1, num_2, d_4)
#         break
#
#
# print(substract_in_4("3", "3"))
# # 21.30 31133 -31111.10