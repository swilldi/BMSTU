import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QGroupBox, QLabel, QDoubleSpinBox, QSpinBox, QComboBox, QPushButton
)
from PyQt6.QtGui import QFont

from Solver import Solver


# TODO: заменить на реальную модель
from pprint import pprint
def compute_interpolation(solver: Solver, params: dict) -> float:
    # pprint(params)
    # raise NotImplementedError("Модель не реализована")
    return solver.solve(params)


FONT = QFont()
FONT.setPointSize(16)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Интерполяция u = f(x, y, z)")

        self.solver = Solver()

        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        layout.setSpacing(12)
        layout.setContentsMargins(16, 16, 16, 16)

        self.axes = {}
        for ax in ("x", "y", "z"):
            group = QGroupBox(f"Ось {ax.upper()}")
            group.setFont(FONT)
            g_layout = QHBoxLayout(group)
            g_layout.setSpacing(10)
            g_layout.setContentsMargins(12, 16, 12, 16)

            lbl_val = QLabel("Значение:")
            lbl_val.setFont(FONT)
            g_layout.addWidget(lbl_val)

            spin_val = QDoubleSpinBox()
            spin_val.setRange(0.0, 4)
            spin_val.setSingleStep(0.1)
            spin_val.setDecimals(4)
            spin_val.setFont(FONT)
            spin_val.setMinimumHeight(36)
            spin_val.setMinimumWidth(120)
            g_layout.addWidget(spin_val)

            g_layout.addSpacing(16)

            lbl_method = QLabel("Метод:")
            lbl_method.setFont(FONT)
            g_layout.addWidget(lbl_method)

            combo = QComboBox()
            combo.addItem("Полином Ньютона", "newton")
            combo.addItem("Сплайн", "spline")
            combo.setFont(FONT)
            combo.setMinimumHeight(36)
            combo.setMinimumWidth(180)
            g_layout.addWidget(combo)

            g_layout.addSpacing(16)

            lbl_deg = QLabel("Степень:")
            lbl_deg.setFont(FONT)
            g_layout.addWidget(lbl_deg)

            spin_deg = QSpinBox()
            spin_deg.setRange(1, 4)
            spin_deg.setValue(3)
            spin_deg.setFont(FONT)
            spin_deg.setMinimumHeight(36)
            spin_deg.setMinimumWidth(70)
            g_layout.addWidget(spin_deg)

            g_layout.addStretch()

            combo.currentIndexChanged.connect(
                lambda _, c=combo, s=spin_deg, ld=lbl_deg: (
                    s.setEnabled(c.currentData() == "newton"),
                    ld.setEnabled(c.currentData() == "newton"),
                )
            )

            layout.addWidget(group)
            self.axes[ax] = (spin_val, combo, spin_deg)

        self.btn = QPushButton("Вычислить")
        self.btn.setFont(FONT)
        self.btn.setMinimumHeight(42)
        self.btn.clicked.connect(self.compute)
        layout.addSpacing(4)
        layout.addWidget(self.btn)

        result_row = QHBoxLayout()
        lbl_u = QLabel("u =")
        lbl_u.setFont(FONT)
        self.lbl_result = QLabel("—")
        self.lbl_result.setFont(FONT)
        result_row.addWidget(lbl_u)
        result_row.addWidget(self.lbl_result)
        result_row.addStretch()
        layout.addSpacing(4)
        layout.addLayout(result_row)

    def compute(self):
        params = {}
        for ax, (spin_val, combo, spin_deg) in self.axes.items():
            params[f"{ax}_value"] = spin_val.value()
            params[f"{ax}_method"] = combo.currentData()
            params[f"{ax}_degree"] = spin_deg.value()

        try:
            result = compute_interpolation(self.solver, params)
            self.lbl_result.setText(str(result))
        except NotImplementedError:
            self.lbl_result.setText("Ошибка: модель не реализована")
        except Exception as e:
            self.lbl_result.setText(f"Ошибка: {e}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec())