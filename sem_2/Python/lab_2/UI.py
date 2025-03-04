from window_class import Window
from entry_field_class import EntryField
import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk

window_size = (1200, 500)
column_count = 5
row_count = 5

# Создание окна
window = Window(window_size, (400, 200), (False, False))
# window.grid_config(row_count, column_count)

# Поля ввода значений
entry_fields = {
    "func": EntryField("Функция", (0, 0)),
    "start": EntryField("Начало\nотрезка", (2, 0)),
    "end": EntryField("Конец\nотрезка", (2, 1)),
    "step": EntryField("Шаг деления", (2, 2)),
    "n_max": EntryField("Макс. кол-во\nитераций", (2, 3)),
    "eps": EntryField("Точность", (2, 4)),
}

# Изображение графика
img_pil = Image.open("graph.png")
img = ImageTk.PhotoImage(img_pil.resize((500, 340)))
tk.Label(window.window, image=img).grid(row=4, column=0, rowspan=2, columnspan=3)


# Таблица корней
table_columns = ("number", "a_b", "x", "y", "iter_count", "error_code")
table = ttk.Treeview(columns=table_columns, show="headings")
table.grid(row=4, column=3, rowspan=2, columnspan=2)

table.heading("number", text="№", )
table.heading("a_b", text="x_i;x_(i+1)")
table.heading("x", text="x")
table.heading("y", text="f(x)")
table.heading("iter_count", text="Кол-во итераций")
table.heading("error_code", text="Код ошибки")

table.column("#1", stretch=tk.NO, width=30)
table.column("#2", stretch=tk.NO, width=100)
table.column("#3", stretch=tk.NO, width=100)
table.column("#4", stretch=tk.NO, width=100)
table.column("#5", stretch=tk.NO, width=100)
table.column("#6", stretch=tk.NO, width=100)


window.window.mainloop()