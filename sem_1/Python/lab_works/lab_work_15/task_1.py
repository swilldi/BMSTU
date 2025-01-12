from bin_file_func import *
import os

"""
удаляем отрицательные элементы
"""

# выбираем файл для работы и заполняем его
# file = chose_bin_file()
# fill_file(file)

# # можем не пытаться что-то вводить, а просто сгенерировать содержимое файла
file = "test_task_1.bin"
generate_bin_number(file, 10)

positive_count = 0
file_size = os.path.getsize(file)
element_count = file_size // step

# выводим файл до обработки
print("Файл до:")
print_file(file)
print()

with open(file, "rb+") as f:
    # проходим по всем элементам
    for i in range(0, file_size, step):
        # переходим на i-ю строку и считываем число
        f.seek(i, 0)
        num_code = f.read(step)
        num = unpack(FMT, num_code)[0]
        if num >= 0:
            # переходим на строку
            f.seek(positive_count, 0)
            positive_count += step
            f.write(num_code)
    f.seek(positive_count)
    f.truncate()

# выводим файл после обработки
print("Файл после:")
print_file(file)


