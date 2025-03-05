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
        for row in data:
            self.table.insert("", tkinter.END, values=row)
