from struct import pack, unpack, calcsize
import os

def isPrimeNum(num):
    """проверка простое ли число"""
    import math
    
    if num == 0 or num == 1:
        return False
    
    for divider in range(2, int(math.sqrt(num)) + 1):
        if num % divider == 0:
            return False
    return True

def print_bin(file):
    """вывод бинарного файла"""
    with open(file, "rb") as f:
        while line := f.read(size):
            num = unpack(FMT, line)[0]
            print(num)


FMT = "i"
size = calcsize(FMT)
# file = input("Введите файл: ")
file = "numbers.bin"


# Ввод базы данных
element_count = int(input("Введите кол-во элементов: "))
with open(file, "wb") as f:
    for i in range(element_count):
        num = int(input(f"Введите {i + 1} число: "))
        f.write(pack(FMT, num))

print("Файл до:")
print_bin(file)
# удаление простых чисел
element_count = os.path.getsize(file)
prime_num_count = 0
with open(file, "rb+") as f:
    for i in range(0, element_count, size):
        f.seek(i)
        num = unpack(FMT, f.read(size))[0]
        if not isPrimeNum(num):
            f.seek(prime_num_count)
            f.write(pack(FMT, num))
            prime_num_count += size
    f.seek(prime_num_count)
    f.truncate()

print("\nФайл после:")
print_bin(file)

# 67 71 73 79 83 89 97 101


