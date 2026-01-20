from c_func import *
from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel, QHBoxLayout, QVBoxLayout, QScrollArea, QWidget, QPushButton, QLineEdit, QSpinBox, QGridLayout, QPlainTextEdit
from PyQt6.QtGui import QIntValidator, QRegularExpressionValidator
from PyQt6.QtCore import QRegularExpression
import sys


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle("lab_12")
        
        self.task_windows = []
        
        self.button_task_1 = QPushButton("Заполнение массива\n простыми числами")
        self.button_task_1.clicked.connect(self.start_task_1)
        self.button_task_2 = QPushButton("Вставка числа после\n четных чисел")
        self.button_task_2.clicked.connect(self.start_task_2)
        
        layout = QHBoxLayout()
        layout.addWidget(self.button_task_1)
        layout.addWidget(self.button_task_2)
        
        buttons = QWidget()
        buttons.setLayout(layout)
        
        
        self.setCentralWidget(buttons)
    
    def start_task_1(self):
        print("запуск задания 1")
        w = TaskOneWindow()
        self.task_windows.append(w)
        w.show()
        
    def start_task_2(self):
        print("запуск задания 2")
        w = TaskTwoWindow()
        self.task_windows.append(w)
        w.show()
        
class TaskOneWindow(QMainWindow):
    def __init__(self):
        super(TaskOneWindow, self).__init__()
        self.setWindowTitle("task_1")
        
        
        # ввод количества элементов
        self.input_label = QLabel("Размер массива: ")
        self.input = QSpinBox()
        self.input.setValue(5)
        self.input.setMinimum(0)
        self.input.setMaximum(1000)
        
        # Кнопка активации
        self.button = QPushButton("Заполнение массив простыми числами")
        self.button.clicked.connect(self.fill_arr)
        
        # Результат работы
        self.output = QPlainTextEdit("Здесь будет отображаться массив простых чисел")
        self.output.setReadOnly(True)
        
        layout = QGridLayout()
        layout.addWidget(self.input_label, 0, 0)
        layout.addWidget(self.input, 0, 1)
        layout.addWidget(self.button, 1, 0, 1, 2)
        layout.addWidget(self.output, 2, 0, 1, 2)
        
        
        widgets = QWidget()
        widgets.setLayout(layout)
        self.setCentralWidget(widgets)
    
    def fill_arr(self):
        n = self.input.value()
        if (n == 0):
            self.output.setPlainText("Массив пустой")
            return
        arr = arr_fill_prime_num(n)
        res_test = [ f"{i+1}) {arr[i]}" for i in range(len(arr))]
        self.output.setPlainText("\n".join(res_test))
        
        

class TaskTwoWindow(QMainWindow):
    def __init__(self):
        super(TaskTwoWindow, self).__init__()
        self.setWindowTitle("task_2")
        
        # Регулярное выражение для массива чисел через пробел
        rx = QRegularExpression(r"(-?\d* )*")
        
        # Ввод массива
        self.input_arr_label = QLabel("Исходный массив: ")
        self.input_arr = QLineEdit()
        self.input_arr.setValidator(QRegularExpressionValidator(rx))
        # Ввод заполняемого числа
        self.input_fill_name_label = QLabel("Заполняемое число: ")
        self.input_fill_name = QLineEdit()
        self.input_fill_name.setValidator(QIntValidator(-10**6, 10**6))
        
        
        # Кнопка выполнениея действия
        self.button = QPushButton("Вставить после четных чисел")
        self.button.clicked.connect(self.add_after_prime_num)
        
        
        # Вывод исходных массивов
        # Выделение максимального количества памяти
        self.method_1_label = QLabel("Сразу выделяется максимальное количество памяти")
        self.method_1_output = QLabel("Здесь будет массив")
        scroll_method_1 = QScrollArea()
        scroll_method_1.setWidget(self.method_1_output)
        scroll_method_1.setWidgetResizable(True)
        
        # Два запуска функции: определения кол-ва элементов, выполнение операции
        self.method_2_label = QLabel("Сначала считается нужно количество элементов")
        self.method_2_output = QLabel("Здесь будет массив")
        scroll_method_2 = QScrollArea()
        scroll_method_2.setWidget(self.method_2_output)
        scroll_method_2.setWidgetResizable(True)
        
        
        # Размещение виджетов в окне
        layout = QGridLayout()
        layout.addWidget(self.input_arr_label, 0, 0)
        layout.addWidget(self.input_arr, 0, 1)
        layout.addWidget(self.input_fill_name_label, 1, 0)
        layout.addWidget(self.input_fill_name, 1, 1)
        layout.addWidget(self.button, 2, 0, 1, 2)
        layout.addWidget(self.method_1_label, 3, 0, 1, 2)
        layout.addWidget(scroll_method_1, 4, 0, 1, 2)
        layout.addWidget(self.method_2_label, 5, 0, 1, 2)
        layout.addWidget(scroll_method_2, 6, 0, 1, 2)
        
        widgets = QWidget()
        widgets.setLayout(layout)
        self.setCentralWidget(widgets)
    
    def add_after_prime_num(self):
        arr = list(map(int, self.input_arr.text().split()))
        fill_num = int(self.input_fill_name.text())
        
        self.method_1_output.setText(" ".join(map(str, arr_add_after_even_1(arr, fill_num))))
        self.method_2_output.setText(" ".join(map(str, arr_add_after_even_2(arr, fill_num))))
        
        
# Запуск приложения
app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()

