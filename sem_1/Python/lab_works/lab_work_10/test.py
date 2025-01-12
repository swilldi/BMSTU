# def a(f):
#     c = 1
#     print("c =", c)
#     def v(a, b):
#         nonlocal c
#         c += b
#         print("c =", c)
#         res = f(a, c)
#         return res
#     return v
#
# @a
# def b(a, b):
#     res = a + b
#     return res
#
#
