import tkinter as tk
from main import *



def make_plus():
    print("+")
    n_1, n_2 = num_1.get(), num_2.get()
    result.set(command_plus(n_1, n_2))

def make_minus():
    print("-")
    n_1, n_2 = num_1.get(), num_2.get()
    result.set(command_minus(n_1, n_2))

def del_last():
    if not selected_num.get():
        num = num_1
    else:
        num = num_2
    num.set(num.get()[:-1])

def set_num(get_digit):
    if not selected_num.get():
        num = num_1
    else:
        num = num_2

    num.set(num.get() + get_digit())

def clear_all():
    num_1.set("")
    num_2.set("")
    result.set("")



def add_zero():
    return "0"

def add_one():
    return "1"

def add_two():
    return "2"

def add_three():
    return "3"




window = tk.Tk()
window.geometry("600x800")

num_1 = tk.StringVar()
num_2 = tk.StringVar()
result = tk.StringVar()
selected_num = tk.BooleanVar(value=False)


for col in range(5):
    window.columnconfigure(index=col, weight=1)
for row in range(5):
    window.columnconfigure(index=row, weight=1)


# Установка заголовков полей ввода и вывода
tk.Label(text="Num_1:").grid(row=0, column=0)
tk.Label(text="Num_2:").grid(row=1, column=0)
tk.Label(text="Result:").grid(row=2, column=0)
tk.Label(text="Clear:").grid(row=3, column=0)
tk.Label(text="Operation:").grid(row=4, column=0)
tk.Label(text="Selected num:").grid(row=5, column=0)

# Установка кнопок для выполнения арифметических операция
tk.Button(text="+", command=make_plus).grid(row=4, column=1)
tk.Button(text="-", command=make_minus).grid(row=4, column=2)
# Установка кнопок для очиски полей
tk.Button(text="Num_1", command=lambda: num_1.set("")).grid(row=3, column=1)
tk.Button(text="Num_2", command=lambda: num_2.set("")).grid(row=3, column=2)
tk.Button(text="Result", command=lambda: result.set("")).grid(row=3, column=3)
tk.Button(text="All", command=clear_all).grid(row=3, column=4)
# Установка выбора изменяемго числа
tk.Radiobutton(text="Num_1", value=False, variable=selected_num).grid(row=5, column=1, columnspan=2)
tk.Radiobutton(text="Num_2", value=True, variable=selected_num).grid(row=5, column=2, columnspan=2)
# Установка кнопок для изменения выбранного числа
tk.Button(text="0", command=lambda: set_num(add_zero)).grid(row=6, column=0)
tk.Button(text="1", command=lambda: set_num(add_one)).grid(row=6, column=1)
tk.Button(text="2", command=lambda: set_num(add_two)).grid(row=6, column=2)
tk.Button(text="3", command=lambda: set_num(add_three)).grid(row=6, column=3)
tk.Button(text="del", command=del_last).grid(row=6, column=4)




num_1_field = tk.Entry(textvariable=num_1)
num_1_field.grid(row=0, column=1)

num_2_field = tk.Entry(textvariable=num_2)
num_2_field.grid(row=1, column=1)

result_field = tk.Label(textvariable=result)
result_field.grid(row=2, column=1)



window.mainloop()