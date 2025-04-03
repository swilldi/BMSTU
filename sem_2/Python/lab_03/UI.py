from PyQt6.QtWidgets import *
from PyQt6.QtCore import QSize, Qt
from PyQt6.QtGui import QPixmap
from PIL import Image
from coder import Coder
from os import path

class DialogWindow(QDialog):

    def __init__(self, message: str):
        super().__init__()

        dialog_buttons = QDialogButtonBox.StandardButton.Ok | QDialogButtonBox.StandardButton.Cancel
        self.buttonBox = QDialogButtonBox(dialog_buttons)
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)

        layout = QVBoxLayout()
        message = QLabel(message)
        layout.addWidget(message)
        layout.addWidget(self.buttonBox)
        self.setLayout(layout)

class MainWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.file_path = ""
        self.coder = Coder()

        # self.setBaseSize(QSize(400, 400))
        self.setFixedSize(QSize(400, 400))

        # Ввод текста
        self.text_field = QTextEdit()
        self.text_field.setPlaceholderText("Введите сообщение...")
        self.text_field.setFixedHeight(100)


        # Кнопки
        self.hide_string_button = QPushButton("Скрыть строку")
        self.hide_string_button.clicked.connect(self.hide_string)

        self.get_string_button = QPushButton("Извлечь строку")
        self.get_string_button.clicked.connect(self.get_string)

        self.choose_file_button = QPushButton("Выбрать файл")
        self.choose_file_button.clicked.connect(self.choose_file)

        # Текст
        self.file_path_label = QLabel("Путь к файлу")
        self.file_path_label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        # Изображение
        self.image_widget = QLabel()

        layout = QVBoxLayout()

        # align = Qt.AlignmentFlag.AlignVCenter | Qt.AlignmentFlag.AlignTop
        layout.addWidget(self.text_field, 0, Qt.AlignmentFlag.AlignBottom)
        layout.addWidget(self.hide_string_button, 1)
        layout.addWidget(self.get_string_button, 2)
        layout.addWidget(self.choose_file_button, 3)
        layout.addWidget(self.file_path_label, 4)

        # layout.addWidget(self.image_widget, 0, 1, 1, 3)

        widget = QWidget()
        widget.setLayout(layout)
        self.setCentralWidget(widget)


    def hide_string(self):
        # ошибки связанные с файлом
        if not self.file_path:
            QMessageBox.warning(self, "", "Файл не указан")
            return
        if not path.isfile(self.file_path):
            QMessageBox.warning(self, "", "Указан не файл или он не существует")
            return

        # получение сообщения
        message = self.text_field.toPlainText()

        if not message:
            dlg = DialogWindow("Сообщение пустое. Продолжать?")
            if not dlg.exec():
                return


        # ошибки связанные с сообщением
        if len(message) > 255:
            QMessageBox.warning(self, "", "Слишком большая строка")
            return
        if not message.isascii():
            QMessageBox.warning(self, "", "Строка содержит символы не из ASCII")
            return

        # получаем массив пикселей изображения
        image = Image.open(self.file_path)
        pixels = list(image.getdata())

        if (len(pixels) - 3) / 3 < len(message):
            QMessageBox.warning(self, "", "Слишком большая строка для данного ")
            return

        self.coder.pixels = pixels

        # кодируем сообщение
        self.coder.encode(message)

        # сохраняем изображение с закодированным сообщение
        image.putdata(pixels)
        image.save(self.file_path)

        # Сообщение об успешном завершении кодирования
        QMessageBox.about(self, "Successful encoded", "Сообщение успешно закодировано")

    def get_string(self):
        # ошибки связанные с файлом
        if not self.file_path:
            QMessageBox.warning(self, "", "Файл не указан")
            return
        if not path.isfile(self.file_path):
            QMessageBox.warning(self, "", "Указан не файл или он не существует")
            return

        image = Image.open(self.file_path)
        pixels = list(image.getdata())
        self.coder.pixels = pixels

        message = self.coder.decode()
        if not message.isascii():
            QMessageBox.warning(self, "No message", "Изображение не содержит сообщения")
            return

        QMessageBox.about(self, "Decoded string", message)

    def choose_file(self):
        self.file_path = QFileDialog.getOpenFileName(
            parent=None,
            caption="Выберите файл",
            directory="",
            filter="Images (*.bmp)"
        )[0]
        path = self.reform_file_path(self.file_path)
        self.file_path_label.setText(path)

    def reform_file_path(self, path: str):
        ROW_LEN = 47

        if len(path) <= ROW_LEN:
            return path

        new_path = ""
        row_len = 0
        path = path.split("/")
        for part in path[:-1]:
            cur_len = len(part)
            if row_len + cur_len > ROW_LEN:
                new_path += "\n" + part
                row_len = 0
            else:
                new_path += part
                row_len += cur_len
            new_path += "/"

        if len(path[-1]) + row_len > ROW_LEN:
            new_path += "\n" + path[-1]
        else:
            new_path += path[-1]

        return new_path


if __name__ == "__main__":

    app = QApplication([])

    window = MainWindow()
    window.show()

    # Запускаем цикл событий.
    app.exec()