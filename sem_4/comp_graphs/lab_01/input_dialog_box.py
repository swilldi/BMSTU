from PyQt6.QtWidgets import (QGraphicsView, QGraphicsScene, QMainWindow,
                             QApplication, QTableView, QGraphicsLineItem,
                             QLabel, QGridLayout, QWidget, QGraphicsTextItem, QGraphicsEllipseItem, QTableWidget,
                             QHeaderView, QTableWidgetItem, QPushButton, QLineEdit, QDialog, QVBoxLayout,
                             QDialogButtonBox, QMessageBox, QTextEdit, QAbstractItemView, QDoubleSpinBox, QGroupBox, QHeaderView, QFormLayout)
from PyQt6.QtCore import Qt, QLineF, QAbstractTableModel, QRegularExpression
from PyQt6.QtGui import QMouseEvent, QPen, QColor, QBrush, QValidator, QRegularExpressionValidator

class InputDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Ввод данных")
        self.setup_ui()

    def setup_ui(self):
        # Основной вертикальный лэйаут: форма + кнопки
        root = QVBoxLayout(self)
        # root.setContentsMargins(20, 15, 20, 15)
        # root.setSpacing(12)

        form = QFormLayout()

        form.setHorizontalSpacing(10)
        form.setVerticalSpacing(12)
        form.setLabelAlignment(Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter)
        form.setFormAlignment(Qt.AlignmentFlag.AlignLeft | Qt.AlignmentFlag.AlignTop)

        v = QRegularExpressionValidator(QRegularExpression("-?[0-9]{0,3}([,.][0-9]+)?"))
        self.x_input = QLineEdit()
        self.x_input.setValidator(v)
        self.x_input.setMinimumWidth(120)

        self.y_input = QLineEdit()
        self.x_input.setMinimumWidth(120)

        form.addRow("x:", self.x_input)
        form.addRow("y:", self.y_input)

        self.buttons = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok |
            QDialogButtonBox.StandardButton.Cancel
        )
        # русские подписи кнопок
        self.buttons.button(QDialogButtonBox.StandardButton.Ok).setText("ОК")
        self.buttons.button(QDialogButtonBox.StandardButton.Cancel).setText("Отмена")

        self.buttons.accepted.connect(self.accept)
        self.buttons.rejected.connect(self.reject)

        root.addLayout(form)
        root.addWidget(self.buttons)

        # чуть компактнее по ширине, чтобы поля не уезжали вправо
        self.setFixedWidth(200)

    def get_data(self):
        # Для QDoubleSpinBox ручная проверка regex не нужна — он сам валидирует ввод.
        x = float(self.x_input.text().replace(",", "."))
        y = float(self.y_input.text().replace(",", "."))

        if abs(x) >= 50 or abs(y) >= 50:
            msg = QMessageBox(self)
            msg.setText("Ошибка")
            msg.setInformativeText("Циферки хорошие, но очень большие по модулю")
            msg.setWindowTitle("Ошибка")
            msg.exec()
            return None

        return {
            "x": x,
            "y": y
        }