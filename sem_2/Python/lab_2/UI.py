from window_class import Window
from entry_field_class import EntryField
from table_class import Table
from main import RootFinder
import tkinter as tk
import math
from tkinter import ttk
from PIL import Image, ImageTk

def find_root():
    finder = RootFinder(
        # entry_fields["func"].get(),
        # (lambda x: x**3 - x),
        (lambda x: math.sin(x)),
        (float(entry_fields["start"].get()), float(entry_fields["end"].get())),
        float(entry_fields["step"].get()),
        int(entry_fields["n_max"].get()),
        float(entry_fields["eps"].get())
    )

    # ищем корни
    finded_roots = finder.find_roots()

    # добавляем корни в таблицу
    table.content_update(finded_roots)




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

# # Изображение графика
# img_pil = Image.open("graph.png")
# img = ImageTk.PhotoImage(img_pil.resize((500, 340)))
# tk.Label(window.window, image=img).grid(row=4, column=0, rowspan=2, columnspan=3)


# Таблица корней
table_columns = ("number", "a_b", "x", "y", "iter_count", "error_code")
table_position = {"row": 4, "column": 3, "rowspan": 2, "columnspan": 2}
heading_names = (
    ("number","№"), ("a_b","x_i;x_(i+1)"), ("x", "x"), ("y", "f(x)"),
    ("iter_count", "Кол-во итераций"), ("error_code", "Код ошибки")
)
columns_width = (30, 100, 100, 100, 100, 100)

table = Table(table_columns, table_position)
table.heading_update(heading_names)
table.columns_update(columns_width)

find_root_button = tk.Button(text="Найти корни", command=find_root)
find_root_button.grid(row=0, column=column_count-1)

window.window.mainloop()