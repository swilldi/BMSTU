import tkinter as tk
from tkinter import messagebox
from main import *


def click_menu_about():
    print("click about")
    messagebox.showinfo(title="About", message="ООО \"ЛучшиеКалькуляторыВВидеПо\"\nДудырев Дмитрий ИУ7-22Б")

def del_last():
    expression.set(expression.get()[:-1])

def add_expression(get_digit):
    expression.set(expression.get() + get_digit)

def clear_all():
    expression.set("")
    result.set("")

def check_expression(*args):
    exp = expression.get().strip()
    if not exp:
        return

    correct_symbols = {"0", "1", "2", "3", "-", "+", " "}
    if set(exp) - correct_symbols or not exp[0].isdigit() or not exp[-1].isdigit():
        result_font_color.set("#B71C1C")
        result_background_color.set("#FFCDD2")

        result.set("Выражение не корректное")
        correct_expression.set(False)
    else:
        result_font_color.set("#7AD948")
        result_background_color.set("#CFFFB5")
        result.set("")
        correct_expression.set(True)


def solve_expression():
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
        elif symbol.isdigit():
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
    "pady": 10,
    "padx": 10
}

# характеристики расположения кнопок очистки
SPEC_CLEAR = SPEC.copy()
SPEC_CLEAR.update((
    ("ipadx", 0),
    ("ipady", 10)
))

# характеристики кнопок с числами и выражениями
FUNC_BUTTON_STYLE = {
    "font": (30)
}

window = tk.Tk()
window.geometry("800x800")
window.resizable(False, False)

expression = tk.StringVar()
result = tk.StringVar()
correct_expression = tk.BooleanVar(value=True)

result_font_color = tk.StringVar(value="#B71C1C")
result_background_color = tk.StringVar(value="#FFCDD2")


for col in range(4):
    window.columnconfigure(index=col, weight=1)
for row in range(5):
    window.columnconfigure(index=row, weight=1)


# Установка заголовков полей ввода и вывода
tk.Label(text="Expression:").grid(row=0, column=0)
# tk.Label(text="Num_2:").grid(row=1, column=0)
tk.Label(text="Result:").grid(row=1, column=0)
tk.Label(text="Clear:").grid(row=2, column=0)
# tk.Label(text="Operation:").grid(row=4, column=0)
# tk.Label(text="Selected expression:").grid(row=5, column=0)


# Установка кнопок для очиски полей
tk.Button(text="Expression", command=lambda: expression.set("")).grid(row=2, column=1, **SPEC_CLEAR)
# tk.Button(text="Num_2", command=lambda: num_2.set("")).grid(row=3, column=2)
tk.Button(text="Result", command=lambda: result.set("")).grid(row=2, column=2, **SPEC_CLEAR)
tk.Button(text="All", command=clear_all).grid(row=2, column=3, **SPEC_CLEAR)
# Установка выбора изменяемго числа
# tk.Radiobutton(text="Num_1", value=False, variable=selected_num).grid(row=5, column=1, columnspan=2)
# tk.Radiobutton(text="Num_2", value=True, variable=selected_num).grid(row=5, column=2, columnspan=2)

# Установка кнопок для ввода чисел
tk.Button(text="0", command=lambda: add_expression("0"), **FUNC_BUTTON_STYLE).grid(row=5, column=0, **SPEC)
tk.Button(text="1", command=lambda: add_expression("1"), **FUNC_BUTTON_STYLE).grid(row=5, column=1, **SPEC)
tk.Button(text="2", command=lambda: add_expression("2"), **FUNC_BUTTON_STYLE).grid(row=5, column=2, **SPEC)
tk.Button(text="3", command=lambda: add_expression("3"), **FUNC_BUTTON_STYLE).grid(row=5, column=3, **SPEC)

tk.Button(text="=", command=solve_expression).grid(row=6, column=0, **SPEC)
# Установка кнопок для ввода арифметических знаков
tk.Button(text="+", command=lambda: add_expression(" + "), **FUNC_BUTTON_STYLE).grid(row=6, column=1, **SPEC)
tk.Button(text="-", command=lambda: add_expression(" - "), **FUNC_BUTTON_STYLE).grid(row=6, column=2, **SPEC)
# Установка кнопок для удаление последнего символа
tk.Button(text="del", command=del_last, **FUNC_BUTTON_STYLE).grid(row=6, column=3, **SPEC)




expression_field = tk.Entry(textvariable=expression)
expression_field.grid(row=0, column=1, columnspan=3)

expression.trace_add("write", check_expression)
# num_2_field = tk.Entry(textvariable=num_2)
# num_2_field.grid(row=1, column=1)

result_field = tk.Label(textvariable=result)
result_field.grid(row=1, column=1, columnspan=3)

main_menu = tk.Menu()
main_menu.add_command(label="help")
main_menu.add_command(label="About", command=click_menu_about)




window.config(menu=main_menu)
window.mainloop()