import struct
from os import makedirs, path
from struct_function import *

# Структура: название фильма; год выхода; оценка
FIELD_NAME = 0
FIELD_YEAR = 1
FIELD_SCORE = 2
DATA_BITE = 60

class NotFieldNumber(Exception):
    def __init__(self, number):
        self.number = number

    def __str__(self):
        return f"Число {self.number} не привязано ни к одному полю"

class NegativeValue(Exception):
    def __init__(self, number):
        self.number = number

    def __str__(self):
        return f"Число {self.number} меньше нуля"

class NotInRange(Exception):
    def __init__(self):
        self.num = numpy

    def __str__(self):
        return f"Число {self.num} число по модулю больше 2147483647"

def input_int(input_msg, /, err_msg=None) -> int:
    """Ввод целого числа"""
    while True:
        try:
            num = int(input(input_msg).strip())
            if num < 0:
                raise NegativeValue(num)
            if abs(num) > 2147483647:
                raise NotInRange(num)
        except ValueError:
            if err_msg is None:
                err_msg = "Необходимо ввести целое число"
            print(err_msg)
        except NotInRange as e:
            print(e)
        except NegativeValue as e:
            print(e)
        else:
            return num

def console_clear():
    """Очистка консоли"""
    import os
    os.system("clear")

def choice_file() -> str:
    """Выбрать файл для работы"""
    import os
    full_path = input("Введите путь к файлу: ")
    # if full_path
    path = os.path.dirname(full_path)
    # создаем папки для указанного пути
    if path:
        os.makedirs(path, exist_ok=True)

    # проверка на возможность чтения

    if os.path.isfile(full_path):
        if not os.access(full_path, os.R_OK):
            print("Нет права на чтение")
            return None
        print(f"Выбран файл {full_path}")
        return full_path
    elif os.path.isdir(full_path):
        print("Введена папка")
        return None
    else:
        open(full_path, "w").close()
        print(f"Создан файл {full_path}")
        return full_path

def choice_field() -> (int, str):
    "выбор поля базы данных для поиска"
    print("1. Название фильма\n2. Год выпуска\n3. Оценка")
    while True:
        try:
            field_num = int(input("Введите номер поля: "))
            if 1 < field_num > 3:
                raise NotFieldNumber(field_num)
        except ValueError:
            print("Необходимо ввести число")
        except NotFieldNumber as e:
            print(e)
        else:
            break

    match field_num:
        case 1:
            value = input("Введите название фильма: ")
        case 2:
            value = input_int("Введите год выпуска: ")
        case 3:
            value = input_int("Введите оценку: ")
    return field_num - 1, value

def input_data() -> (str, int, int):
    film_name = input("Введите название фильма: ").strip()
    year_release = input_int("Введите год выпуска фильма: ")
    film_score = input_int("Введите оценку фильма: ")
    return film_name, year_release, film_score

def initialize_database(database):
    """Инициализировать базу данных"""
    import os
    # проверка на возможность изменять файл (можно конечно декоратором, но ладно...)
    if not os.access(database, os.W_OK):
        print("Нет прав на запись")
        return

    rows_count = input_int("Введие количество строк базы данных: ")
    # открываем файл
    with open(f"{database}", "wb") as f:
        for i in range(rows_count):
            console_clear()
            print(f"Ввод {i+1}/{rows_count} строки")
            data = input_data()
            coded_line = code_line(data)
            f.write(coded_line)

def print_database(file_path:str, show_line_number=False):
    """Вывести содержимое базы данных"""
    print(" " * 6 * show_line_number + f"{'Название фильма':<30} {'Год':<10} {'Оценка':<10}")
    print(" " * 6 * show_line_number + "-" * 50)
    with open(f"{file_path}", "rb") as f:
        coded_line = f.read(DATA_BITE)
        try:
            line = decode_line(coded_line)
        except struct.error:
            line = ""
        line_number = 0
        while len(line) == 3:
            if show_line_number:
                line_number += 1
                print(f"{str(line_number) + ".":^4} {line[0]:<30} {line[1]:<10} {line[2]:<10}")
            else:
                print(f"{line[0]:<30} {line[1]:<10} {line[2]:<10}")
            coded_line = f.read(DATA_BITE)
            try:
                line = decode_line(coded_line)
            except struct.error:
                line = ""

    print(" " * 6 * show_line_number + "-" * 50)

    return line_number

def add_data(file_path, new_data, ind):
    """Добавить запись в конец базы данных"""
    import os

    # проверка на возможность изменять файл
    if not os.access(file_path, os.W_OK):
        print("Нет прав на запись")
        return

    elements_count = os.path.getsize(file_path) // DATA_BITE
    if ind + 1 > elements_count:
        with open(file_path, "ab") as f:
            f.write(code_line(new_data))
    else:
        elements_count += 1
        with open(file_path, "rb+") as f:
            # выделяем место для новых данных
            f.write("".encode("utf-8"))
            for i in range(1, elements_count - ind + 1):
                f.seek(-DATA_BITE * i, 2)
                data = f.read(DATA_BITE)
                f.write(data)
            # вставляем элемент
            f.seek(DATA_BITE * ind, 0)
            f.write(code_line(new_data))

    print(f"Данные добавлены в базу данных")

def del_data(database, ind):
    # считываем файл без выбранной строки
    elements_count = path.getsize(database) // DATA_BITE
    with open(database, "rb+") as f:
        f.seek(ind * DATA_BITE, 0)
        for i in range(1, elements_count - ind):
            f.seek(DATA_BITE, 1)
            data = f.read(DATA_BITE)
            f.seek(-DATA_BITE * 2, 1)
            f.write(data)
        f.truncate()

    print("Строка удалена")

def search_database(file_path, field_1, field_2=None):
    """Поиск по одному или двум полям"""
    def make_check(line, field):
        t, value = field
        # print(line, field)
        if t == 0:
            return value == line[t].strip()
        else:
            return value == line[t]


    def check_line(line):
        if field_2 is None:
            # рассматриваем тип и значение первого поля
            return make_check(line, field_1)
        else:
            return make_check(line, field_1) and make_check(line, field_2)

    def print_field(field):
        if field is None:
            return ""

        if field[0] == FIELD_NAME:
            msg = "Название фильма содержит: "
        elif field[0] == FIELD_YEAR:
            msg = "Год выпуска фильма: "
        elif field[0] == FIELD_SCORE:
            msg = "Оценка фильма: "
        return msg + str(field[1]) + "\n"

    console_clear()
    print(f"{print_field(field_1)}{print_field(field_2)}Найденые данные:")
    print(f"{'Название фильма':<30} {'Год':<10} {'Оценка':<10}")
    print("-" * 50)
    with open(f"{file_path}", "rb") as f:
        f.seek(0)
        while line := f.read(DATA_BITE):
            # print(line.split(";"))
            line = decode_line(line)
            if check_line(line):
                print(f"{line[0]:<30} {line[1]:<10} {line[2]:<10}")
    print("-" * 50)

def code_line(data: (str, int, int), pattern="50sii") -> bytes:
    from struct import pack

    # обрезавем строку, чтобы она занимала не более 50 байт
    if len(data[0]) > 25:
        string = ""
        size = 0
        for letter in data[0]:
            if 1040 <= ord(letter) <= 1103:
                if size + 2 <= 50:
                    size += 2
                    string += letter
            elif size + 1 <= 50:
                size += 1
                string += letter
    # print(data[0])
    return pack(pattern, data[0].encode('utf-8', errors="replace"), data[1], data[2])

def decode_line(coded_data, pattern="50sii") -> (str, int, int):
    from struct import unpack
    data = unpack(pattern, coded_data)

    return data[0].decode("utf-8").strip("\00"), data[1], data[2]

