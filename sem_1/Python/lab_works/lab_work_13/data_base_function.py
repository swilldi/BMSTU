from os import makedirs

# Структура: название фильма; год выхода; оценка
FIELD_NAME = 0
FIELD_YEAR = 1
FIELD_SCORE = 2

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

def input_int(input_msg, err_msg=None) -> int:
    """Ввод целого числа"""
    while True:
        try:
            num = int(input(input_msg).strip())
            if num < 0:
                raise NegativeValue(num)
        except ValueError:
            if err_msg is None:
                err_msg = "Необходимо ввести целое число"
            print(err_msg)
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
    print("Для использования абсолютного пути обязательно добавьте / в начале, "
          "иначе будет создан путь в папке с программой")
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
            value = str(input_int("Введите год выпуска: "))
        case 3:
            value = str(input_int("Введите оценку: "))
    return field_num - 1, value

def input_data() -> (str, str, str):
    film_name = input("Введите название фильма: ").strip().replace(";", " ")
    year_release = str(input_int("Введите год выпуска фильма: ")).replace(";", " ")
    film_score = str(input_int("Введите оценку фильма: ")).replace(";", " ")
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
    with open(f"{database}", "w") as f:
        for i in range(rows_count):
            console_clear()
            print(f"Ввод {i+1}-й/{rows_count} строки")
            data = input_data()
            f.write(f"{data[0].strip()};{data[1].strip()};{data[2].strip()}\n")

def print_database(file_path:str):
    """Вывести содержимое базы данных"""
    print(f"{'Название фильма':<30} {'Год':<10} {'Оценка':<10}")
    print("-" * 50)
    with open(f"{file_path}", "r") as f:
        f.seek(0)
        line = f.readline().strip().split(';')
        while len(line) == 3:
            print(f"{line[0]:<30} {line[1]:<10} {line[2]:<10}")
            line = f.readline().strip().split(';')
    print("-" * 50)

def add_database(file_path, data):
    """Добавить запись в конец базы данных"""
    import os

    # проверка на возможность изменять файл
    if not os.access(file_path, os.W_OK):
        print("Нет прав на запись")
        return

    with open(f"{file_path}", "a") as f:
        f.write(f"{data[0].strip()};{data[1].strip()};{data[2].strip()}\n")
    print(f"Добавлено в базу данных: {" ".join(data)}")


def search_database(file_path, field_1, field_2=None):
    """Поиск по одному или двум полям"""
    def make_check(line, field):
        """Строгое сравнение данных"""
        t, value = field
        return value == line[t].strip()

    def check_line(line):
        """Проверка одного или двух полей"""
        if field_2 is None:
            # рассматриваем тип и значение первого поля
            return make_check(line, field_1)
        else:
            return make_check(line, field_1) and make_check(line, field_2)

    def print_field(field):
        """вывод информации о поле"""
        if field is None:
            return "\n"

        if field[0] == FIELD_NAME:
            msg = "Название фильма: "
        elif field[0] == FIELD_YEAR:
            msg = "Год выпуска фильма: "
        elif field[0] == FIELD_SCORE:
            msg = "Оценка фильма: "
        return msg + str(field[1]) + "\n"

    console_clear()
    print(f"{print_field(field_1)}{print_field(field_2)}Найденые данные:")

    with open(f"{file_path}") as f:
        print(f"{'Название фильма':<30} {'Год':<10} {'Оценка':<10}")
        print("-" * 50)
        f.seek(0)
        while line := f.readline():
            # print(line.split(";"))
            # проверка строки на соответствие условию
            data = line.strip().split(";")
            if check_line(data):
                print(f"{data[0]:<30} {data[1]:<10} {data[2]:<10}")
        print("-" * 50)


