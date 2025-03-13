from window_class import Window
from entry_field_class import EntryField
from table_class import Table
from root_finder import *
import tkinter as tk
from tkinter import messagebox
import re
from tkinter import ttk
from PIL import Image, ImageTk

frac_num_pattern = re.compile(r'^-?[1-9][0-9]*(.[0-9]*[1-9])?$|^-?[1-9][0-9]*(.[0-9]*[1-9])?[eE]-?[0-9]+|-?0.[0-1][0-9]*$')
int_num_pattern = re.compile(r'^-?[1-9][0-9]*')

FILDES_NAMES = {
    "func": "Функция",
    "start": "Начало отрезка",
    "end": "Конец отрезка",
    "step": "Щаг деления",
    "n_max": "Макс кол-во итераций",
    "eps": "Точность"
}


def show_error_code():
    msg = """
    1 – Кол-во итераций превышенно
    """
    messagebox.showinfo(title="Info", message=msg)

def uncorect_info(fild_name: str):
    info_correct.set(f"Некорректный ввод: {FILDES_NAMES[fild_name]}")
    fields_correct.set(False)


def check_fields(*args):
    if not check_expression(entry_fields["func"].get()) and entry_fields["func"].get():
        uncorect_info("func")
        return

    for key in ["start", "end", "step", "eps"]:
        if not(re.match(frac_num_pattern, entry_fields[key].get())) and entry_fields[key].get():
            uncorect_info(key)
            return

    if not(re.match(int_num_pattern, entry_fields["n_max"].get())) and entry_fields["n_max"].get():
        uncorect_info("n_max")
        return

    fields_correct.set(True)
    info_correct.set("")
    return

def find_root():
    if not fields_correct or not all(value.get() for value in entry_fields.values()):
        return

    exp = entry_fields["func"].get().replace(" ", "").replace("^", "**")
    print(exp)
    print(float(entry_fields["start"].get()), float(entry_fields["end"].get()), float(entry_fields["step"].get()), int(entry_fields["n_max"].get()), float(entry_fields["eps"].get()))

    segments = np.arange(
        float(entry_fields["start"].get()),
        float(entry_fields["end"].get()),
        float(entry_fields["step"].get())
    )

    if abs(segments[-1] - float(entry_fields["end"].get())) < 1e-5:
        segments = np.append(segments, float(entry_fields["end"].get()))

    finder = RootFinder(exp, segments, int(entry_fields["n_max"].get()), float(entry_fields["eps"].get()))



    # start, end, step = -10, 10, 0.05
    # segments = np.arange(start, end, step)
    # if abs(segments[-1] - end) > 1e-6:
    #     segments = np.append(segments, end)
    # finder = RootFinder(
    #     # "x**2 - 10",
    #     "sin(x) + cos(x) / ln(x)",
    #     segments,
    #     20,
    #     1e-5
    # )

    # ищем корни
    finded_roots = finder.find_roots()

    # добавляем корни в таблицу
    table.content_update(finded_roots)

    finder.get_graph()

    img_pil = Image.open("graph.png")
    img = ImageTk.PhotoImage(img_pil.resize((500, 340)))
    graph.config(image=img)
    graph.image = img
    # os.remove("graph.png")

    print("я всё")



def check_staples(exp):
    open_count = 0
    for symbol in exp:
        if symbol == "(":
            open_count += 1
        elif symbol == ")":
            open_count -= 1

        if open_count < 0:
            return False

    return open_count == 0


def check_expression(exp):
    return check_staples(exp) and (re.search(r'^\s*\+.*|.*[+-]\s*$|\d\s+\d|\(\s*[+]|[-+]\s*\)', exp) is None)


window_size = (1400, 500)
column_count = 6
row_count = 3


# Создание окна
window = Window(window_size, (0, 0), (False, False))
# window.grid_config(row_count, column_count)

fields_correct = tk.BooleanVar()
info_correct = tk.StringVar()

# Поля ввода значений
entry_fields = {
    "func": EntryField("Функция", (0, 0)),
    "start": EntryField("Начало\nотрезка", (2, 0)),
    "end": EntryField("Конец\nотрезка", (2, 1)),
    "step": EntryField("Шаг деления", (2, 2)),
    "n_max": EntryField("Макс. кол-во\nитераций", (2, 3)),
    "eps": EntryField("Точность", (2, 4)),
}

for field in entry_fields.values():
    field.value.trace_add("write", check_fields)


# Изображение графика
img_pil = Image.open("default_graph.png")
img = ImageTk.PhotoImage(img_pil.resize((500, 340)))
graph = ttk.Label(window.window, image=img)
graph.grid(row=4, column=0, rowspan=2, columnspan=3)

# Таблица корней
table_columns = ("number", "a_b", "x", "y", "iter_count", "error_code")
window.window.rowconfigure(4, weight=1)
window.window.columnconfigure(3, weight=1)
table_position = {"row": 4, "column": 3, "rowspan": 2, "columnspan": 3, "sticky": "ew" }
heading_names = (
    ("number","№"), ("a_b","x_i;x_(i+1)"), ("x", "x"), ("y", "f(x)"),
    ("iter_count", "Кол-во итераций"), ("error_code", "Код ошибки")
)
columns_width = (30, 205, 205, 205, 110, 70)

table = Table(table_columns, table_position)
table.heading_update(heading_names)
table.columns_update(columns_width)

find_root_button = tk.Button(text="Найти корни", command=find_root)
find_root_button.grid(row=0, column=column_count-1)

info_correct_label = tk.Label(textvariable=info_correct)
info_correct_label.grid(row=0, column=column_count-2)

# меню информации

info_menu = tk.Menu()
info_menu.add_command(label="Errore codes", command=show_error_code)

main_menu = tk.Menu()
main_menu.add_cascade(label="Info", menu=info_menu)
window.window.config(menu=main_menu)

window.window.mainloop()

