"""Embedded live radar plot workspace with detachable/maximizable plots."""

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (
    QDialog,
    QFrame,
    QGridLayout,
    QHBoxLayout,
    QLabel,
    QPushButton,
    QSizePolicy,
    QVBoxLayout,
    QWidget,
)


class PlotPanel(QFrame):
    """A plot card that can temporarily detach its plot into a large window."""

    def __init__(self, title, plot_widget, description="", object_name=""):
        super().__init__()
        self.setObjectName("RadarPlotPanel")
        self.setMinimumSize(300, 220)
        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.plot_widget = plot_widget
        self.title_text = title
        self._floating_dialog = None

        root = QVBoxLayout(self)
        root.setContentsMargins(10, 8, 10, 10)
        root.setSpacing(6)

        header = QHBoxLayout()
        title_label = QLabel(title)
        title_label.setObjectName("RadarPlotTitle")
        header.addWidget(title_label)
        header.addStretch(1)
        self.float_button = QPushButton("Pop out  ↗")
        self.float_button.setToolTip("Open this live plot in a separate resizable window")
        self.float_button.setObjectName("PlotFloatButton")
        self.float_button.clicked.connect(self.pop_out)
        header.addWidget(self.float_button)
        root.addLayout(header)

        if description:
            description_label = QLabel(description)
            description_label.setObjectName("RadarPlotDescription")
            description_label.setWordWrap(True)
            root.addWidget(description_label)

        self.plot_container = QWidget()
        self.plot_layout = QVBoxLayout(self.plot_container)
        self.plot_layout.setContentsMargins(0, 0, 0, 0)
        self.plot_layout.addWidget(plot_widget)
        root.addWidget(self.plot_container, 1)

    def pop_out(self):
        if self._floating_dialog is not None:
            self._floating_dialog.showNormal()
            self._floating_dialog.raise_()
            self._floating_dialog.activateWindow()
            return

        self.plot_layout.removeWidget(self.plot_widget)
        self._floating_dialog = QDialog(self.window())
        self._floating_dialog.setWindowTitle(f"SPARC mmWave Studio — {self.title_text}")
        self._floating_dialog.setWindowFlag(Qt.Window, True)
        self._floating_dialog.setMinimumSize(800, 560)
        dialog_layout = QVBoxLayout(self._floating_dialog)
        dialog_layout.setContentsMargins(8, 8, 8, 8)
        dialog_layout.addWidget(self.plot_widget)
        self._floating_dialog.finished.connect(self._restore_plot)
        self._floating_dialog.showMaximized()

    def _restore_plot(self, _result=None):
        if self._floating_dialog is None:
            return
        dialog = self._floating_dialog
        self._floating_dialog = None
        dialog_layout = dialog.layout()
        if dialog_layout is not None:
            dialog_layout.removeWidget(self.plot_widget)
        self.plot_widget.setParent(self.plot_container)
        self.plot_layout.addWidget(self.plot_widget)
        dialog.deleteLater()


class PlotWorkspace(QWidget):
    """Responsive 3-plot arrangement for the Live Radar / Signal Analysis tab."""

    def __init__(self, parent=None):
        super().__init__(parent)
        root = QVBoxLayout(self)
        root.setContentsMargins(12, 12, 12, 12)
        root.setSpacing(10)

        intro = QHBoxLayout()
        heading = QLabel("Live signal analysis")
        heading.setObjectName("PageHeading")
        intro.addWidget(heading)
        intro.addStretch(1)
        hint = QLabel("Use Pop out to maximize any plot independently")
        hint.setObjectName("PageDescription")
        intro.addWidget(hint)
        root.addLayout(intro)

        self.grid = QGridLayout()
        self.grid.setContentsMargins(0, 0, 0, 0)
        self.grid.setHorizontalSpacing(10)
        self.grid.setVerticalSpacing(10)
        self.grid.setColumnStretch(0, 1)
        self.grid.setColumnStretch(1, 1)
        self.grid.setRowStretch(0, 3)
        self.grid.setRowStretch(1, 4)
        root.addLayout(self.grid, 1)
        self.panels = {}

    def add_plot(self, title, plot_widget, description, key):
        panel = PlotPanel(title, plot_widget, description, key)
        if key == "range_profile":
            self.grid.addWidget(panel, 0, 0, 1, 2)
        elif key == "range_doppler":
            self.grid.addWidget(panel, 1, 0)
        elif key == "range_azimuth":
            self.grid.addWidget(panel, 1, 1)
        else:
            row = len(self.panels) // 2
            col = len(self.panels) % 2
            self.grid.addWidget(panel, row, col)
        self.panels[key] = panel
        return panel
