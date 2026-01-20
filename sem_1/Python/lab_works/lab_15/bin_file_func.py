from struct import pack, unpack, calcsize
from random import randint


class NegativeValue(Exception):
    def __init__(self, num):
        self.num = num
    def __str__(self):
        return f"Число {self.num} отрицательное"

class NumberNotInRange(Exception):
    def __init__(self, num):
        self.num = num
    def __str__(self):
        return f"Число {self.num} не входит в диапазон 32-х битных чисел"

FMT = "i"
step = calcsize(FMT)

def generate_bin_number(file: str, n: int, /, negative: bool =True):
    with open(file, "wb+") as f:
        for _ in range(n):
            if negative:
                num = randint(-10**2, 10**2)
            else:
                num = randint(1, 10**2)
            f.write(pack(FMT, num))


            # f.write(pack(FMT, 100))
            # f.write(pack(FMT, -100))


def print_file(file):
    with open(file, "rb") as f:
        while el_code := f.read(step):
            print(unpack(FMT, el_code)[0])


def input_int(msg: str = "Введите целое число: ", /,only_positive: bool = False):
    """Ввод целого положительного числа"""
    while True:
        try:
            num = int(input(msg))
            if num < 0 and only_positive:
                raise NegativeValue(num)
            elif not (-2147483648 <= num <= 2147483647):
                raise NumberNotInRange(num)
        except ValueError:
            print("Число должно быть целым")
        except NumberNotInRange as e:
            print(e)
        except NegativeValue as e:
            print(e)
        else:
            return num


def chose_bin_file():
    import os
    while True:
        file_path = input("Введите путь к файлу: ")

        # Обработка пути указанного к файлу
        if os.path.isdir(file_path):
            print("Введен не файл")
            continue
        # Файл существует
        elif os.path.isfile(file_path):
            # есть права на чтение и запись
            if os.access(file_path, os.W_OK) and os.access(file_path, os.R_OK):
                return file_path
            else:
                print("Нет прав на чтение и запись файла")
                continue
        else:
            folders = os.path.dirname(file_path)
            if folders:
                os.makedirs(folders, exist_ok=True)
            # создаем или очищаем выбранный файл
            open(file_path, "wb").close()
            return file_path





def fill_file(file_path: str):
    """Заполняет переданный файл цеыими числами"""
    element_count = input_int("Введите количество чисел: ", only_positive=True)
    with open(file_path, "wb") as f:
        for i in range(element_count):
            num = input_int(f"Введите {i+1} элемент: ")
            f.write(pack(FMT, num))