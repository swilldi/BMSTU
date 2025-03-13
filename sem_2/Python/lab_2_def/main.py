import tkinter as tk
import sympy as sm

def find_root():
    # str_func = "sin(x)"
    # a = -1
    # b = 1
    # eps = 1e-4

    str_func = str_func_tk.get()
    a = float(start_tk.get())
    b = float(end_tk.get())
    eps = float(eps_tk.get())

    x_symbol = sm.symbols("x")
    func = sm.simplify(str_func)
    print(func)
    func_d1 = func.diff(x_symbol)
    print(func_d1)
    func_d2 = func_d1.diff(x_symbol)
    print(func_d2)

    f = lambda x: func.subs(x_symbol, x)
    f_d1 = lambda x: func_d1.subs(x_symbol, x)
    f_d2 = lambda x: func_d2.subs(x_symbol, x)

    a, b = min(a, b), max(a, b)

    x = a
    while abs(f(x) / f_d1(x)) > eps:
        x = x - f(x) / f_d1(x)
    if a <= x <= b:
        x = x.evalf()
        root_value.set(f"x: {x:g}")
        f_root_value.set(f"f(x): {f(x):g}")
        return

    x = b
    while abs(f(x) / f_d1(x)) > eps:
        x = x - f(x) / f_d1(x)
    if a <= x <= b:
        x = x.evalf()
        root_value.set(f"x: {x:g}")
        f_root_value.set(f"f(x): {f(x):g}")
        return





col_count = 4
row_count = 4

root = tk.Tk()

# настройка сетки
for i in range(col_count):
    root.columnconfigure(i)
for i in range(row_count):
    root.rowconfigure(i)

# переменные для полей ввода
str_func_tk = tk.StringVar()
start_tk = tk.StringVar()
end_tk = tk.StringVar()
eps_tk = tk.StringVar()

# переменные для полей вывода
root_value = tk.StringVar(value=f"x:")
f_root_value = tk.StringVar(value="f(x):")

# поля ввода
tk.Label(text="Функция: ").grid(row=0, column=0)
str_func_field = tk.Entry(textvariable=str_func_tk)
str_func_field.grid(row=0, column=1)

tk.Label(text="Начало: ").grid(row=1, column=0)
start_field = tk.Entry(textvariable=start_tk)
start_field.grid(row=1, column=1)

tk.Label(text="Конец: ").grid(row=2, column=0)
end_field = tk.Entry(textvariable=end_tk)
end_field.grid(row=2, column=1)

tk.Label(text="eps: ").grid(row=3, column=0)
eps_field = tk.Entry(textvariable=eps_tk)
eps_field.grid(row=3, column=1)



# настройка вывода
answer_x = tk.Label(textvariable=root_value)
answer_x.grid(row=0, column=3)

answer_fx = tk.Label(textvariable=f_root_value)
answer_fx.grid(row=1, column=3)


# Кнопка расчета
solve_button = tk.Button(text="Найти корень", command=find_root)
solve_button.grid(row=3, column=3)


root.mainloop()


