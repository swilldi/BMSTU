import tkinter
from tkinter import ttk

class Table:
    def __init__(self, columns, position):
        self.table = ttk.Treeview(columns=columns, show="headings")
        self.table.grid(**position)

    def heading_update(self, values):
        for heading, text in values:
            self.table.heading(heading, text=text)

    def columns_update(self, values):
        for i, value in enumerate(values):
            self.table.column(f"#{i+1}", stretch=tkinter.NO, width=value)

    def content_update(self, data):
        self.table.delete(*self.table.get_children())
        index = 1
        for row in data:
            print(row)
            print([(row[0], row[1])])
            row = [index] + [f"{row[0]:g} | {row[1]:g}", f"{row[2]:g}", f"{row[3]:e}"] + row[4:]
            index += 1
            self.table.insert("", tkinter.END, values=row)
