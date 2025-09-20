from PyQt6.QtWidgets import (QGraphicsView, QGraphicsScene, QMainWindow,
                             QApplication, QTableView, QGraphicsLineItem,
                             QLabel, QGridLayout, QWidget, QGraphicsTextItem, QGraphicsEllipseItem, QTableWidget,
                             QHeaderView, QTableWidgetItem, QPushButton, QLineEdit, QDialog, QVBoxLayout,
                             QDialogButtonBox, QMessageBox, QTextEdit)
from PyQt6.QtCore import Qt, QLineF
from PyQt6.QtGui import QMouseEvent, QPen, QColor, QBrush

from re import compile, fullmatch
from main import find_min_diff_triangle

regex_num = compile('-?[0-9]{1,2}')


class Canvas(QGraphicsView):
    def __init__(self, table):
        super().__init__()
        self.table = table

        # Границы сцены
        self.x_left = self.y_left = -2000
        self.x_right = self.y_right = 2000
        self.x_0 = 0  # Центр по X
        self.y_0 = 0  # Центр по Y
        self.step = (self.x_right - self.x_left) // 100
        self.k_scale = (self.x_right - self.x_left) / 100

        self.dots: dict[(float, float):QGraphicsEllipseItem] = {}
        self.dots_count = 0
        self.last_dots: list[QGraphicsEllipseItem] = []
        self.sides: list[QGraphicsLineItem] = []

        self.scene = QGraphicsScene()
        self.setScene(self.scene)
        self.scene.setSceneRect(self.x_left, self.y_left,
                                self.x_right - self.x_left,
                                self.y_right - self.y_left)

        self.setupAxis()
        self.centerOn(self.x_0, self.y_0)

        self.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOn)
        self.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOn)
        self.setMouseTracking(True)
        self.canvasMove = False

    def update_table(self):
        """Обновляет таблицу координатами точек"""
        self.table.setRowCount(len(self.dots))
        # self.table.setColumnCount(3)
        # self.table.setHorizontalHeaderLabels(["№", "X", "Y"])

        for row, (coord, dot) in enumerate(self.dots.items()):
            # print("123", row, coord)
            x, y = coord
            # self.table.setItem(row, 0, QTableWidgetItem(str(row + 1)))
            self.table.setItem(row, 0, QTableWidgetItem(f"{int(x / self.step)}"))
            self.table.setItem(row, 1, QTableWidgetItem(f"{int(-y / self.step)}"))

        # Автоматическое растягивание столбцов
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)

    def create_dot(self, x, y, isScaled=False):
        print(x, y)
        if isScaled:
            x *= self.k_scale
            y *= self.k_scale

        x = round(x / self.step) * self.step
        y = round(y / self.step) * self.step

        size = 15

        for pos, dot in list(self.dots.items()):
            if abs(pos[0] - x) < size / 2 and abs(pos[1] - y) < size / 2:  # 5px - радиус попадания
                self.scene.removeItem(dot)
                del self.dots[pos]
                print(f"Удалена точка: {int(x)}, {int(y)}")
                self.update_table()
                return

        dot = QGraphicsEllipseItem(x - size / 2, y - size / 2, size, size)
        dot.setBrush(QBrush(QColor("red")))
        dot.setPen(QPen(Qt.PenStyle.NoPen))  # Без контура
        self.scene.addItem(dot)
        self.dots_count += 1
        self.dots[(x, y)] = dot
        self.update_table()
        # print(self.dots)

    def make_sides(self, coords):
        sides = [
            QGraphicsLineItem(coords[0][0], coords[0][1], coords[1][0], coords[1][1]),
            QGraphicsLineItem(coords[2][0], coords[2][1], coords[1][0], coords[1][1]),
            QGraphicsLineItem(coords[0][0], coords[0][1], coords[2][0], coords[2][1])
        ]

        pen = QPen(QColor("blue"))
        pen.setWidth(3)
        for side in sides:
            side.setPen(pen)
            self.scene.addItem(side)

        return sides



    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == Qt.MouseButton.LeftButton and not self.canvasMove:
            pos = self.mapToScene(event.position().toPoint())
            self.create_dot(pos.x(), pos.y())
            print(type(pos.x()))
            print(f"Добавлена точка: {pos.x():.0}, {pos.y():.0}")

        elif event.button() == Qt.MouseButton.RightButton:
            self.canvasMove = not self.canvasMove
            mode = QGraphicsView.DragMode.ScrollHandDrag if self.canvasMove else QGraphicsView.DragMode.NoDrag
            self.setDragMode(mode)
            print(f"Режим перемещения: {'ON' if self.canvasMove else 'OFF'}")

        super().mousePressEvent(event)

    def setupAxis(self):
        # Основные оси
        x_axis = QGraphicsLineItem(QLineF(self.x_left, self.y_0, self.x_right, self.y_0))
        y_axis = QGraphicsLineItem(QLineF(self.x_0, self.y_left, self.x_0, self.y_right))

        pen = QPen(QColor("black"))
        pen.setWidth(2)
        x_axis.setPen(pen)
        y_axis.setPen(pen)

        # Деления на осях
        # 40 делений
        tick_length = 10
        step = self.step
        for i in range(int(self.x_left), int(self.x_right) + 1, int(step)):
            # Деления на оси X


            self.scene.addItem(QGraphicsLineItem(QLineF(i, self.y_left, i, self.y_right)))
            self.scene.addItem(QGraphicsLineItem(QLineF(self.x_left, i, self.x_right, i)))

            tick = QGraphicsLineItem(QLineF(i, self.y_0 - tick_length / 2,
                                            i, self.y_0 + tick_length / 2))
            label_x = QGraphicsTextItem(str(i // step))
            label_x.setPos(i, self.y_0)

            tick.setPen(pen)
            self.scene.addItem(tick)
            self.scene.addItem(label_x)

            # Деления на оси Y
            tick = QGraphicsLineItem(QLineF(self.x_0 - tick_length / 2, i,
                                            self.x_0 + tick_length / 2, i))
            label_y = QGraphicsTextItem(str(-i // step))
            label_y.setPos(self.x_0, i)
            tick.setPen(pen)
            self.scene.addItem(tick)
            self.scene.addItem(label_y)

        self.scene.addItem(x_axis)
        self.scene.addItem(y_axis)


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        layout = QGridLayout()
        layout.addWidget(QLabel("Таблица значений"), 0, 1)
        self.layout = layout

        layout.setColumnStretch(0, 10)
        layout.setColumnStretch(1, 4)

        layout.setRowStretch(0, 20)
        layout.setRowStretch(4, 1)
        layout.setRowStretch(5, 4)

        table = QTableWidget()
        table.setColumnCount(2)
        table.setHorizontalHeaderLabels(["X", "Y"])
        table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        layout.addWidget(table, 0, 1)
        self.table = table

        self.solve_button = QPushButton("Решить")
        self.solve_button.clicked.connect(self.push_solve)
        layout.addWidget(self.solve_button, 2, 1)

        self.add_dot_button = QPushButton("Добавить/Удалить точку")
        self.add_dot_button.clicked.connect(self.push_add_dot)
        layout.addWidget(self.add_dot_button, 1, 1)

        text_result_label = QLabel("Результаты:")
        layout.addWidget(text_result_label, 4, 0)

        text_result = QTextEdit()
        text_result.setReadOnly(True)
        layout.addWidget(text_result, 5, 0)
        self.text_result = text_result

        self.canvas = Canvas(table)
        layout.addWidget(self.canvas, 0, 0, 3, 1)

        self.setLayout(layout)
        self.setGeometry(100, 100, 1000, 700)
        # Убрал setFixedSize для возможности изменения размера окна

    def push_add_dot(self):
        dialog = InputDialog(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()

            if data is None:
                return

            self.canvas.create_dot(float(data["x"]), -float(data["y"]), isScaled=True)
            print(f"Введенные данные: {data}")

    def push_solve(self):

        if len(self.canvas.dots) < 3:
            msg = QMessageBox()
            msg.setText("Ошибка")
            msg.setInformativeText('Точек мало\n(геометрию списывал?)')
            msg.setWindowTitle("Ошибка")
            msg.exec()
            return



        data = find_min_diff_triangle(self.canvas.dots)

        for side in self.canvas.sides:
            self.canvas.scene.removeItem(side)
        for coord, dot in self.canvas.dots.items():
            if coord in self.canvas.last_dots:
                dot.setBrush(QBrush(QColor("red")))

        self.canvas.last_dots.clear()
        self.canvas.last_dots.extend(data[0])

        self.canvas.sides = self.canvas.make_sides(data[0])
        for coord in data[0]:
            self.canvas.dots[coord].setBrush(QBrush(QColor("blue")))


        res = ""
        for coord in data[0]:
            res += f"({int(coord[0] / self.canvas.step)}, {-int(coord[1] / self.canvas.step)})\n"
        res += f"Минимальная разница: {data[1]}"

        # str_coords = list(map(lambda c: f"{c / self.canvas.step:.2f}", data[0]))
        self.text_result.setText(res)


class InputDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Ввод данных")
        self.setup_ui()

    def setup_ui(self):
        layout = QVBoxLayout()

        # Поле для имени
        self.x_label = QLabel("X:")
        self.x_input = QLineEdit()
        layout.addWidget(self.x_label)
        layout.addWidget(self.x_input)

        # Поле для возраста
        self.y_label = QLabel("Y:")
        self.y_input = QLineEdit()
        layout.addWidget(self.y_label)
        layout.addWidget(self.y_input)

        # Кнопки OK/Cancel
        self.buttons = QDialogButtonBox(
            QDialogButtonBox.StandardButton.Ok |
            QDialogButtonBox.StandardButton.Cancel
        )
        self.buttons.accepted.connect(self.accept)
        self.buttons.rejected.connect(self.reject)
        layout.addWidget(self.buttons)

        self.setLayout(layout)

    def get_data(self):
        if not (fullmatch(regex_num, self.x_input.text()) and fullmatch(regex_num, self.y_input.text())):
            msg = QMessageBox()
            msg.setText("Ошибка")
            msg.setInformativeText('Вводи пж нормальные циферки\n')
            msg.setWindowTitle("Ошибка")
            msg.exec()
            return None

        if abs(float(self.x_input.text())) >= 50 or abs(float(self.x_input.text())) >= 50:
            msg = QMessageBox()
            msg.setText("Ошибка")
            msg.setInformativeText('Циферки хорошие, но очень большие по модулю\n')
            msg.setWindowTitle("Ошибка")
            msg.exec()
            # MessageBox('Циферки хорошие, но очень большие по модулю\n')
            return None

        return {
            "x": self.x_input.text(),
            "y": self.y_input.text()
        }

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()
