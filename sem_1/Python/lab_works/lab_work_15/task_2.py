from struct import unpack, calcsize
from bin_file_func import *
import os

"""
После каждого нечетного числа вставляем его удвоенное значение
"""

# выбираем файл для работы и заполняем его
# file = chose_bin_file()
# fill_file(file)

# # можем не пытаться что-то вводить, а просто сгенерировать содержимое файла
file = "test_task_2.bin"
generate_bin_number(file, 5)

file_size = os.path.getsize(file)
element_count = file_size // step
odd_num_count = 0

# выводим файл до обработки
print("Файл до:")
print_file(file)
print()

with open(file, "rb") as f:
    # f.seek(-step, 2)
    ind = 0
    while ind < file_size:
        num = unpack(FMT, f.read(step))[0]
        if abs(num) % 2 != 0:
            odd_num_count += 1
        ind += step
        # f.seek(-step, 1)

# print(odd_num_count)

with open(file, "rb+") as f:
    new_ind = step * (element_count + odd_num_count - 1)
    for ind in range(file_size - step, -1, -step):
        f.seek(ind)
        num = unpack(FMT, f.read(step))[0]
        # число не четное
        if abs(num) % 2 != 0:
            # вписываем удвоенное число на новое место
            f.seek(new_ind)
            f.write(pack(FMT, num * 2))
            new_ind -= step

            # вписываем исходное число на новое место
            f.seek(new_ind)
            f.write(pack(FMT, num))
        else:
            # вписываем число на новое место
            f.seek(new_ind)
            f.write(pack(FMT, num))
        new_ind -= step

# выводим файл после обработки
print("Файл после:")
print_file(file)



