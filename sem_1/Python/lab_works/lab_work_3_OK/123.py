# while ((number := int(input())) > 0):
#     print(f"print({number})")

# a = 0.1
# b = 0.2
# DELTA = 1e-8
# if abs(0.3 - a - b) < DELTA:
# 	print("ok")
# else:
# 	print("no")

# x = float(input())
# eps = float(input())
#
# el = 1 / x
# s = el

# i = 1
#while abs (el) > eps:
# 	i += 1
# 	el = 1 / (x**i)
# 	s += el

# # хороший пример
# while abs(el) > eps:
# 	el /= x
# 	s += el
# print(s)

# import time
# i = 1
# while True:
#     time.sleep(i**2)
#     print(i**2)
#     i += 1

x = float(input())
eps = float(input())

el = 1 / x
s = el

# i = 1
#while abs (el) > eps:
# 	i += 1
# 	el = 1 / (x**i)
# 	s += el

# хороший пример
while abs(el) > eps:
	el /= x
	s += el
print(s)