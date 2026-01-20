# a = 12.1 + 0.2
# print(a)
#
# print(f"{a:f}")
# print(f"{a:7.3f}") #
# print(f"{a:>10.3f}") # выравнивание вправо
# print(f"{a:<10.3f}") # выравнивение влево
# print(f"{a:^10.3f}") # выравнивание по центру
# print(f"{a:-^10.3f}") # заполняем пробелы знаком -
# print(f"{a:e}") # делаем вывод с e в степени
# print(f"{a:g}") # форматирование по g
# print(f"{a:>+10.3e}") # здесь + выводит знак
#

a = [1, 2, 3]
b = a
c = [1, 2, 3]

# сравниевает содержание
print("a == b: ", a == b)
print("b == c: ", b == c)
print("a == c: ", a == c, '\n')

# сравниевает id
print("a id b: ", a is b)
print("b id c: ", b is c)
print("a id c: ", a is c, "\n")

print(id(a))
print(id(b))
print(id(c))