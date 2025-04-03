from PyQt6.QtWidgets import *
from PyQt6.QtCore import QSize

from PIL import Image


def negative_photo(full_path: str):
    full_path = full_path.split("/")

    img_path = "/".join(full_path[:-1]) + "/"
    img_name = full_path[-1]

    img = Image.open(img_path + img_name)
    pixels = list(img.getdata())

    for i in range(len(pixels)):
        print(pixels[i])
        r, g, b = pixels[i][:3]

        pixels[i] = (255 - r, 255 - g, 255 - b)

    img.putdata(pixels)
    img.save(img_path + "neg_" + img_name)


# negative_photo("/Users/dmitriy/BMSTU/sem_2/Python/lab_03/template/image_1.bmp")

app = QApplication([])
window = QMainWindow()
window.setFixedSize(QSize(400, 200))
layout = QVBoxLayout()

file_path = ""

def choose_file():
    # Выбор пути к файлу
    global file_path
    file_path = QFileDialog.getOpenFileName(
        parent=None,
        caption="Выберите файл",
        directory="",
        filter="Images (*.bmp)"
    )[0]

    file_path_label.setText(file_path)


# Кнопочки
make_negative_button = QPushButton("Сделать негатив")
make_negative_button.clicked.connect(lambda: negative_photo(file_path))

choose_file_button = QPushButton("Выбрать файл")
choose_file_button.clicked.connect(choose_file)

# Тексты
file_path_label = QLabel("Путь файла")

# Добавление элементов в layout
layout.addWidget(make_negative_button, 0)
layout.addWidget(choose_file_button, 1)
layout.addWidget(file_path_label, 2)


# Установка layout
widget = QWidget()
widget.setLayout(layout)
window.setCentralWidget(widget)

window.show()
app.exec()
