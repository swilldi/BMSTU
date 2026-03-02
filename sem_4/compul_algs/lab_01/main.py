from PyQt6.QtWidgets import QApplication
from UI import MainWindow

app = QApplication([])
window = MainWindow()
window.show()
app.exec()
