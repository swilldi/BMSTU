import string
from random import *

# число
rn = lambda: randint(1, 20)

# длина
rl = lambda: randint(2, 6)


# список
def write_list(file, length):
    for _ in range(length):
        file.write(str(rl()) + "\n")


# матрица
def write_matrix(file, row, col=None):
    if col is None:
        col = row
    for _ in range(row):
        for __ in range(col):
            file.write(str(rn()) + "\n")


def prog_1():
    file = open("test_1.txt", "w")
    a = rl()
    b = rl()
    file.write(str(a) + "\n")
    write_list(file, a)
    file.write(str(b) + "\n")
    write_list(file, b)


def prog_2():
    file = open("test_2.txt", "w")
    l = rl()
    file.write(str(l) + "\n")
    for i in range(l):
        for j in range(l):
            file.write(str(rn()) + "\n")


def prog_3():
    file = open("test_3.txt", "w")

    col = rl()
    a = rl()
    b = rl()

    file.write(str(col) + '\n')

    file.write(str(a) + "\n")
    write_matrix(file, a, col)

    file.write(str(b) + "\n")
    write_matrix(file, b, col)


def prog_4():
    file = open("test_4.txt", "w")
    col = rn()
    row = rn()

    file.write(f"{row}\n{col}\n")
    write_matrix(file, row, col)

    l = randint(2, row)
    file.write(f"{l}\n")
    I = sample(range(1, row), k=l)
    for n in I:
        file.write(f"{n}\n")


def prog_5():
    file = open("test_5.txt", "w")
    r_a = randint(2, 4)
    c_a = randint(2, 4)
    file.write(f"{r_a}\n{c_a}\n")
    for _ in range(r_a):
        for __ in range(c_a):
            file.write(f"{randint(1, 40)}\n")

    r_b = c_a
    c_b = randint(2, 6)
    file.write(f"{r_b}\n{c_b}\n")
    for _ in range(r_b):
        for __ in range(c_b):
            file.write(f"{randint(1, 40)}\n")


def prog_6():
    file = open("test_6.txt", "w")
    r = randint(2, 10)
    c = randint(2, 10)
    file.write(f"{r}\n{c}\n")
    for i in range(r):
        for j in range(c):
            file.write(f"{choice(string.ascii_letters)}\n")


def prog_7():
    file = open("test_7.txt", "w")

    x = randint(2, 6)
    y = randint(2, 6)
    z = randint(2, 6)

    file.write(f"{x}\n{y}\n{z}\n")

    for _ in range(x):
        for __ in range(y):
            for ___ in range(z):
                file.write(f"{randint(1, 40)}\n")


option = input()
match option:
    case "1":
        prog_1()
    case "2":
        prog_2()
    case "3":
        prog_3()
    case "4":
        prog_4()
    case "5":
        prog_5()
    case "6":
        prog_6()
    case "7":
        prog_7()
    case "all":
        prog_1()
        prog_2()
        prog_3()
        prog_4()
        prog_5()
        prog_6()
        prog_7()
