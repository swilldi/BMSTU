import tkinter as tk

class EntryField:
    def __init__(self, label: str, position: (int, int)):
        self.value = tk.StringVar()
        self.label = label

        tk.Label(text=label).grid(row=position[0], column=position[1])
        self.field = tk.Entry(textvariable=self.value)
        self.field.grid(row=position[0] + 1, column=position[1], sticky="n")

    def get(self):
        return self.value.get()

    def set(self, val):
        self.value.set(val)