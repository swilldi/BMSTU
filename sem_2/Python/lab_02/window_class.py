import tkinter as tk

class Window:
    def __init__(self,
                 size: (int, int) = (200, 200),
                 othod: (int, int) = (0, 0),
                 resize: (bool, bool) = (True, True)
                 ):

        self.window = tk.Tk()
        self.window.geometry(f"{size[0]}x{size[1]}+{othod[0]}+{othod[1]}")
        self.window.resizable(*resize)

    def grid_config(self, row_count = 0, column_count = 0):
        for i in range(column_count):
            self.window.columnconfigure(index=i, weight=1)
        for i in range(row_count):
            self.window.rowconfigure(index=i, weight=1)

