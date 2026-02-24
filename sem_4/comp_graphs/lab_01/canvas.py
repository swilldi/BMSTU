from PyQt6.QtWidgets import (QGraphicsView, QGraphicsScene, QMainWindow,
                             QApplication, QTableView, QGraphicsLineItem,
                             QLabel, QGridLayout, QWidget, QGraphicsTextItem, QGraphicsEllipseItem, QTableWidget,
                             QHeaderView, QTableWidgetItem, QPushButton, QLineEdit, QDialog, QVBoxLayout,
                             QDialogButtonBox, QMessageBox, QTextEdit, QAbstractItemView, QDoubleSpinBox, QGroupBox, QHeaderView)
from PyQt6.QtCore import Qt, QLineF, QAbstractTableModel, QRectF
from PyQt6.QtGui import QMouseEvent, QPen, QColor, QBrush

from figure import *
from point_table import PointTable

class Canvas(QGraphicsView):
    def __init__(self, table: PointTable):
        super().__init__()
        self.table = table

        self.d_x = self.d_y = 0
        self.dot_size = 0.2
        self.cur_sides = []


        # Границы сцены
        self.x_left = self.y_left = -2000
        self.x_right = self.y_right = 2000
        self.x_0 = 0  # Центр по X
        self.y_0 = 0  # Центр по Y
        self.step = (self.x_right - self.x_left) / 100
        self.k_scale = (self.x_right - self.x_left) / 100

        self.dots: dict[int,QGraphicsEllipseItem] = {}
        self.dot_labels: dict[int, QGraphicsTextItem] = {}

        self.last_dots: list[QGraphicsEllipseItem] = []
        self.sides: list[QGraphicsLineItem] = []

        self.scene = QGraphicsScene()
        self.setScene(self.scene)
        self.scene.setSceneRect(self.x_left, self.y_left,
                                self.x_right - self.x_left,
                                self.y_right - self.y_left)

        self.setupAxis()
        self.centerOn(self.x_0, self.y_0)

        # Запрещаем перемещение/прокрутку сцены пользователем
        self.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.setDragMode(QGraphicsView.DragMode.NoDrag)
        self.setMouseTracking(True)

        self.create_d_dot()
        self._ensure_all_points_visible(force=True)

    def create_d_dot(self, x = 0, y = 0):
        size = (self.dot_size + 0.1) * self.step
        x = x * self.step
        y = -y * self.step
        dot = QGraphicsEllipseItem(x - size / 2, y - size / 2, size, size)
        dot.setBrush(QBrush(QColor("blue")))
        dot.setPen(QPen(Qt.PenStyle.NoPen))  # Без контура
        self.scene.addItem(dot)
        self.d_dot = dot
        # print(self.dots)

    def update_d_dot(self, x, y):
        self.scene.removeItem(self.d_dot)
        self.create_d_dot(x, y)
        self._ensure_all_points_visible()

    def _points_bbox(self):
        """Прямоугольник, который покрывает все точки A и точку d (без осей/сетки)."""
        rect = None

        # Точки из множества A
        for dot in self.dots.values():
            r = dot.sceneBoundingRect()
            rect = r if rect is None else rect.united(r)

        # Точка d
        if hasattr(self, "d_dot") and self.d_dot is not None:
            r = self.d_dot.sceneBoundingRect()
            rect = r if rect is None else rect.united(r)

        return rect

    def _ensure_all_points_visible(self, force=False):
        """Если точки не помещаются во видимую область, подбираем масштаб так, чтобы всё было видно."""
        rect = self._points_bbox()
        if rect is None:
            return

        # Делаем небольшие поля вокруг результата
        margin = max(self.step * 2, 30)
        rect = QRectF(rect)
        rect.adjust(-margin, -margin, margin, margin)

        view_rect = self.mapToScene(self.viewport().rect()).boundingRect()

        if force or (not view_rect.contains(rect)):
            self.fitInView(rect, Qt.AspectRatioMode.KeepAspectRatio)

    def update_dot(self, ind, x, y):
        if ind in self.dots:
            self.scene.removeItem(self.dots[ind])
        if ind in self.dot_labels:
            self.scene.removeItem(self.dot_labels[ind])
        self.create_dot(Point(ind, x, y))
        self._ensure_all_points_visible()

    def create_dot(self, point: Point, isScaled=False):
        x, y = point.x, point.y
        print("before: ", x, y)

        if isScaled:
            x /= self.step
            y /= self.step

        x = x * self.step
        y = y * self.step
        print("after: ", x, y)


        size = self.dot_size * self.step

        # for pos, dot in list(self.dots.items()):
        #     if abs(pos[0] - x) < size / 2 and abs(pos[1] - y) < size / 2:  # 5px - радиус попадания
        #         self.scene.removeItem(dot)
        #         del self.dots[pos]
        #         print(f"Удалена точка: {x}, {y}")
        #         return

        dot = QGraphicsEllipseItem(x - size / 2, y - size / 2, size, size)
        dot.setBrush(QBrush(QColor("red")))
        dot.setPen(QPen(Qt.PenStyle.NoPen))  # Без контура
        self.scene.addItem(dot)
        self.dots[point.index] = dot

        label = QGraphicsTextItem(str(point.index + 1))
        label.setDefaultTextColor(QColor("red"))
        # Сдвиг подписи немного вправо и вверх от центра точки
        label.setPos(x + size / 2 + 2, y - size / 2 - 2)
        self.scene.addItem(label)
        self.dot_labels[point.index] = label

    def remove_dot(self, index: int):
        # Удаляем сам кружок
        if index in self.dots:
            self.scene.removeItem(self.dots[index])
            self.dots.pop(index)

        # Удаляем подпись
        if index in self.dot_labels:
            self.scene.removeItem(self.dot_labels[index])
            self.dot_labels.pop(index)

        # После удаления индексы точек в таблице обычно съезжают.
        # Сдвигаем ключи для всех элементов с индексом больше удалённого.
        keys = sorted(list(self.dots.keys()))
        for k in keys:
            if k > index:
                self.dots[k - 1] = self.dots.pop(k)

        label_keys = sorted(list(self.dot_labels.keys()))
        for k in label_keys:
            if k > index:
                self.dot_labels[k - 1] = self.dot_labels.pop(k)

        # Обновляем текст подписи, чтобы совпадал с новым индексом (нумерация с 1)
        for k, lbl in self.dot_labels.items():
            lbl.setPlainText(str(k + 1))
        self._ensure_all_points_visible(force=True)

    def draw_parallelogram(self, dots):
        for side in self.cur_sides:
            self.scene.removeItem(side)

        self.cur_sides = []
        for i in range(0, 4):
            a, b = dots[i], dots[(i + 1) % 4]
            side = QGraphicsLineItem(a.x * self.step, a.y * self.step, b.x * self.step, b.y * self.step)
            self.cur_sides.append(side)

        pen = QPen(QColor("green"))
        pen.setWidth(3)
        for side in self.cur_sides:
            side.setPen(pen)
            self.scene.addItem(side)




    def mousePressEvent(self, event: QMouseEvent):
        if event.button() == Qt.MouseButton.LeftButton:
            pos = self.mapToScene(event.position().toPoint())
            x, y = pos.x() / self.step, pos.y() / self.step
            self.create_dot(Point(self.table.rowCount(), x, y))
            self.table.add_dot(x, y)
            self._ensure_all_points_visible()
            print(f"Добавлена точка: {x}, {y}")

        super().mousePressEvent(event)

    def wheelEvent(self, event):
        # Запрещаем прокрутку/панорамирование колёсиком/тачпадом
        event.accept()

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
