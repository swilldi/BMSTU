from bin_file_func import *
import os


def swap(file, element_1: (bytes, int), element_2: (bytes, int)):
    """Меняем переданные элементы местами"""
    # записываем значение второго элемента на место первого
    file.seek(element_1[1])
    file.write(element_2[0])

    # записываем значение первого элемента на место второго
    file.seek(element_2[1])
    file.write(element_1[0])

def get_element(file, ind):
    """Получаем значени элемента, его закодированную версию и расположение в файле"""
    file.seek(ind, 0)
    element = (file.read(step), ind)
    num = unpack(FMT, element[0])[0]

    return num, element


# выбираем файл для работы и заполняем его
# file = chose_bin_file()
# fill_file(file)

# # можем не пытаться что-то вводить, а просто сгенерировать содержимое файла
file = "test_task_3.bin"
generate_bin_number(file, 10)


file_size = os.path.getsize(file)
# sort_step = file_size // step // 2

# Вывод элементов файла до сортировки
print("Файл до:")
print_file(file)
print()

with open(file, "rb+") as f:
    # задаем дистанцию м/у элементами
    distance = file_size // 2
    if distance % 4 != 0:
        distance -= distance % 4

    while distance:
        for i in range(distance, file_size, step):
            while True:
                # считываем элементы
                num_1, element_1 = get_element(f, i)
                num_2, element_2 = get_element(f, i - distance)
                i += step

                # если дальний элемент меньше ближнего, то свапаем
                if num_1 < num_2:
                    swap(f, element_1, element_2)
                if i >= file_size:
                    break


        # уменьшаем дистанцию м/у элементами
        distance //= 2
        if distance % 4 != 0:
            distance -= distance % 4

    for i in range(0, file_size - step, step):
        num_1, element_1 = get_element(f, i + step)
        num_2, element_2 = get_element(f, i)
        if num_1 < num_2:
            swap(f, element_1, element_2)





# Вывод файлов после сортировки
print("Файл после:")
print_file(file)