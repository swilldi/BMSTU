"""
Задачи:
1) Арифметика: отрицательные числа
2) Слова именно слова заменяем
3) Выводы сообщений пользователю
"""


class NotInRange(Exception):
    def __init__(self, number):
        self.number = number

    def __str__(self):
        return f"Число {self.number} не является управляющим."


def find_word_indexes(line, find_word):
    """Ищет индексы вхождения слова в строке """
    import string
    word = ""
    start_ind = end_ind = None
    indexes = []
    # проходим по строке
    for j in range(len(line)):
        # print(word)
        # если символ пробел или знак припинание – окончание/начало слова
        if line[j].isspace() or line[j] in string.punctuation:
            end_ind = j
            if word == find_word:
                indexes.append((start_ind, end_ind))
            word = ""
            start_ind = end_ind = None
        # иначе – буква и записываем
        else:
            word += line[j]
            if start_ind is None:
                start_ind = j
    # проверяем последнее записанное слово
    else:
        if word == find_word:
            end_ind = j

    if end_ind is not None:
        indexes.append((start_ind, end_ind))


def input_command() -> str:
    """Ввод команды"""
    while True:
        command = input("Введите номер команды: ").lower()

        # команда относиться к именным
        if command in ["help", "h", "show", "hide", "print", "p"]:
            return command
        # попытка перевести в число
        try:
            command = int(command)
            if command > 7:
                raise NotInRange(command)
        except ValueError:
            # над текстом подумай =) много где
            print("Команда не распознана.")
        except NotInRange:
            print(NotInRange)
        else:
            return str(command)


def print_menu():
    """Выводит список функций текстового процессора и их номера для ввода команд"""
    print("\nВывести: \"p\" или \"print\" для вывода текста",
          "1. Выровнять текст по левому краю.",
          "2. Выровнять текст по правому краю.",
          "3. Выровнять текст по ширине.",
          "4. Удаление всех вхождений заданного слова.",
          "5. Замена одного слова другим во всём тексте.",
          "6. Вычисление арифметических выражений над целыми числами внутри текста",
          "7. Найти, вывести и затем удалить специальное предложение (h/help для подробностей)",
          "0. Завершить программу", sep="\n", end="\n\n")


def print_help():
    """Выводит сообщение пользователю о том, как пользоваться программой"""
    print("\nДля выполнения команд выводимой в меню необходимо ввести её номер",
          "Например для выравнивания текста по ширине нужно ввести \"3\"",
          "Текстовые команды:",
          "h / help – выводит данное сообщение с краткой информацией об использовании программы",
          "p / print – выводит текс с примененным форматированием",
          "show – показывает меню (стоит по умолчанию)",
          "hide – скрывает меню",
          "Специальная строка – строка количество слов, содержащих каждую букву 2 и более раз, максимально",
          sep="\n", end="\n\n")


def find_longest_string(text) -> int:
    """ищет максимальную строку в тексте"""
    max_length = 0
    for line in text:
        max_length = max(max_length, len(line))
    return max_length


def print_text(text):
    """Вывод текста"""
    for line in text:
        print(line)
    print()


def alignment_left(text):
    """Выравнавние текста по левому краю"""
    text_size = len(text)
    for i in range(text_size):
        first_not_space = 0
        text[i] = " ".join(text[i].split())
        # первый не пробельный символ
        for j in range(len(text[i])):
            if text[i][j] != " ":
                first_not_space = j
                break
        text[i] = text[i][first_not_space:]


def alignment_right(text):
    """Выравнивание по правому краю, относительно наибольшей строки"""

    # увеличиваем длину всех строк до максимальной длины
    # дополняя пробелами слева
    text_size = len(text)
    max_row_length = find_longest_string(text)
    for i in range(text_size):
        text[i] = " ".join(text[i].split())
        text[i] = " " * (max_row_length - len(text[i])) + text[i]


def alignment_width(text):
    """Выравнивание по ширине относительно наибольшей строки"""
    text_size = len(text)
    max_row_length = find_longest_string(text)
    for i in range(text_size):
        row = text[i].strip()
        delta_length = max_row_length - len(row)
        row = row.split(" ")
        # разница длину данной строки максимальной
        word_count = len(row)
        if word_count == 1:
            continue

        # целое от деления и остаток от деления дельты длины на кол-во промежутков м/у слов
        space_between_words, space_remains = divmod(delta_length, word_count - 1)
        text[i] = ""
        for j in range(word_count - 1):
            if j < space_remains:
                text[i] += row[j] + " " * (space_between_words + 2)
            else:
                text[i] += row[j] + " " * (space_between_words + 1)
        else:
            text[i] += row[j + 1]


def remove_word(text, delete_word: str):
    """Удаление всех вхождений переданного аргумента во всем тексте"""
    # уменьшение
    replace_word(text, delete_word, "")


def replace_word(text, old: str, new: str):
    """Замена слова old на new во всем тексте"""
    import string

    text_size = len(text)

    for i in range(text_size):
        line = text[i]
        word = ""
        start_ind = None
        indexes = []
        # выполняем поиск индексов начала и конца старых слов
        for j in range(len(line)):
            # print(word)
            # символ – пробел или знак, значит слово закончилось
            if line[j].isspace() or line[j] in string.punctuation:
                if word.upper() == old.upper():
                    indexes.append((start_ind, j))
                word = ""
                start_ind = None
            # иначе заполняем
            else:
                word += line[j]
                if start_ind is None:
                    start_ind = j


        # собираем новую строку в которой заменяем старые слова на новые
        new_line = ""
        last_ind = 0
        for start_end in indexes:
            start = start_end[0]
            new_line += line[last_ind:start] + new
            last_ind = start_end[1]
        else:
            new_line += line[last_ind:]
            text[i] = new_line


def calculate(text):
    """
    Находит в тексте операции вычитания и деления, выполняет и
    заменят в тексте выражения на их результат
    """
    import string

    def solve_expression(expression: str):
        """считает значение выражения из строки"""
        result = None
        # если в выражении и вычитание и деление
        if "-" in expression and "/" in expression:
            sign = 0
            ind = 0
            expression = expression.split("-")
            len_expression = len(expression)
            divide_result = 0
            while ind < len_expression:
                element = expression[ind]
                if not element:
                    sign = (sign + 1) % 2
                elif result is None and "/" not in element:
                    result = int(element) * (-1) ** sign
                elif "/" in element:
                    while ind + 1 < len_expression and expression[ind][-1] == "/":
                        element += expression[ind + 1]
                        sign = (sign + 1) % 2
                        ind += 1

                    element = element.split("/")
                    divide_result = int(element[0]) * (-1) ** sign
                    for divider in element[1:]:
                        if divider == "0":
                            return "Error"
                        divide_result /= int(divider)


                    if result is None:
                        result = divide_result
                        divide_result = 0
                    else:
                        result -= divide_result
                else:
                    if divide_result:
                        result -= divide_result
                        divide_result = 0
                    result -= int(element)

                ind += 1
        # если в выражении только деление
        elif "/" in expression:
            expression = expression.split("/")
            result = int(expression[0])

            for num in expression[1:]:
                if num == "0":
                    return "Error"
                result /= int(num)

        # если в выражении только вычитание
        else:
            expression = expression.split("-")
            sign = 0
            result = None
            start = None
            for i in range(len(expression)):
                el = expression[i]
                if not el:
                    sign = (sign + 1) % 2
                else:
                    result = int(el) * (-1)**sign
                    start = i
                    break


            for num in expression[start+1:]:
                if not num:
                    sign = (sign + 1) % 2
                else:
                    result -= int(num) * (-1) ** sign

        return f"{result:.3g}"

    for i in range(len(text)):
        line = text[i]
        line_length = len(line)
        ind = 0
        all_expression = []
        current_expression = ""
        start_ind, end_ind = 0, 0
        wasSpace = False
        while ind < line_length:
            symbol = line[ind]
            # символ операции
            if symbol in "/-":
                # новый флаг правильной записи
                if current_expression and current_expression[-1].isdigit():
                    end_ind = ind

                if symbol == "-":
                    current_expression += symbol
                elif symbol == "/" and current_expression and current_expression[-1] != "/":
                    current_expression += symbol
                else:
                    if current_expression and ("-" in current_expression or "/" in current_expression):
                        # all_expression.append((current_expression[:-1], start_ind, end_ind))
                        all_expression.append((current_expression, start_ind, end_ind))

                    current_expression = ""

            # символ – пробел
            elif symbol.isspace():
                if current_expression and current_expression[-1].isdigit():
                    end_ind = ind
                    wasSpace = True
                else:
                    wasSpace = False
            # символ число
            elif symbol.isdigit():
                # если начинается новое выражение
                if not current_expression:
                    start_ind = ind
                # если м/у числами пробел – новое выражение
                if wasSpace:
                    if current_expression and ("-" in current_expression or "/" in current_expression)\
                            and len(current_expression) >= 3:
                        all_expression.append((current_expression, start_ind, end_ind))
                    start_ind = ind
                    current_expression = symbol
                else:
                    current_expression += symbol
            # все остальное (не числа, не операции)
            else:
                if current_expression and ("-" in current_expression or "/" in current_expression)\
                        and len(current_expression) >= 3:
                    all_expression.append((current_expression, start_ind, end_ind))
                current_expression = ""

            ind += 1
        else:
            # обработка последней операции
            if current_expression and current_expression[-1].isdigit() and \
                    ("-" in current_expression or "/" in current_expression) and len(current_expression) >= 3:
                all_expression.append((current_expression, start_ind, ind))


        # формируем новую строку с заменой выражения на значение выражения
        new_line = ""
        last_ind = 0
        for el in all_expression:
            new_line += line[last_ind:el[1]] + solve_expression(el[0])
            last_ind = el[-1]
        else:
            new_line += line[last_ind:]
        text[i] = new_line




def remove_special_row(text):
    """
    Ищет, выводит и удаляет из текста предложение, в котором количество слов, содержащих каждую букву 2 и более
    раз, максимально
    """
    import string

    good_word_count = 0
    result = {"start_ind": 0, "end_ind": 0, "start_row": 0, "end_row": 0, "max_good_word": 0}
    last_point = 0
    for row_index in range(len(text)):
        line = text[row_index]
        letters_word = dict()
        for i in range(len(line)):
            symbol = line[i]
            # если точка, значит закончилось предложение
            if symbol in ".?!":
                # проверка последнего слова предложения
                if letters_word and all(x >= 2 for x in letters_word.values()):
                    good_word_count += 1

                # если хороши слов больше сохраняем информацию по последнем предложении
                if good_word_count > result["max_good_word"]:
                    result = {"start_ind": last_point,
                              "end_ind": i + 1,
                              "start_row": result["end_row"],
                              "end_row": row_index,
                              "max_good_word": good_word_count
                              }
                good_word_count = 0
                # создаем новый словарь кол-ва букв
                letters_word = dict()
                last_point = i

            # если пунктуационный символ, то игнорируем
            elif symbol in string.punctuation:
                continue
            # если пробел, значит слово закончилось
            elif symbol.isspace():
                # проверяем удов-ет ли слово условию
                if letters_word and all(x >= 2 for x in letters_word.values()):
                    good_word_count += 1
                # создаем новый словарь кол-ва букв
                letters_word = dict()
            # в противном случае буква, значит считаем количество
            elif symbol.isalpha():
                # если есть в словаре
                if symbol in letters_word:
                    letters_word[symbol] += 1
                else:
                    letters_word[symbol] = 1

        # проверка последнего слова в строке
        if letters_word and all(x >= 2 for x in letters_word.values()):
            good_word_count += 1
        # создаем новый словарь кол-ва букв
        letters_word = dict()

    # выводим словарь с крайними значениями предложения
    # print(result)

    # форматируем исходный текст
    deleted_row = 0
    if result["start_ind"] + 1 < len(text[result["start_row"]]):
        if result["start_ind"] != 0:
            result["start_ind"] += 1
        deleted_sentence = text[result["start_row"]][result["start_ind"]:] + " "
    else:
        deleted_sentence = ""
    # сокращаем первую строку
    text[result["start_row"]] = text[result["start_row"]][:result["start_ind"]]
    for i in range(result["start_row"] + 1, result["end_row"]):
        deleted_sentence += text.pop(i - deleted_row) + " "
        deleted_row += 1
    deleted_sentence += text[result["end_row"] - deleted_row][:result["end_ind"] + 1]
    text[result["end_row"] - deleted_row] = text[result["end_row"] - deleted_row][result["end_ind"]:]

    if deleted_sentence:
        print("Удалено следующее предложение:", deleted_sentence, sep="\n")
    else:
        print("Предложение удовлетворяющее условию нет")
