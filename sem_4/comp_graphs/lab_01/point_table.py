from PyQt6.QtWidgets import (
                             QTableWidget, QHeaderView, QTableWidgetItem,
                             QDialog, QMessageBox, QAbstractItemView,
                             QDoubleSpinBox, QGroupBox, QHeaderView)
from PyQt6.QtCore import Qt, QLineF, QAbstractTableModel


from figure import *

class PointTable(QTableWidget):
    def __init__(self):
        super().__init__()
        self.setColumnCount(3)
        self.setHorizontalHeaderLabels(["N", "x", "y"])
        self.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)

        self.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeMode.Fixed)
        self.setColumnWidth(0, 40)

        self.setEditTriggers(QAbstractItemView.EditTrigger.NoEditTriggers)
        self.setSelectionBehavior(QAbstractItemView.SelectionBehavior.SelectRows)
        self.setSelectionMode(QAbstractItemView.SelectionMode.SingleSelection)
        self.verticalHeader().setVisible(False)

    def delete_selected_row(self):
        row = self.currentRow()
        if row == -1:
            QMessageBox.warning(self, "Удаление", "Сначала выделите строку в таблице.")
            return

        self.removeRow(row)
        for i in range(row, self.rowCount()):
            self.setItem(i, 0, QTableWidgetItem(f"{i + 1}"))

    def add_dot(self, x, y):
        i = self.rowCount()
        self.setRowCount(i + 1)

        self.setItem(i, 0, QTableWidgetItem(f"{i + 1}"))
        self.setItem(i, 1, QTableWidgetItem(f"{x}"))
        self.setItem(i, 2, QTableWidgetItem(f"{y}"))

    def get_dots(self) -> [Point]:
        dots = []
        for i in range(self.rowCount()):
            x = float(self.item(i, 1).text())
            y = float(self.item(i, 2).text())
            dots.append(Point(i, x, y))

        return dots

