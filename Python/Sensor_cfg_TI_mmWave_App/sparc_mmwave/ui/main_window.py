"""Modern SPARC application shell around the existing, feature-complete radar UI.

The legacy radar configuration widgets and callbacks are deliberately retained
in legacy_window.py in this first migration step.  This keeps existing sensor
configuration behaviour intact while separating the application shell and
navigation from the large legacy UI implementation.
"""
from pathlib import Path

from PyQt5.QtCore import Qt, QThread, QTimer, pyqtSignal
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtWidgets import (
    QFrame, QHBoxLayout, QLabel, QMainWindow, QPushButton, QSizePolicy,
    QStackedWidget, QTabWidget, QVBoxLayout, QWidget, QGridLayout,
    QDialog, QToolButton,
)

from .legacy_window import MainWindow as LegacyMainWindow


APP_ROOT = Path(__file__).resolve().parents[2]
LOGO_PATH = APP_ROOT / "sparc_mmwave" / "resources_icon.png"


class MainWindow(LegacyMainWindow):
    """SPARC-branded dashboard/navigation with backwards-compatible widgets."""

    # Worker threads in the existing parser call update_specified_table().
    # Relay those calls to the GUI thread before touching Qt widgets.
    table_update_requested = pyqtSignal(str, object)

    def __init__(self):
        super().__init__()
        self.setWindowTitle("SPARC | mmWave Radar Studio")
        self.setWindowIcon(QIcon(str(LOGO_PATH)))
        self.setMinimumSize(1050, 700)
        self.resize(1360, 860)

        self.table_update_requested.connect(self._apply_table_update, Qt.QueuedConnection)
        self._build_application_shell()
        self._apply_theme()
        self._dashboard_timer = QTimer(self)
        self._dashboard_timer.timeout.connect(self._refresh_dashboard)
        self._dashboard_timer.start(1000)
        self._refresh_dashboard()

    # ---------- Thread-safe compatibility layer ----------
    def update_specified_table(self, table_id, content):
        if QThread.currentThread() != self.thread():
            self.table_update_requested.emit(str(table_id), content)
            return
        super().update_specified_table(table_id, content)

    def _apply_table_update(self, table_id, content):
        super().update_specified_table(table_id, content)

    # ---------- Application shell ----------
    def _build_application_shell(self):
        old_central = self.takeCentralWidget()
        old_layout = old_central.layout() if old_central else None

        # Detach existing widgets from the original vertical layout.  Their
        # underlying objects and callbacks remain intact when reparented below.
        if old_layout is not None:
            old_layout.removeItem(self.select_radar_layout)
            for widget in (self.tab_widget_main, self.browse_config_button,
                           self.connect_button, self.send_button,
                           self.stop_device_button):
                old_layout.removeWidget(widget)

        # Remove legacy tabs from their original tab widget before regrouping.
        legacy_tabs = {}
        for i in range(self.tab_widget_main.count()):
            page = self.tab_widget_main.widget(i)
            title = self.tab_widget_main.tabText(i)
            legacy_tabs[title] = page
        while self.tab_widget_main.count():
            self.tab_widget_main.removeTab(0)

        # Header with SPARC identity and the two frequently used selectors.
        header = QFrame()
        header.setObjectName("AppHeader")
        header_layout = QHBoxLayout(header)
        header_layout.setContentsMargins(18, 12, 18, 12)
        header_layout.setSpacing(14)

        logo = QLabel()
        logo.setObjectName("BrandLogo")
        if LOGO_PATH.exists():
            pixmap = QPixmap(str(LOGO_PATH))
            logo.setPixmap(pixmap.scaledToHeight(48, Qt.SmoothTransformation))
        logo.setFixedWidth(150)
        logo.setAlignment(Qt.AlignLeft | Qt.AlignVCenter)
        header_layout.addWidget(logo)

        brand_text = QVBoxLayout()
        title = QLabel("mmWave Radar Studio")
        title.setObjectName("AppTitle")
        subtitle = QLabel("Configuration · Visualization · Diagnostics")
        subtitle.setObjectName("AppSubtitle")
        brand_text.addWidget(title)
        brand_text.addWidget(subtitle)
        header_layout.addLayout(brand_text)
        header_layout.addStretch(1)

        header_layout.addWidget(self._field_label("Radar platform"))
        header_layout.addWidget(self.select_radar_combo_box)
        header_layout.addWidget(self._field_label("Configuration preset"))
        header_layout.addWidget(self.select_default_best_Config_combo_box)

        # Primary actions remain visible regardless of the selected page.
        actions = QFrame()
        actions.setObjectName("ActionBar")
        action_layout = QHBoxLayout(actions)
        action_layout.setContentsMargins(14, 8, 14, 8)
        action_layout.setSpacing(9)
        self.browse_config_button.setText("Load CFG")
        self.connect_button.setText("Connect")
        self.send_button.setText("Send configuration")
        self.stop_device_button.setText("Stop device")
        self.send_button.setObjectName("PrimaryButton")
        self.stop_device_button.setObjectName("DangerButton")
        for button in (self.browse_config_button, self.connect_button,
                       self.send_button, self.stop_device_button):
            button.setMinimumHeight(34)
            action_layout.addWidget(button)
        action_layout.addStretch(1)

        # Main navigation and content stack.
        shell = QWidget()
        shell_layout = QVBoxLayout(shell)
        shell_layout.setContentsMargins(0, 0, 0, 0)
        shell_layout.setSpacing(0)
        shell_layout.addWidget(header)
        shell_layout.addWidget(actions)

        body = QWidget()
        body_layout = QHBoxLayout(body)
        body_layout.setContentsMargins(12, 12, 12, 12)
        body_layout.setSpacing(12)

        sidebar = QFrame()
        sidebar.setObjectName("Sidebar")
        sidebar.setFixedWidth(190)
        side_layout = QVBoxLayout(sidebar)
        side_layout.setContentsMargins(8, 12, 8, 12)
        side_layout.setSpacing(6)
        nav_caption = QLabel("WORKSPACE")
        nav_caption.setObjectName("NavCaption")
        side_layout.addWidget(nav_caption)

        self.page_stack = QStackedWidget()
        self.page_stack.setObjectName("PageStack")
        self.navigation_buttons = []

        # Configuration page: port management and the full CFG editor.
        config_page = QWidget()
        config_layout = QVBoxLayout(config_page)
        config_tabs = QTabWidget()
        config_tabs.addTab(legacy_tabs["Serial Ports"], "Ports & Console")
        config_tabs.addTab(legacy_tabs["Configuration"], "CFG Editor")
        config_layout.addWidget(config_tabs)

        # Live page: the 3D scene and point/side-information tables.
        live_page = QWidget()
        live_layout = QVBoxLayout(live_page)
        self.live_tabs = QTabWidget()
        self.live_tabs.setDocumentMode(True)
        self.live_tabs.addTab(legacy_tabs["3D scatter plot"], "3D Point Cloud")
        self.live_tabs.addTab(legacy_tabs["Detected Points"], "Detected Points")
        live_layout.addWidget(self.live_tabs)

        # Diagnostics page: frame/TLV information and display tuning.
        diagnostics_page = QWidget()
        diagnostics_layout = QVBoxLayout(diagnostics_page)
        diagnostics_tabs = QTabWidget()
        diagnostics_tabs.addTab(legacy_tabs["Frame Content"], "Frame & Sensor Data")
        diagnostics_tabs.addTab(legacy_tabs["Settings"], "Display Settings")
        diagnostics_layout.addWidget(diagnostics_tabs)

        # Overview page with useful live values derived from the existing model.
        self.dashboard_page = self._create_dashboard_page()

        pages = [
            ("Overview", self.dashboard_page),
            ("Configuration", config_page),
            ("Live Radar", live_page),
            ("Diagnostics", diagnostics_page),
        ]
        for index, (name, page) in enumerate(pages):
            button = QPushButton(name)
            button.setObjectName("NavButton")
            button.setCheckable(True)
            button.clicked.connect(lambda checked=False, i=index: self._select_page(i))
            side_layout.addWidget(button)
            self.navigation_buttons.append(button)
            self.page_stack.addWidget(page)
        side_layout.addStretch(1)

        version = QLabel("SPARC · v2.0")
        version.setObjectName("VersionLabel")
        side_layout.addWidget(version)

        body_layout.addWidget(sidebar)
        body_layout.addWidget(self.page_stack, 1)
        shell_layout.addWidget(body, 1)
        self.setCentralWidget(shell)
        self._select_page(0)

        # Keep the legacy baud-rate selectors available, but move them out of
        # the always-visible header. They remain accessible under Diagnostics.
        advanced_bar = QFrame()
        advanced_bar.setObjectName("AdvancedBar")
        adv_layout = QHBoxLayout(advanced_bar)
        adv_layout.setContentsMargins(12, 6, 12, 6)
        adv_layout.addWidget(QLabel("Advanced serial settings"))
        adv_layout.addWidget(self._field_label("Command baud rate"))
        adv_layout.addWidget(self.select_commad_baudrate_combo_box)
        adv_layout.addWidget(self._field_label("Data baud rate"))
        adv_layout.addWidget(self.select_data_baudrate_combo_box)
        adv_layout.addStretch(1)
        diagnostics_layout.addWidget(advanced_bar)

        # The previous central widget is now empty of all reparented content.
        if old_central is not None:
            old_central.deleteLater()

    def attach_radar_visualizations(self, radar_application):
        """Embed the three live signal plots in the Live Radar workspace."""
        from .plot_workspace import PlotWorkspace

        if getattr(self, "plot_workspace", None) is not None:
            self.live_tabs.removeTab(self.live_tabs.indexOf(self.plot_workspace))
            self.plot_workspace.deleteLater()

        self.plot_workspace = PlotWorkspace(self)
        self.plot_workspace.add_plot(
            "Range Profile", radar_application.range_profile_figure,
            "Range profile and noise profile across the measured range.",
            "range_profile",
        )
        self.plot_workspace.add_plot(
            "Range-Doppler", radar_application.range_doppler_heatmap_figure,
            "Range versus radial velocity; Doppler bins are centered around zero.",
            "range_doppler",
        )
        self.plot_workspace.add_plot(
            "Range-Azimuth", radar_application.range_azimuth_heatmap_figure,
            "Static range-angle response across the radar field of view.",
            "range_azimuth",
        )
        self.live_tabs.insertTab(0, self.plot_workspace, "Signal Analysis")
        self.live_tabs.setCurrentWidget(self.plot_workspace)

    @staticmethod
    def _field_label(text):
        label = QLabel(text)
        label.setObjectName("FieldLabel")
        return label

    def _create_dashboard_page(self):
        page = QWidget()
        layout = QVBoxLayout(page)
        layout.setContentsMargins(18, 18, 18, 18)
        layout.setSpacing(14)

        heading = QLabel("Radar overview")
        heading.setObjectName("PageHeading")
        description = QLabel("A quick view of the selected platform and calculated configuration.")
        description.setObjectName("PageDescription")
        layout.addWidget(heading)
        layout.addWidget(description)

        cards = QGridLayout()
        cards.setHorizontalSpacing(12)
        cards.setVerticalSpacing(12)
        self.dashboard_values = {}
        metrics = [
            ("platform", "Radar platform", "—"),
            ("range", "Maximum range", "—"),
            ("range_resolution", "Range resolution", "—"),
            ("velocity", "Unambiguous velocity", "—"),
            ("frame_period", "Frame periodicity", "—"),
            ("active_time", "Active frame time", "—"),
        ]
        for index, (key, label_text, initial) in enumerate(metrics):
            card = QFrame()
            card.setObjectName("MetricCard")
            card_layout = QVBoxLayout(card)
            card_layout.setContentsMargins(15, 13, 15, 13)
            caption = QLabel(label_text)
            caption.setObjectName("MetricCaption")
            value = QLabel(initial)
            value.setObjectName("MetricValue")
            value.setTextInteractionFlags(Qt.TextSelectableByMouse)
            card_layout.addWidget(caption)
            card_layout.addWidget(value)
            cards.addWidget(card, index // 3, index % 3)
            self.dashboard_values[key] = value
        layout.addLayout(cards)

        note = QFrame()
        note.setObjectName("InfoPanel")
        note_layout = QVBoxLayout(note)
        note_layout.setContentsMargins(16, 14, 16, 14)
        note_title = QLabel("Getting started")
        note_title.setObjectName("PanelTitle")
        note_text = QLabel(
            "1. Select the radar platform and configuration preset above.\n"
            "2. Open Configuration → Ports & Console and select the command/data ports.\n"
            "3. Load a TI .cfg file, connect to the sensor, then send the configuration.\n"
            "4. Use Live Radar and Diagnostics to inspect incoming frames."
        )
        note_text.setObjectName("PanelText")
        note_text.setWordWrap(True)
        note_layout.addWidget(note_title)
        note_layout.addWidget(note_text)
        layout.addWidget(note)
        layout.addStretch(1)
        return page

    def _select_page(self, index):
        self.page_stack.setCurrentIndex(index)
        for i, button in enumerate(self.navigation_buttons):
            button.setChecked(i == index)

    def _refresh_dashboard(self):
        params = getattr(self, "radar_params", {}) or {}
        def display(key, suffix="", digits=2):
            value = params.get(key)
            if value is None or value == 0:
                return "—"
            try:
                return f"{float(value):.{digits}f}{suffix}"
            except (TypeError, ValueError):
                return str(value)

        self.dashboard_values["platform"].setText(self.select_radar_combo_box.currentText())
        self.dashboard_values["range"].setText(display("Maximum Range [m]", " m"))
        self.dashboard_values["range_resolution"].setText(display("Range Resolution [m]", " m", 3))
        self.dashboard_values["velocity"].setText(display("Unambiguous Velocity [km/h]", " km/h"))
        self.dashboard_values["frame_period"].setText(display("Frame Periodicity [ms]", " ms"))
        self.dashboard_values["active_time"].setText(display("Active Frame Time [ms]", " ms"))

    def _apply_theme(self):
        self.setStyleSheet("""
            QMainWindow, QWidget { background: #f4f6f9; color: #1f2937; font-family: 'Segoe UI', Arial; font-size: 10pt; }
            #AppHeader { background: #ffffff; border-bottom: 1px solid #dce2ea; }
            #AppTitle { color: #14263d; font-size: 17pt; font-weight: 700; }
            #AppSubtitle { color: #64748b; font-size: 9pt; }
            #ActionBar { background: #ffffff; border-bottom: 1px solid #dce2ea; }
            #Sidebar { background: #172b45; border-radius: 10px; }
            #NavCaption { color: #9fb1c8; font-size: 8pt; font-weight: 700; padding: 4px 10px 10px; }
            QPushButton#NavButton { color: #dbe6f2; background: transparent; border: 0; border-radius: 6px; text-align: left; padding: 11px 12px; font-weight: 600; }
            QPushButton#NavButton:hover { background: #29415f; }
            QPushButton#NavButton:checked { background: #31577e; color: #ffffff; }
            #VersionLabel { color: #9fb1c8; font-size: 8pt; padding: 8px; }
            #RadarPlotPanel { background: #ffffff; border: 1px solid #dce3ec; border-radius: 9px; }
            #RadarPlotTitle { color: #14263d; font-size: 11pt; font-weight: 700; }
            #RadarPlotDescription { color: #64748b; font-size: 8pt; }
            QPushButton#PlotFloatButton { color: #1769aa; background: #f4f8fc; border: 1px solid #cbdced; padding: 5px 10px; }
            QPushButton#PlotFloatButton:hover { background: #e7f1fa; }
            #PageStack { background: #ffffff; border: 1px solid #e1e6ed; border-radius: 9px; }
            #PageHeading { color: #14263d; font-size: 19pt; font-weight: 700; }
            #PageDescription { color: #64748b; }
            #MetricCard { background: #ffffff; border: 1px solid #e1e6ed; border-radius: 9px; }
            #MetricCaption { color: #64748b; font-size: 9pt; }
            #MetricValue { color: #14263d; font-size: 17pt; font-weight: 700; }
            #InfoPanel { background: #f8fafc; border: 1px solid #e1e6ed; border-radius: 9px; }
            #PanelTitle { color: #14263d; font-weight: 700; }
            #PanelText { color: #475569; line-height: 1.5; }
            #FieldLabel { color: #64748b; font-size: 9pt; }
            #AdvancedBar { background: #f8fafc; border: 1px solid #e1e6ed; border-radius: 7px; }
            QPushButton { padding: 7px 12px; border: 1px solid #cbd5e1; border-radius: 6px; background: #ffffff; }
            QPushButton:hover { background: #eef4fa; }
            QPushButton#PrimaryButton { color: white; background: #1769aa; border-color: #1769aa; font-weight: 700; }
            QPushButton#PrimaryButton:hover { background: #12598f; }
            QPushButton#DangerButton { color: #a12b2b; }
            QComboBox, QLineEdit { background: #ffffff; border: 1px solid #cbd5e1; border-radius: 5px; padding: 6px; min-width: 90px; }
            QTabWidget::pane { border: 1px solid #e1e6ed; background: #ffffff; }
            QTabBar::tab { background: #edf1f5; padding: 8px 13px; margin-right: 2px; }
            QTabBar::tab:selected { background: #ffffff; color: #1769aa; border-bottom: 2px solid #1769aa; }
            QTableWidget, QPlainTextEdit { background: #ffffff; alternate-background-color: #f8fafc; gridline-color: #e2e8f0; }
            QHeaderView::section { background: #edf2f7; padding: 6px; border: 0; border-bottom: 1px solid #d8e0e9; font-weight: 600; }
            QStatusBar { background: #ffffff; border-top: 1px solid #dce2ea; }
        """)
