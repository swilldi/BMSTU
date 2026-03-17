"""
Графический интерфейс для вычисления значений функции u = f(x, y, z)
с использованием различных методов интерполяции.

Интерфейс передаёт данные в модель через функцию compute_interpolation(),
которую необходимо реализовать в модуле model.py.
"""

import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QGridLayout, QGroupBox, QLabel, QDoubleSpinBox, QSpinBox,
    QComboBox, QPushButton, QFrame, QSizePolicy
)
from PyQt6.QtCore import Qt, QThread, pyqtSignal
from PyQt6.QtGui import QFont, QPalette, QColor


# ── Заглушка модели ──────────────────────────────────────────────────────────
# Замените импорт ниже на реальный модуль, когда он будет готов.
# from model import compute_interpolation

def compute_interpolation(params: dict) -> float:
    """
    Заглушка. Замените тело функции вызовом реальной модели.

    Параметры (params):
        x_value   : float  — значение x
        y_value   : float  — значение y
        z_value   : float  — значение z

        x_method  : str    — 'newton' | 'spline'
        y_method  : str    — 'newton' | 'spline'
        z_method  : str    — 'newton' | 'spline'

        x_degree  : int    — степень полинома Ньютона по x (только для 'newton')
        y_degree  : int    — степень полинома Ньютона по y (только для 'newton')
        z_degree  : int    — степень полинома Ньютона по z (только для 'newton')

    Возвращает:
        float — вычисленное значение u = f(x, y, z)
    """
    raise NotImplementedError("Модель ещё не реализована.")


# ── Поток для асинхронного вычисления ────────────────────────────────────────
class ComputeWorker(QThread):
    result_ready = pyqtSignal(float)
    error_occurred = pyqtSignal(str)

    def __init__(self, params: dict):
        super().__init__()
        self.params = params

    def run(self):
        try:
            value = compute_interpolation(self.params)
            self.result_ready.emit(value)
        except NotImplementedError:
            self.error_occurred.emit("Модель не реализована.")
        except Exception as e:
            self.error_occurred.emit(str(e))


# ── Виджет для одной оси ─────────────────────────────────────────────────────
class AxisWidget(QGroupBox):
    """Группа управления для одной координаты (x, y или z)."""

    METHOD_NEWTON = "newton"
    METHOD_SPLINE = "spline"

    def __init__(self, axis_label: str, color: str, parent=None):
        super().__init__(parent)
        self.axis_label = axis_label
        self._build_ui(color)

    def _build_ui(self, color: str):
        self.setTitle(f"  Ось  {self.axis_label}  ")
        self.setAlignment(Qt.AlignmentFlag.AlignCenter)

        font = QFont("Consolas", 11, QFont.Weight.Bold)
        self.setFont(font)

        self.setStyleSheet(f"""
            QGroupBox {{
                border: 2px solid {color};
                border-radius: 8px;
                margin-top: 14px;
                padding: 8px;
                background: #1a1d2e;
                color: {color};
                font-size: 13px;
                font-weight: bold;
            }}
            QGroupBox::title {{
                subcontrol-origin: margin;
                subcontrol-position: top center;
                padding: 0 10px;
                color: {color};
                letter-spacing: 3px;
            }}
            QLabel {{
                color: #c0c4d8;
                font-size: 11px;
                font-weight: normal;
                background: transparent;
            }}
            QDoubleSpinBox, QSpinBox, QComboBox {{
                background: #0d0f1a;
                color: #e8eaf6;
                border: 1px solid {color}88;
                border-radius: 5px;
                padding: 4px 8px;
                font-size: 12px;
                min-height: 28px;
            }}
            QDoubleSpinBox:focus, QSpinBox:focus, QComboBox:focus {{
                border: 1px solid {color};
            }}
            QComboBox::drop-down {{
                border: none;
                width: 20px;
            }}
            QComboBox QAbstractItemView {{
                background: #0d0f1a;
                color: #e8eaf6;
                selection-background-color: {color}55;
            }}
            QSpinBox::up-button, QSpinBox::down-button,
            QDoubleSpinBox::up-button, QDoubleSpinBox::down-button {{
                width: 18px;
                background: {color}33;
                border: none;
            }}
            QSpinBox::up-button:hover, QSpinBox::down-button:hover,
            QDoubleSpinBox::up-button:hover, QDoubleSpinBox::down-button:hover {{
                background: {color}66;
            }}
        """)

        layout = QGridLayout(self)
        layout.setSpacing(8)

        # ─ Значение координаты ─
        lbl_val = QLabel("Значение:")
        self.spin_value = QDoubleSpinBox()
        self.spin_value.setRange(0.0, 4.0)
        self.spin_value.setSingleStep(0.1)
        self.spin_value.setDecimals(4)
        self.spin_value.setValue(0.0)
        self.spin_value.setToolTip(f"Значение {self.axis_label} ∈ [0, 4]")

        layout.addWidget(lbl_val, 0, 0)
        layout.addWidget(self.spin_value, 0, 1)

        # ─ Метод интерполяции ─
        lbl_method = QLabel("Метод:")
        self.combo_method = QComboBox()
        self.combo_method.addItem("Полином Ньютона", self.METHOD_NEWTON)
        self.combo_method.addItem("Сплайн", self.METHOD_SPLINE)
        self.combo_method.currentIndexChanged.connect(self._on_method_changed)

        layout.addWidget(lbl_method, 1, 0)
        layout.addWidget(self.combo_method, 1, 1)

        # ─ Степень полинома (только для Ньютона) ─
        self.lbl_degree = QLabel("Степень:")
        self.spin_degree = QSpinBox()
        self.spin_degree.setRange(1, 20)
        self.spin_degree.setValue(3)
        self.spin_degree.setToolTip("Степень полинома Ньютона (1–20)")

        layout.addWidget(self.lbl_degree, 2, 0)
        layout.addWidget(self.spin_degree, 2, 1)

    def _on_method_changed(self):
        is_newton = self.combo_method.currentData() == self.METHOD_NEWTON
        self.lbl_degree.setVisible(is_newton)
        self.spin_degree.setVisible(is_newton)

    # ── Публичный API ─────────────────────────────────────────────────────────
    def get_value(self) -> float:
        return self.spin_value.value()

    def get_method(self) -> str:
        return self.combo_method.currentData()

    def get_degree(self) -> int:
        return self.spin_degree.value()


# ── Главное окно ─────────────────────────────────────────────────────────────
class MainWindow(QMainWindow):
    AXIS_COLORS = {
        "X": "#ff6b6b",   # красный
        "Y": "#51cf66",   # зелёный
        "Z": "#339af0",   # синий
    }

    def __init__(self):
        super().__init__()
        self.setWindowTitle("Интерполяция функции u = f(x, y, z)")
        self.setMinimumWidth(560)
        self._worker: ComputeWorker | None = None
        self._build_ui()

    def _build_ui(self):
        self.setStyleSheet("""
            QMainWindow {
                background: #0d0f1a;
            }
            QWidget#central {
                background: #0d0f1a;
            }
        """)

        central = QWidget()
        central.setObjectName("central")
        self.setCentralWidget(central)

        root = QVBoxLayout(central)
        root.setContentsMargins(24, 20, 24, 24)
        root.setSpacing(16)

        # ── Заголовок ─────────────────────────────────────────────────────────
        header = QLabel("u = f(x, y, z)")
        header.setAlignment(Qt.AlignmentFlag.AlignCenter)
        header.setStyleSheet("""
            QLabel {
                color: #e8eaf6;
                font-size: 22px;
                font-weight: bold;
                font-family: 'Consolas', monospace;
                letter-spacing: 4px;
                padding: 8px 0;
            }
        """)
        root.addWidget(header)

        subtitle = QLabel("Интерполяция трёхмерной функции")
        subtitle.setAlignment(Qt.AlignmentFlag.AlignCenter)
        subtitle.setStyleSheet("""
            QLabel {
                color: #5c6080;
                font-size: 11px;
                letter-spacing: 2px;
                font-family: 'Consolas', monospace;
                padding-bottom: 4px;
            }
        """)
        root.addWidget(subtitle)

        # ── Разделитель ───────────────────────────────────────────────────────
        line = QFrame()
        line.setFrameShape(QFrame.Shape.HLine)
        line.setStyleSheet("color: #2a2d40;")
        root.addWidget(line)

        # ── Виджеты осей ─────────────────────────────────────────────────────
        axes_row = QHBoxLayout()
        axes_row.setSpacing(14)
        self.axis_widgets: dict[str, AxisWidget] = {}

        for ax, color in self.AXIS_COLORS.items():
            aw = AxisWidget(ax, color)
            aw.setSizePolicy(
                QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed
            )
            self.axis_widgets[ax] = aw
            axes_row.addWidget(aw)

        root.addLayout(axes_row)

        # ── Кнопка вычисления ─────────────────────────────────────────────────
        self.btn_compute = QPushButton("⟳  Вычислить")
        self.btn_compute.setFixedHeight(44)
        self.btn_compute.setCursor(Qt.CursorShape.PointingHandCursor)
        self.btn_compute.setStyleSheet("""
            QPushButton {
                background: qlineargradient(
                    x1:0, y1:0, x2:1, y2:0,
                    stop:0 #ff6b6b, stop:0.5 #cc5de8, stop:1 #339af0
                );
                color: #ffffff;
                border: none;
                border-radius: 8px;
                font-size: 14px;
                font-weight: bold;
                font-family: 'Consolas', monospace;
                letter-spacing: 2px;
            }
            QPushButton:hover {
                background: qlineargradient(
                    x1:0, y1:0, x2:1, y2:0,
                    stop:0 #ff8787, stop:0.5 #da77f2, stop:1 #74c0fc
                );
            }
            QPushButton:pressed {
                background: qlineargradient(
                    x1:0, y1:0, x2:1, y2:0,
                    stop:0 #c92a2a, stop:0.5 #9c36b5, stop:1 #1971c2
                );
            }
            QPushButton:disabled {
                background: #2a2d40;
                color: #5c6080;
            }
        """)
        self.btn_compute.clicked.connect(self._on_compute)
        root.addWidget(self.btn_compute)

        # ── Панель результата ─────────────────────────────────────────────────
        result_frame = QFrame()
        result_frame.setStyleSheet("""
            QFrame {
                background: #131626;
                border: 1px solid #2a2d40;
                border-radius: 8px;
                padding: 4px;
            }
        """)
        result_layout = QHBoxLayout(result_frame)
        result_layout.setContentsMargins(16, 10, 16, 10)

        lbl_u = QLabel("u =")
        lbl_u.setStyleSheet("""
            QLabel {
                color: #5c6080;
                font-family: 'Consolas', monospace;
                font-size: 15px;
                background: transparent;
                border: none;
            }
        """)

        self.lbl_result = QLabel("—")
        self.lbl_result.setAlignment(Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter)
        self.lbl_result.setStyleSheet("""
            QLabel {
                color: #e8eaf6;
                font-family: 'Consolas', monospace;
                font-size: 20px;
                font-weight: bold;
                background: transparent;
                border: none;
            }
        """)

        result_layout.addWidget(lbl_u)
        result_layout.addWidget(self.lbl_result, 1)
        root.addWidget(result_frame)

        # ── Строка состояния ──────────────────────────────────────────────────
        self.lbl_status = QLabel("")
        self.lbl_status.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.lbl_status.setStyleSheet("""
            QLabel {
                color: #5c6080;
                font-size: 10px;
                font-family: 'Consolas', monospace;
                letter-spacing: 1px;
                background: transparent;
            }
        """)
        root.addWidget(self.lbl_status)

    # ── Сборка параметров ─────────────────────────────────────────────────────
    def _collect_params(self) -> dict:
        """
        Собирает параметры с GUI и возвращает словарь для передачи в модель.
        """
        params = {}
        for ax_lower, ax_upper in [("x", "X"), ("y", "Y"), ("z", "Z")]:
            aw = self.axis_widgets[ax_upper]
            params[f"{ax_lower}_value"] = aw.get_value()
            params[f"{ax_lower}_method"] = aw.get_method()
            if aw.get_method() == AxisWidget.METHOD_NEWTON:
                params[f"{ax_lower}_degree"] = aw.get_degree()
        return params

    # ── Обработчики событий ───────────────────────────────────────────────────
    def _on_compute(self):
        if self._worker and self._worker.isRunning():
            return  # защита от двойного нажатия

        params = self._collect_params()
        self._set_computing_state(True)

        self._worker = ComputeWorker(params)
        self._worker.result_ready.connect(self._on_result)
        self._worker.error_occurred.connect(self._on_error)
        self._worker.finished.connect(lambda: self._set_computing_state(False))
        self._worker.start()

    def _on_result(self, value: float):
        self.lbl_result.setStyleSheet("""
            QLabel {
                color: #51cf66;
                font-family: 'Consolas', monospace;
                font-size: 20px;
                font-weight: bold;
                background: transparent;
                border: none;
            }
        """)
        self.lbl_result.setText(f"{value:.8g}")
        self.lbl_status.setText("Вычисление завершено успешно.")

    def _on_error(self, message: str):
        self.lbl_result.setStyleSheet("""
            QLabel {
                color: #ff6b6b;
                font-family: 'Consolas', monospace;
                font-size: 14px;
                font-weight: bold;
                background: transparent;
                border: none;
            }
        """)
        self.lbl_result.setText("Ошибка")
        self.lbl_status.setText(f"⚠  {message}")

    def _set_computing_state(self, computing: bool):
        self.btn_compute.setEnabled(not computing)
        if computing:
            self.btn_compute.setText("⟳  Вычисляется…")
            self.lbl_status.setText("Выполняется вычисление…")
            self.lbl_result.setStyleSheet("""
                QLabel {
                    color: #5c6080;
                    font-family: 'Consolas', monospace;
                    font-size: 20px;
                    font-weight: bold;
                    background: transparent;
                    border: none;
                }
            """)
            self.lbl_result.setText("…")
        else:
            self.btn_compute.setText("⟳  Вычислить")


# ── Точка входа ───────────────────────────────────────────────────────────────
def main():
    app = QApplication(sys.argv)
    app.setStyle("Fusion")

    # Тёмная палитра для нативных виджетов
    palette = QPalette()
    palette.setColor(QPalette.ColorRole.Window, QColor("#0d0f1a"))
    palette.setColor(QPalette.ColorRole.WindowText, QColor("#e8eaf6"))
    palette.setColor(QPalette.ColorRole.Base, QColor("#131626"))
    palette.setColor(QPalette.ColorRole.AlternateBase, QColor("#1a1d2e"))
    palette.setColor(QPalette.ColorRole.Text, QColor("#e8eaf6"))
    palette.setColor(QPalette.ColorRole.Button, QColor("#1a1d2e"))
    palette.setColor(QPalette.ColorRole.ButtonText, QColor("#e8eaf6"))
    palette.setColor(QPalette.ColorRole.Highlight, QColor("#339af0"))
    palette.setColor(QPalette.ColorRole.HighlightedText, QColor("#ffffff"))
    app.setPalette(palette)

    window = MainWindow()
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()