import tkinter as tk
from tkinter import messagebox
from tkinter import font
from re import compile, search
from main import *


def click_menu_about():
    """Функция вызывает информационное окно"""
    # print("click about")
    messagebox.showinfo(title="About", message="ООО \"ЛучшиеКалькуляторыВВидеПо\"\nДудырев Дмитрий ИУ7-22Б")


def click_menu_info():
    msg = """
    Clear: 
        Expression - очистить выражение
        Result - очистить результат
        All - очистить всё
    
    = - получить значение выражения
    """
    messagebox.showinfo(title="Info", message=msg)


def del_last():
    """Функция удаляет последний введенный символ выражения"""
    # удаляй сразу с пробелом
    exp = expression.get()
    match len(exp):
        case 0:
            return
        case 1:
            expression.set("")
        case _:
            if exp[-2] == " " or exp[-1] == " ":
                expression.set(exp[:-2])
            else:
                expression.set(exp[:-1])


def add_expression(get_digit):
    """Добавляет к выражению символ"""
    expression.set(expression.get() + get_digit)

def clear_all():
    """Очищает меню выражения и результата"""
    expression.set("")
    result.set("")

def check_expression(*args):
    """Проверяет правильность введенного выражения"""
    exp = expression.get().strip()
    if not exp:
        return

    correct_symbols = {"0", "1", "2", "3", "-", "+", " ", "."}
    if set(exp) - correct_symbols or not exp[-1].isdigit() or search(PATTERN_BAD_PART_1, exp) or search(PATTERN_BAD_PART_2, exp):
        result.set("Выражение не корректное")
        correct_expression.set(False)
    else:
        result.set("")
        correct_expression.set(True)


def solve_expression():
    """выполняет вычисления и задает новое значение в поле Result """
    if not correct_expression.get():
        return

    cur_result = 0
    minus = False
    number = ""
    for symbol in expression.get():
        if symbol == "-":
            if number:
                cur_result += converter_to_10(number) * (-1 if minus else 1)
                number = ""
            minus = False if minus else True
        elif symbol.isdigit() or symbol == ".":
            number += symbol
        elif number:
            cur_result += converter_to_10(number) * (-1 if minus else 1)
            number = ""
            minus = False

    if number:
        cur_result += converter_to_10(number) * (-1 if minus else 1)

    result.set(converter_from_10(cur_result, 4))

# шаблок характеристики расположения кнопок
SPEC = {
    "ipadx": 60,
    "ipady": 40,
    "pady": 0,
    "padx": 0,
    "sticky": "nsew"
}

# характеристики расположения кнопок очистки
SPEC_CLEAR = SPEC.copy()
SPEC_CLEAR.update((
    ("ipadx", 0),
    ("ipady", 10)
))

# характеристики расположения кнопок знака сложения и вычитания
SPEC_SIGN = SPEC.copy()
SPEC_SIGN.update((
    ("ipadx", SPEC["ipadx"] * 2),
    ("ipady", SPEC["ipady"]),
    ("columnspan",2)
))

# характеристики расположения кнопки подсчета выражения
SPEC_EQUAL = SPEC.copy()
SPEC_EQUAL.update((
    ("ipadx", SPEC["ipadx"]),
    ("ipady", SPEC["ipady"] * 2 + SPEC["pady"]),
    ("rowspan",2)
))

PATTERN_BAD_PART_1 = compile(r'[^0-3]\.[0-3]*')
PATTERN_BAD_PART_2 = compile(r'[0-3]*\.[0-3]+\.]')


# создаем окно, задаем его размеры и отключаем изменение размера
window = tk.Tk()
window.geometry("800x800")
window.title("Калькулятор")
window.option_add("*tearOff", tk.FALSE)
window.resizable(False, False)

# характеристики кнопок с числами и выражениями
FUNC_BUTTON_STYLE = {
    "font": font.Font(size=20)
}

# создаем переменные для арифметического выражения, результата выражения и значения
# корректности введенного выражения
expression = tk.StringVar()
result = tk.StringVar()
correct_expression = tk.BooleanVar(value=True)

# задаем сетку в окне
for col in range(4):
    window.columnconfigure(index=col, weight=1)
for row in range(6):
    window.columnconfigure(index=row, weight=1)


# Установка заголовков полей ввода и вывода
tk.Label(text="Expression:").grid(row=0, column=0)
tk.Label(text="Result:").grid(row=1, column=0)
tk.Label(text="Clear:").grid(row=2, column=0)


# Установка кнопок для очистки полей
tk.Button(text="Expression", command=lambda: expression.set("")).grid(row=2, column=1, **SPEC_CLEAR)
tk.Button(text="Result", command=lambda: result.set("")).grid(row=2, column=2, **SPEC_CLEAR)
tk.Button(text="All", command=clear_all).grid(row=2, column=3, **SPEC_CLEAR)


# Установка кнопок для ввода чисел
tk.Button(text="0", command=lambda: add_expression("0"), **FUNC_BUTTON_STYLE).grid(row=6, column=1, **SPEC)
tk.Button(text="1", command=lambda: add_expression("1"), **FUNC_BUTTON_STYLE).grid(row=5, column=0, **SPEC)
tk.Button(text="2", command=lambda: add_expression("2"), **FUNC_BUTTON_STYLE).grid(row=5, column=1, **SPEC)
tk.Button(text="3", command=lambda: add_expression("3"), **FUNC_BUTTON_STYLE).grid(row=5, column=2, **SPEC)
tk.Button(text=".", command=lambda: add_expression("."), **FUNC_BUTTON_STYLE).grid(row=6, column=0, **SPEC)


# Установка кнопки для выполнения введенной операции
tk.Button(text="=", command=solve_expression, **FUNC_BUTTON_STYLE).grid(row=5, column=3, **SPEC_EQUAL)

# Установка кнопок для ввода арифметических знаков
tk.Button(text="+", command=lambda: add_expression(" + "), **FUNC_BUTTON_STYLE).grid(row=7, column=0, **SPEC_SIGN)
tk.Button(text="-", command=lambda: add_expression(" - "), **FUNC_BUTTON_STYLE).grid(row=7, column=2, **SPEC_SIGN)

# Установка кнопки для удаление последнего символа
tk.Button(text="del", command=del_last, **FUNC_BUTTON_STYLE).grid(row=6, column=2, **SPEC)

# Установка поля для ввода выражения
expression_field = tk.Entry(textvariable=expression)
expression_field.grid(row=0, column=1, columnspan=3,  stick="nsew", ipady=20)

# проверка корректности выражения при вводе символов
expression.trace_add("write", check_expression)

# установка поля с результатом вычислений
result_field = tk.Label(textvariable=result)
result_field.grid(row=1, column=1, columnspan=3, stick="nsew", ipady=20)

# создание меню
main_menu = tk.Menu()

clear_menu = tk.Menu()
clear_menu.add_command(label="All", command=clear_all)
clear_menu.add_command(label="Expression", command=lambda: expression.set(""))
clear_menu.add_command(label="Result", command=lambda: result.set(""))

main_menu.add_command(label="Help", command=click_menu_info)
main_menu.add_command(label="About", command=click_menu_about)
main_menu.add_cascade(label="Clear", menu=clear_menu)

# оснвной цикл приложения и подключение меню
window.config(menu=main_menu)

window.mainloop()