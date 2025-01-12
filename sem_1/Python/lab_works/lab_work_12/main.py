from word_processor import *

ALIGN_IS_RIGHT = "right"
ALIGN_IS_LEFT = "left"
ALIGN_IS_WIDTH = "width"


isShowMenu = True
align = ""
# text = [
#         "На столе лежали 3 книги, одна изиз них",
#         "была открыта на странице 47, в углу комнаты",
#         "   стояли 8 -- 6 стула. На часах было 6:15 утра",
#         "и за окном слышались шаги, их было",
#         "не меньше 10. В комнате царила отто тишина,",
#         "нарушаемая лишь тиканием часов. Я сделал",
#         "  5/2 шагов к окну и замер."
#     ]

text = [
    "Текущая задача, словно зеркальная, требует построения фразы, в которой слова имеют повторяющиеся буквы",
    "Например, слово ‘мама’ прекрасно подходит, как и ‘тестостерон’",
    "Попробуем решить: 50 - 18 / 4 - 3 = 44. гдегде дада вычитание и деление играют главную роль",
    "Ещё пример: 144 / 12 - 8 / 0 = 10. что демонстрирует важность порядка операций",
    "Повторения создают уникальную симметрию. словно в слове 'параллелограмм'",
    "Вычисления, такие как 81 / 9 - 6 - 4 = -1, подчёркивают роль деления",
    "Арифметика добавляет точности, а слова — симметрии и красоты.",
]

while True:
    if isShowMenu:
        print_menu()
    command = input_command()

    match command:
        case "0":
            print("Спасибки, что запустил =)")
            break
        case "1":
            alignment_left(text)
            align = ALIGN_IS_LEFT
        case "2":
            alignment_right(text)
            align = ALIGN_IS_RIGHT
        case "3":
            alignment_width(text)
            align = ALIGN_IS_WIDTH
        case "4":
            word = input("Введите слово которое нужно удалить: ")
            remove_word(text, word)
        case "5":
            old = input("Введите слово, которое будет заменено: ")
            new = input("Введите на что будет заменено: ")
            replace_word(text, old, new)
        case "6":
            calculate(text)
        case "7":
            remove_special_row(text)
        case "h" | "help":
            print_help()
        case "show":
            isShowMenu = True
        case "hide":
            isShowMenu = False
        case "p" | "print":
            print_text(text)


    if align == ALIGN_IS_LEFT:
        alignment_left(text)
    elif align == ALIGN_IS_RIGHT:
        alignment_right(text)
    elif align == ALIGN_IS_WIDTH:
        alignment_width(text)



