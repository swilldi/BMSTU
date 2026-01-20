import os

from data_base_function import *
from numpy.ma.core import negative


class CommandError(Exception):
    def __init__(self, number):
        self.number = number

    def __str__(self):
        return f"Число {self.number} не привязано ни к одной команде"


def print_menu():
    '''Выводит меню'''
    print(
        "1. Выбрать файла для работы\n"
        "2. Инициализировать базу данных\n"
        "3. Вывести содержимое базы данных\n"
        "4. Добавить запись в базу данных\n"
        "5. Удалить запись базы данных\n"
        "6. Поиск по одному полю\n"
        "7. Поиск по двум полям"
    )


def input_command() -> int:
    '''Ввод команды для меню'''
    while True:
        try:
            command = int(input("Введите номер команды: "))
            if 1 < command > 7:
                raise CommandError(command)
        except ValueError:
            print("Необходимо ввести число")
            return None
        except CommandError as e:
            print(e)
            return None
        else:
            return command


def wait_quit():
    '''Ожидание завершения от пользователя'''
    while True:
        n = input("Введите q, чтобы вернуться в меню: ")
        if n.lower() == "q":
            break


showMenu = True
database = None
# database = "/Users/dmitry/Documents/BMSTU/Programming/Python/lab_works/lab_work_14/new.bin"
# database = "/Users/dmitry/Documents/BMSTU/Programming/Python/lab_works/lab_work_14/database_files/films.bin"
code_pattern = "50sii"

while True:
    console_clear()
    # Выводим файл который активен
    if database is None:
        print("НЕОБХОДИМО ВЫБРАТЬ ФАЙЛ")
    else:
        print(f"Выбранный файл: {database}")
    # Выводим меню
    if showMenu:
        print_menu()
    command = input_command()

    # Была введена неверная команда
    if command is None:
        wait_quit()
        continue
    # файл не выбран
    elif database is None and command != 1:
        print("Файл не выбран")
        wait_quit()
        continue

    console_clear()
    match command:
        case 1:
            # выбор базы данных
            database = choice_file()
        case 2:
            # создание новой базы данных
            initialize_database(database)
        case 3:
            # вывод базы данных
            print_database(database)

        case 4:
            # добавление новой строки
            line_count = print_database(database, show_line_number=True)
            index = input_int("Введите индекс нового элемента: ") - 1
            data = input_data()
            
                
            add_data(database, data, index)
        case 5:
            # удаление строки
            line_count = print_database(database, show_line_number=True)
            del_index = input_int("Введите номер удаляемой строки: ") - 1
            while 1 < del_index >= line_count:
                del_index = input_int("Введите номер удаляемой строки: ")
            del_data(database, del_index)

        case 6:
            # поиск по одному полю
            print("Ввод поля:")
            field_1 = choice_field()
            search_database(database, field_1)

        case 7:
            # поиск по двум полям
            print("Ввод первого поля:")
            field_1 = choice_field()
            console_clear()
            print("Ввод второго поля:")
            field_2 = choice_field()
            console_clear()
            search_database(database, field_1, field_2)

    wait_quit()
