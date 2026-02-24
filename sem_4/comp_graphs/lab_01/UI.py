from PyQt6.QtWidgets import (QGraphicsView, QGraphicsScene, QMainWindow,
                             QApplication, QTableView, QGraphicsLineItem,
                             QLabel, QGridLayout, QWidget, QGraphicsTextItem, QGraphicsEllipseItem, QTableWidget,
                             QHeaderView, QTableWidgetItem, QPushButton, QLineEdit, QDialog, QVBoxLayout,
                             QDialogButtonBox, QMessageBox, QTextEdit, QAbstractItemView, QDoubleSpinBox, QGroupBox,
                             QHeaderView, QFormLayout, QHBoxLayout)
from PyQt6.QtCore import Qt, QLineF, QAbstractTableModel, QRegularExpression
from PyQt6.QtGui import QMouseEvent, QPen, QColor, QBrush, QValidator, QRegularExpressionValidator


from point_table import PointTable
from input_dialog_box import InputDialog


from canvas import Canvas
from figure import *

from solver import solve_parallelograms




class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        self._setup_ui()
        self.parallelograms = []

        # layout.setColumnStretch(0, 10)
        # layout.setColumnStretch(1, 4)
        #
        # layout.setRowStretch(0, 20)
        # layout.setRowStretch(4, 1)
        # layout.setRowStretch(5, 4)

        self.setGeometry(100, 100, 1000, 700)
        self.setFixedSize(1000, 700)
        self.selected_figure_index = 0
        # Убрал setFixedSize для возможности изменения размера окна


    def push_add_dot(self):
        dialog = InputDialog(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()
            if data is None:
                return

            x, y = float(data["x"]), -float(data["y"])
            self.canvas.create_dot(Point(self.table.rowCount(), x, y), isScaled=False)
            self.canvas._ensure_all_points_visible()
            self.table.add_dot(x, -y)

            print(f"Введенные данные: {data}")

    def push_remove_dot(self):
        row = self.table.currentRow()
        if row == -1:
            QMessageBox.warning(self, "Удаление", "Сначала выделите строку в таблице.")
            return

        print(row)
        self.canvas.remove_dot(row)
        self.table.delete_selected_row()

    def push_edit_dot(self):
        row = self.table.currentRow()
        if row == -1:
            QMessageBox.warning(self, "Изменение", "Сначала выделите строку в таблице.")
            return

        dialog = InputDialog(self)
        if dialog.exec() == QDialog.DialogCode.Accepted:
            data = dialog.get_data()
            if data is None:
                return

            x, y = float(data["x"]), -float(data["y"])
            self.table.setItem(row, 1, QTableWidgetItem(f"{x}"))
            self.table.setItem(row, 2, QTableWidgetItem(f"{-y}"))
            self.canvas.update_dot(row, x, y)

            print(f"Введенные данные: {data}")

    def push_solve(self):
        # Нужно минимум 3 точки из A
        if self.table.rowCount() < 3:
            QMessageBox.warning(self, "Ошибка", "Точек мало (нужно минимум 3)")
            return

        dots = self.table.get_dots()
        dx, dy = self.spinbox_d_x.value(), self.spinbox_d_y.value()
        self.parallelograms = solve_parallelograms(dots, dx, dy)

        res_text = ""
        is_first_line = True
        for (a, b, c, d) in self.parallelograms:
            res_text += f"{a.index + 1}, {b.index + 1}, {c.index + 1}, {d.index + 1}"
            if is_first_line:
                is_first_line = False
                res_text += "    <--"
            res_text += "\n"

        self.text_result.setText(res_text)
        self.selected_figure_index = 0
        self._draw_parallelogram()

        #
        # # 1) читаем d
        # dx = self.spinbox_d_x.value()
        # dy = self.spinbox_d_y.value()
        #
        # # 2) читаем точки A из таблицы (в математических координатах: Y вверх)
        # points = []
        # n = self.table.rowCount()
        # for row in range(n):
        #     x_item = self.table.item(row, 1)
        #     y_item = self.table.item(row, 2)
        #
        #     x = float(x_item.text()) if x_item is not None else 0.0
        #     y = float(y_item.text()) if y_item is not None else 0.0
        #
        #     points.append(Point(row, x, y))
        #
        # # 3) решаем
        # ok, count, found, text = solve(points, dx, dy, max_draw=100)
        # if not ok:
        #     QMessageBox.warning(self, "Ошибка", text)
        #     return
        #
        # # 4) текстовый вывод
        # self.text_result.setText(text)
        #
        # # 5) графический вывод
        # self.canvas.update_d_dot(dx, dy)
        # self.canvas.clear_result_shapes()
        #
        # for a, b, c in found[:100]:
        #     self.canvas.draw_parallelogram(a, b, c, dx, dy)
        #
        # self.canvas._ensure_all_points_visible(force=True)

    def _draw_parallelogram(self):
        if not self.parallelograms:
            QMessageBox.warning(self, "Ошибка", "Параллелограммы не найдены")

        self.canvas.draw_parallelogram(self.parallelograms[self.selected_figure_index])





    def canvas_update_d_dot(self):
        print(f"d({self.spinbox_d_x.value(), self.spinbox_d_y.value()})")
        self.canvas.update_d_dot(self.spinbox_d_x.value(), self.spinbox_d_y.value())

    def _setup_ui(self):
        self._setup_buttons()
        self._setup_table()
        self.canvas = Canvas(self.table)
        self._setup_text_result()
        self._setup_input_d()
        self._setup_selecting_button()

        layout = QGridLayout()
        layout.addWidget(self.canvas, 0, 0, 3, 1)

        # layout.addLayout(self.spinboxes_point_d_layout, 0, 1)
        layout.addWidget(self.group_input_d, 0, 1)
        layout.addWidget(self.table, 1, 1)
        layout.addWidget(self.group_buttons, 2, 1)
        layout.addWidget(self.selecting_buttons, 3, 1)

        layout.addWidget(self.text_result, 3, 0)

        self.setLayout(layout)
        self.layout = layout

    def _setup_buttons(self):
        group_buttons = QGroupBox()
        vbox_button = QVBoxLayout(group_buttons)

        self.add_dot_button = QPushButton("Добавить точку")
        self.add_dot_button.clicked.connect(self.push_add_dot)
        vbox_button.addWidget(self.add_dot_button)

        self.edit_dot_button = QPushButton("Редактировать точку")
        self.edit_dot_button.clicked.connect(self.push_edit_dot)
        vbox_button.addWidget(self.edit_dot_button)

        self.remove_dot_button = QPushButton("Удалить точку")
        self.remove_dot_button.clicked.connect(self.push_remove_dot)
        vbox_button.addWidget(self.remove_dot_button)

        self.solve_button = QPushButton("Решить")
        self.solve_button.clicked.connect(self.push_solve)
        vbox_button.addWidget(self.solve_button)

        self.group_buttons = group_buttons

    def _setup_selecting_button(self):
        group = QGroupBox("Выбор параллелограмма")
        group.setMinimumHeight(120)

        hbox_move_button = QHBoxLayout(group)

        self.figure_up_button = QPushButton("Вверх")
        self.figure_up_button.clicked.connect(self._up_selected_figure)

        hbox_move_button.addWidget(self.figure_up_button)


        self.figure_down_button = QPushButton("Вниз")
        self.figure_down_button.clicked.connect(self._down_selected_figure)
        hbox_move_button.addWidget(self.figure_down_button)

        self.selecting_buttons = group

    def _up_selected_figure(self):
        print(f"up: {self.selected_figure_index}")
        if self.selected_figure_index == 0:
            return

        res_text = ""
        count = 0
        self.selected_figure_index -= 1
        for (a, b, c, d) in self.parallelograms:
            res_text += f"{a.index + 1}, {b.index + 1}, {c.index + 1}, {d.index + 1}"
            if count == self.selected_figure_index:
                res_text += "    <--"
            res_text += "\n"
            count += 1

        self.text_result.setText(res_text)
        self._draw_parallelogram()

    def _down_selected_figure(self):
        print(f"down: {self.selected_figure_index}")
        if self.selected_figure_index + 1 >= len(self.parallelograms):
            return

        res_text = ""
        count = 0
        self.selected_figure_index += 1
        for (a, b, c, d) in self.parallelograms:
            res_text += f"{a.index + 1}, {b.index + 1}, {c.index + 1}, {d.index + 1}"
            if count == self.selected_figure_index:
                res_text += "    <--"
            res_text += "\n"
            count += 1

        self.text_result.setText(res_text)
        self._draw_parallelogram()

    def _setup_table(self):
        self.table = PointTable()

    def _setup_text_result(self):
        text_result = QTextEdit()
        text_result.setReadOnly(True)
        self.text_result = text_result


    def _setup_input_d(self):
        group_input_d = QGroupBox("Точка d")
        layout = QGridLayout(group_input_d)

        self.spinbox_d_x = QDoubleSpinBox()
        self.spinbox_d_y = QDoubleSpinBox()

        for spinbox in (self.spinbox_d_x, self.spinbox_d_y):
            spinbox.setRange(-50, 50)
            spinbox.setDecimals(3)
            spinbox.setSingleStep(0.1)
            spinbox.setValue(0)
            spinbox.valueChanged.connect(self.canvas_update_d_dot)

        layout.addWidget(QLabel("x: "), 0, 0)
        layout.addWidget(self.spinbox_d_x, 0, 1)
        layout.addWidget(QLabel("y: "), 1, 0)
        layout.addWidget(self.spinbox_d_y, 1, 1)

        self.group_input_d = group_input_d




if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()

    for (x, y) in [(1, 1), (1, 0), (2, 1), (2, 0), (1, -1), (2, -1)]:
        window.canvas.create_dot(Point(window.table.rowCount(), x, y), isScaled=False)
        window.canvas._ensure_all_points_visible()
        window.table.add_dot(x, -y)

    app.exec()
