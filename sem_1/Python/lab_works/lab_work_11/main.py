# Дудырев Дмитрий ИУ7-12Б
# Демонстрация скорости работы и количество операций требуемых для сортировки методом Шелла
# Изначально выводится информация об используемых списках: диапазон значений, длина
# Генерируется список, выводиться список, происходит сортировка методом Шелла и снова выводится список
# Происходит генерация 3 массивов, записанных в виде: упорядоченный, исходный, упорядоченный в обратном порядке
# Сортировка каждого списка методом Шелла, замер количества операция и времения работы алгоритма
# Вывод таблицы результатов
import random


# Функция замеряет время работы функции переданной в качестве аргумента
def time_to_work(func):
    def action(data):
        from time import time
        start = time()
        operations_count = func(data)
        end = time()
        return end - start, operations_count

    return action


# Сортировка методом Шелла, обернутая в декоратор для замера времени работы
@time_to_work
def shell_sort(arr):
    # определение шага
    step = len(arr) // 2
    operations_count = 0
    while step:
        for i, el in enumerate(arr):
            while i >= step and arr[i - step] > el:
                arr[i] = arr[i - step]
                i -= step
                operations_count += 1
            arr[i] = el
        step //= 2
    return operations_count


# Функция для вывода итогово результата в виде таблицы
def print_result(data: list[dict]):
    cols_count = 6
    width_cell = 20
    row_name_size = 20
    row_ind = 0
    horizontal_border = "\n", "-" * (row_name_size + (width_cell + 1) * cols_count)

    # Отступ первой колонки
    print(" " * row_name_size + "|", end="")
    # вывод заголовков с номерами массивов
    for i in range(3):
        print(f"{f"Массив {i + 1}":^{width_cell * 2 + 1}}|", end="")
    print(*horizontal_border)
    # Отступ первой колонки
    print(" " * row_name_size + "|", end="")
    # Вывод под заголовков колонок
    for _ in range(3):
        print(f"{"время":^{width_cell}}|{"перестановки":^{width_cell}}|", end="")
    print(*horizontal_border)

    # Вывод таблицы с результатами
    for j in range(3):
        # Выбор типа исходного списка в зависимости от номера строки
        match row_ind:
            # Упорядоченный список
            case 0:
                row_name = (f"{"Упорядоченный":^{row_name_size}}|" + f"{"|":>{width_cell + 1}}" * cols_count,
                            f"\n{"список":^{row_name_size}}|")
                list_type = "sort"
                row_ind += 1
            # Случайный список
            case 1:
                row_name = (f"{"Случайный":^{row_name_size}}|" + f"{"|":>{width_cell + 1}}" * cols_count,
                            f"\n{"список":^{row_name_size}}|")
                list_type = "rand"
                row_ind += 1
            # Упорядоченный в обратном порядке списко
            case 2:
                row_name = (f"{"Упорядоченный":^{row_name_size}}|" + f"{"|":>{width_cell + 1}}" * cols_count,
                            f"\n{"в обратном порядке":^{row_name_size}}|")
                list_type = "rev_sort"
        print(*row_name, end="")

        for i in range(3):
            time, operations_count = data[i][list_type]
            print(f"{time:^{width_cell}g}|{operations_count:^{width_cell}g}|", end="")
        print(*horizontal_border)


# Вывод списка. Принимает список, тип печати и название
def print_list(data: list, type_print: str = "h", title=None):
    if title is not None:
        print(title)
    if type_print == "v":
        for ind, el in enumerate(data):
            print(f"Элемент [{ind + 1}]: {el}", end="\n")
    elif type_print == "h":
        print("|", end="")
        for el in data:
            print(f" {el} |", end="")
        print()


def input_list() -> list:
    length_list = input_size("Введите размер списка: ")
    data = [0] * length_list
    for i in range(length_list):
        while True:
            try:
                num = float(input(f"Введите {i + 1} элемент: "))
            except:
                print("У нас тут только числа")
            else:
                break
        data[i] = num
    return data


def input_size(msg: str) -> int:
    while True:
        try:
            size = int(input(msg))
        except ValueError:
            print("Длина – это целое число")
        else:
            break
    return size


# Ввод списка и вывод изначального и отсортированного, для демонстрации работы алгоритма
numbers = input_list()
print_list(numbers, title="Изначальный список:")
shell_sort(numbers)
print_list(numbers, title="Отсортированный список:")
print()

statistic = [dict() for _ in range(3)]
for j in range(3):
    # Ввод списка
    length_list = input_size(f"Введите размер списка {j + 1}: ")
    numbers = random.choices(range(1, 1000), k=length_list)

    # Запоминание исходного, отсортированного, отсортированного в обратном порядке
    statistic[j]["sort"] = shell_sort(sorted(numbers))
    statistic[j]["rand"] = shell_sort(numbers)
    statistic[j]["rev_sort"] = shell_sort(sorted(numbers, reverse=True))

print_result(statistic)
