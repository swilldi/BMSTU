# # Вычислить y = 1 - x**2 / 2! + x**4 / 4!
#
# epsilon = float(input())
# x = float(input())**2
#
# fact = 1
# n_fact = 2
# znak = -1
#
# value = 1
# total = 1
# while value >= epsilon:
#     fact *= n_fact - 1
#     fact *= n_fact
#
#     value = znak * x / fact
#     total += value
#
#     znak *= -1
#     x **= 2
#     fact += 2
#     n_fact += 2

# # Вычислить x1 = 1 | y1 = 1 -> xi = x**2(i - 1) + y(i - 1)
# x = y = 1
# print(x, y)
# for i in range(9):
#     x, y = x**2 + y, x + y**2
#     print(x, y)

# # y = сумма (i = 1, 10) i!
# fact = 1
# total = 1
# for i in range(2, 11):
#     fact *= i
#     total += fact
# print(total)

# # n-ый член последовательности фибоначи
# n = int(input())
# x1 = x2 = 1
# for i in range(n - 1):
#     x2 += x1
#     x1, x2 = x2, x1
# print(x2)

# # Дан одномерный массив А. Переписать все положительные элементы в массив B
# length = int(input("Введите длину массива: "))
# A = [int(input(f"Введите элемент {i}: ")) for i in range(length)]
# B = []
#
# for num in A:
#     if num > 0:
#         B += [num]
#
# for i in range(len(B)):
#     print(f"элемент {i} = {B[i]}")

# #  Дан одномерный массив. Найти кол-во, сумму и произвдение положительных четных элементов
# length = int(input("Введите длину массива"))
# number = [float(input("Введиет {i}-ый элемент: ")) for i in range(length)]
#
# total_sum = 0
# total_proizv = 1
# amount = 0
#
# for num in number:
#     if abs(num) % 2 == 0:
#         total_sum += num
#         total_proizv *= num
#         amount += 1
# if amount != 0:
#     print(f"Сумма: {total_sum}\nПроизведени: {total_proizv}\nКоличество: {amount}")
# else:
#     print("Четных чисел нет")

# # меняет максимальный и минимальный элемент
# import math
#
# length = int(input("Введите длину массива: "))
# nums = [float(input(f"Введите {i + 1}-ый элемнт: ")) for i in range(length)]
#
# num_max = -math.inf
# index_max = -1
# num_min = math.inf
# index_min = -1
#
# for i in range(length):
#     num = nums[i]
#
#     if num > num_max:
#         num_max = num
#         index_max = i
#     if num < num_min:
#         num_min = num
#         index_min = i
#
# nums[index_max], nums[index_min] = num_min, num_max
# print(nums)
#
# nums[nums.index(max(nums))],nums[nums.index(min(nums))] = min(nums), max(nums)

# Даны точки на плоскости:
# A = [x1, y1, x2, y2, ..., xn, yn]
# Найти наиб. близкую и наиб. удаленную от [0, 0] и расстояние между ними

# import math
# length = int(input("Введите количество точек: ")) * 2
#
# max_distance = -math.inf
# min_distance = math.inf
# max_x = max_y = 0
# min_x = min_y = 0
#
#
# for i in range(0, length, 2):
#     x, y = A[i:i+2]
#     distance = x**2 + y**2
#     if distance > max_distance:
#         max_distance = distance
#         max_x = x
#         max_y = y
#     if distance < min_distance:
#         min_distance = distance
#         min_x = x
#         min_y = y
#
# print(f"Наиболее удаленная точка ({max_x}, {max_y})\n"
#       f"Наименее удаленная точка ({min_x}, {min_y})\n"
#       f"Расстояние между ними {math.sqrt((max_x - min_x)**2 + (max_y - min_y)**2)}")

# Дан массив упорядоченный по возрастанию. Вставить число r, не использую insert() и sort()

length = int(input("Введите длину массива: "))
a = [3, 6, 4, 7, 8, 45]
r = int(input())
a += [r]
i = -1
if a[i] < a[i - 1]:
    a[i], a[i - 1] = a[i - 1], a[i]
    i -= 1
    while abs(i) != length and a[i] < a[i - 1]:
        a[i], a[i - 1] = a[i - 1], a[i]
print(a)



