import tkinter as tk

class EntryField:
    def __init__(self, label: str, position: (int, int)):
        self.__value = tk.StringVar()
        self.label = label

        tk.Label(text=label).grid(row=position[0], column=position[1])
        tk.Entry(textvariable=self.__value).grid(
            row=position[0] + 1, column=position[1], sticky="n"
        )

    def get(self):
        return self.__value.get()