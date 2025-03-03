from window_class import Window
import tkinter as tk

window_size = (700, 500)
column_count = 6
row_count = 3

window = Window(window_size, (400, 200), (False, False))
window.grid_config(row_count, column_count)



entry_fields = {
    "func": EntryField("Функция", (0, 0)),
    "start": EntryField("Начало\nотрезка", (0, 1)),
    "end": EntryField("Конец\nотрезка", (0, 2)),
    "step": EntryField("Шаг деления", (0, 3)),
    "n_max": EntryField("Макс. кол-во\nитераций", (0, 4)),
    "eps": EntryField("Точность", (0, 5)),
}

entry_fields["start"].get()
window.window.mainloop()