from email.header import Header

import pyqtgraph as pg
from solver import Solver
from reader import read_data
from PyQt6.QtWidgets import QWidget, QHBoxLayout, QVBoxLayout, QGroupBox, QLabel, QDoubleSpinBox, QGridLayout, \
    QPushButton, QMessageBox


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setMinimumHeight(1000)


        self.solver = Solver(*read_data())

        self.button = QPushButton("Решить")
        self.button.clicked.connect(self.draw_graphs)

        self.ui_setup()
        self.test_data_setup()
        # self.draw_graphs()

    def test_data_setup(self):
        spinbox = self.input_hbox

        spinbox["t0"].setValue(14)
        spinbox["tk"].setValue(450)
        spinbox["step"].setValue(1)
        spinbox["T0"].setValue(5400)
        spinbox["px"].setValue(0.04)
        spinbox["R"].setValue(1)
        spinbox["l"].setValue(10)

    def ui_setup(self):
        self.input_setup()
        self.graphs_setup()

        vbox = QVBoxLayout()
        vbox.addWidget(self.input_box)
        vbox.addWidget(self.graph_box)

        self.setLayout(vbox)

    def graphs_setup(self):
        gbox = QGroupBox()

        all_garph = {
            "T": pg.PlotWidget(),
            "p": pg.PlotWidget(),
            "sigma": pg.PlotWidget(),
            "q": pg.PlotWidget(),
            "Rd": pg.PlotWidget(),
            "Fr": pg.PlotWidget(),
        }
        self.all_graph = all_garph

        grid = QGridLayout(gbox)
        grid.addWidget(all_garph["T"], 0, 0)
        grid.addWidget(all_garph["p"], 0, 1)
        grid.addWidget(all_garph["sigma"], 1, 0)
        grid.addWidget(all_garph["q"], 1, 1)
        grid.addWidget(all_garph["Rd"], 2, 0)
        grid.addWidget(all_garph["Fr"], 2, 1)

        self.graph_box = gbox


    def input_setup(self):
        input_box = QGroupBox()
        spinboxes = QHBoxLayout(input_box)
        self.input_hbox: dict[str, QDoubleSpinBox] = { }

        headers = ["t0", "tk", "step", "T0", "px", "R", "l"]
        for header in headers:
            vbox = QVBoxLayout()

            label = QLabel(header)
            if header in ["t0", "tk", "step"]:
                label.setText(f"{header}, 10^-6 c")
            elif header in ["T0"]:
                label.setText(f"{header}, K")
            elif header in ["px"]:
                label.setText(f"{header}, МПа")
            elif header in ["l", "R"]:
                label.setText(f"{header}, cм")


            spinbox = QDoubleSpinBox()
            spinbox.setMinimumWidth(120)
            spinbox.setRange(0, 1_000)
            self.input_hbox[header] = spinbox

            vbox.addWidget(label)
            vbox.addWidget(spinbox)
            spinboxes.addLayout(vbox)

        self.input_hbox["T0"].setRange(0, 10_000)
        spinboxes.addWidget(self.button)
        self.input_box = input_box

    def get_data(self):
        spinbox = self.input_hbox

        t0 = spinbox["t0"].value()
        tk = spinbox["tk"].value()
        t_step = spinbox["step"].value()
        T0 = spinbox["T0"].value()
        R = spinbox["R"].value()
        l = spinbox["l"].value()
        px = spinbox["px"].value()

        return self.solver.solve(t0, tk, t_step, T0, R, l, px)

    def draw_graphs(self):
        data = self.get_data()
        for header in ["T", "p", "sigma", "q", "Rd", "Fr"]:
            self.all_graph[header].plot(data["t"], data[header])
            self.all_graph[header].setTitle(f"{header}(t)", size="20pt")
            print(f"{header}: {data[header]}")




