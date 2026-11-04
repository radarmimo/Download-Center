"""Modern SPARC application shell around the existing, feature-complete radar UI.

The legacy radar configuration widgets and callbacks are deliberately retained
in legacy_window.py in this first migration step.  This keeps existing sensor
configuration behaviour intact while separating the application shell and
navigation from the large legacy UI implementation.
"""
from pathlib import Path

from PyQt5.QtCore import Qt, QThread, QTimer, pyqtSignal
from PyQt5.QtGui import QIcon, QPixmap, QFont
from PyQt5.QtWidgets import (
    QFrame, QHBoxLayout, QLabel, QMainWindow, QPushButton, QSizePolicy,
    QStackedWidget, QTabWidget, QVBoxLayout, QWidget, QGridLayout,
    QDialog, QToolButton, QScrollArea, QSizePolicy, QProgressBar, QApplication,
    QSplitter,
)

from .legacy_window import MainWindow as LegacyMainWindow
from ..core.timing_diagnostics import calculate_timing_metrics


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
        app = QApplication.instance()
        if app is not None:
            ui_font = QFont("Segoe UI", 9)
            ui_font.setStyleStrategy(QFont.PreferAntialias)
            app.setFont(ui_font)
        self.setWindowIcon(QIcon(str(LOGO_PATH)))
        # Allow the application to fit smaller laptop displays; page content
        # uses scroll areas where vertical space is limited.
        self.setMinimumSize(800, 560)
        self.resize(1280, 800)

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

        # Unified application header: brand identity and global radar selectors
        # share one aligned toolbar instead of appearing as disconnected blocks.
        header = QFrame()
        header.setObjectName("AppHeader")
        header.setMinimumHeight(88)
        header_layout = QHBoxLayout(header)
        header_layout.setContentsMargins(20, 10, 22, 10)
        header_layout.setSpacing(18)

        logo = QLabel()
        logo.setObjectName("BrandLogo")
        if LOGO_PATH.exists():
            pixmap = QPixmap(str(LOGO_PATH))
            logo.setPixmap(pixmap.scaledToHeight(44, Qt.SmoothTransformation))
        logo.setFixedWidth(92)
        logo.setAlignment(Qt.AlignLeft | Qt.AlignVCenter)
        header_layout.addWidget(logo)

        brand_text = QVBoxLayout()
        brand_text.setContentsMargins(0, 0, 0, 0)
        brand_text.setSpacing(2)
        title = QLabel("mmWave Radar Studio")
        title.setObjectName("AppTitle")
        subtitle = QLabel("SPARC  /  Radar configuration and visualization")
        subtitle.setObjectName("AppSubtitle")
        brand_text.addWidget(title)
        brand_text.addWidget(subtitle)
        header_layout.addLayout(brand_text, 1)

        header_separator = QFrame()
        header_separator.setObjectName("HeaderSeparator")
        header_separator.setFrameShape(QFrame.VLine)
        header_separator.setFixedHeight(46)
        header_layout.addWidget(header_separator)

        platform_group = self._header_selector(
            "RADAR PLATFORM", self.select_radar_combo_box, "PlatformSelector"
        )
        preset_group = self._header_selector(
            "CONFIGURATION PRESET", self.select_default_best_Config_combo_box, "PresetSelector"
        )
        header_layout.addWidget(platform_group)
        header_layout.addWidget(preset_group)

        # Main actions are placed in a guided workflow on the Live Radar page.
        # Loading a CFG is deliberately separated from serial-port connection.

        # Main navigation and content stack.
        shell = QWidget()
        shell_layout = QVBoxLayout(shell)
        shell_layout.setContentsMargins(0, 0, 0, 0)
        shell_layout.setSpacing(0)
        shell_layout.addWidget(header)

        # Main content occupies the available central area.  Workspace
        # navigation is deliberately placed in a full-width bottom bar rather
        # than a vertical sidebar, giving the radar editor and plots more room.
        self.page_stack = QStackedWidget()
        self.page_stack.setObjectName("PageStack")
        self.page_stack.setMinimumWidth(0)
        self.navigation_buttons = []

        # Configuration page: port management and the full CFG editor.
        config_page = QWidget()
        config_layout = QVBoxLayout(config_page)
        config_toolbar = QFrame()
        config_toolbar.setObjectName("WorkflowPanel")
        config_toolbar_layout = QHBoxLayout(config_toolbar)
        config_toolbar_layout.setContentsMargins(12, 8, 12, 8)
        config_hint = QLabel("Connect command and data UART ports; configure advanced serial settings here.")
        config_hint.setObjectName("PanelTitle")
        config_hint.setWordWrap(True)
        config_toolbar_layout.addWidget(config_hint)
        config_layout.addWidget(config_toolbar)

        # Device setup and diagnostics are one workspace: connection, UART
        # configuration and sensor/display diagnostics are related tasks.
        # Keep baud-rate selectors directly in this page rather than hiding
        # them in a separate Diagnostics navigation item.
        advanced_bar = QFrame()
        advanced_bar.setObjectName("AdvancedBar")
        adv_layout = QHBoxLayout(advanced_bar)
        adv_layout.setContentsMargins(12, 8, 12, 8)
        adv_layout.setSpacing(10)
        advanced_title = QLabel("SERIAL COMMUNICATION")
        advanced_title.setObjectName("NavCaption")
        adv_layout.addWidget(advanced_title)
        adv_layout.addWidget(self._field_label("Command baud rate"))
        adv_layout.addWidget(self.select_commad_baudrate_combo_box)
        adv_layout.addSpacing(14)
        adv_layout.addWidget(self._field_label("Data baud rate"))
        adv_layout.addWidget(self.select_data_baudrate_combo_box)
        adv_layout.addStretch(1)
        config_layout.addWidget(advanced_bar)

        config_tabs = QTabWidget()
        config_tabs.setObjectName("DeviceSetupTabs")
        config_tabs.setDocumentMode(True)
        config_tabs.addTab(legacy_tabs["Serial Ports"], "Ports & Console")
        config_tabs.addTab(legacy_tabs["Frame Content"], "Frame & Sensor Diagnostics")
        config_tabs.addTab(legacy_tabs["Settings"], "Display Diagnostics")
        config_layout.addWidget(config_tabs, 1)

        # Radar Control is a unified configuration-and-operation workspace.
        # Users can edit the CFG and immediately connect/send/start without
        # navigating between separate tabs.
        live_page = QWidget()
        live_layout = QVBoxLayout(live_page)
        live_layout.setContentsMargins(10, 8, 10, 10)
        live_layout.setSpacing(8)

        cfg_toolbar = QFrame()
        cfg_toolbar.setObjectName("WorkflowPanel")
        cfg_toolbar_layout = QHBoxLayout(cfg_toolbar)
        cfg_toolbar_layout.setContentsMargins(12, 7, 12, 7)
        cfg_title = QLabel("Radar configuration")
        cfg_title.setObjectName("PanelTitle")
        cfg_description = QLabel("Load, edit, validate and save the TI configuration, then apply it to the connected radar.")
        cfg_description.setObjectName("PageDescription")
        cfg_description.setWordWrap(True)
        self.browse_config_button.setText("Load .cfg")
        self.browse_config_button.setObjectName("SecondaryButton")
        self.browse_config_button.setMinimumHeight(34)
        cfg_toolbar_layout.addWidget(cfg_title)
        cfg_toolbar_layout.addSpacing(10)
        cfg_toolbar_layout.addWidget(cfg_description, 1)
        cfg_toolbar_layout.addWidget(self.browse_config_button)
        live_layout.addWidget(cfg_toolbar)

        workflow = QFrame()
        workflow.setObjectName("WorkflowPanel")
        workflow_layout = QHBoxLayout(workflow)
        workflow_layout.setContentsMargins(12, 8, 12, 8)
        workflow_layout.setSpacing(8)
        workflow_heading = QLabel("DEVICE CONTROL")
        workflow_heading.setObjectName("NavCaption")
        workflow_layout.addWidget(workflow_heading)
        for button, text, object_name in (
            (self.connect_button, "Connect device", "SecondaryButton"),
            (self.send_button, "Send configuration + start", "PrimaryButton"),
            (self.stop_device_button, "Stop radar", "DangerButton"),
        ):
            button.setText(text)
            button.setObjectName(object_name)
            button.setMinimumHeight(36)
            button.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
            workflow_layout.addWidget(button, 1)
        live_layout.addWidget(workflow)

        self.workflow_status = QLabel("Load or edit a CFG file, connect both UART ports, then send the configuration to start the radar.")
        self.workflow_status.setObjectName("PageDescription")
        self.workflow_status.setWordWrap(True)
        live_layout.addWidget(self.workflow_status)

        # Move the raw command table and Save CFG action out of the editor
        # page. They are presented together with the execution transcript in
        # the lower tabbed workspace, avoiding a long command table consuming
        # vertical space needed by the editable radar-parameter tabs.
        command_table = self.command_table
        if command_table.parentWidget() is not None:
            command_table.parentWidget().layout().removeWidget(command_table)
        command_table.setParent(None)
        save_cfg_button = self.save_cfg_push_button
        if save_cfg_button.parentWidget() is not None:
            save_cfg_button.parentWidget().layout().removeWidget(save_cfg_button)
        save_cfg_button.setParent(None)

        # Reuse the original CFG editor widget directly in this workspace.
        # Its existing tables, editing callbacks and dependent-parameter
        # calculations are intentionally preserved. A page removed from a
        # QTabWidget is hidden by Qt; explicitly show it after reparenting.
        cfg_editor_page = legacy_tabs["Configuration"]
        cfg_editor_page.setMinimumHeight(0)
        cfg_editor_page.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        cfg_editor_page.show()
        self.cfg_editor_page = cfg_editor_page

        # The original editor contains several stacked tables and action rows.
        # On smaller displays, compressing that page caused its controls to
        # overlap. Keep the editor intact and scroll its contents instead.
        self.cfg_editor_scroll = QScrollArea()
        self.cfg_editor_scroll.setObjectName("CfgEditorScroll")
        self.cfg_editor_scroll.setWidgetResizable(True)
        self.cfg_editor_scroll.setFrameShape(QFrame.NoFrame)
        self.cfg_editor_scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.cfg_editor_scroll.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.cfg_editor_scroll.setWidget(cfg_editor_page)

        # Keep the complete CFG editor in the main Radar Control workspace.
        # The command-list and execution-log views are appended to the same
        # tab bar as Chirp / Field of View / Display / EVM Info below, so the
        # user has one coherent configuration workspace rather than two
        # separate tab strips.
        live_layout.addWidget(self.cfg_editor_scroll, 1)

        # Unified visualization workspace: signal plots, 3D point cloud and
        # detected-points table are grouped under one main navigation item.
        # The tab strip is placed at the bottom to preserve the familiar
        # visualization canvas and reduce top-of-page chrome.
        visualization_page = QWidget()
        visualization_layout = QVBoxLayout(visualization_page)
        visualization_layout.setContentsMargins(12, 12, 12, 12)
        visualization_layout.setSpacing(8)
        visualization_header = QHBoxLayout()
        visualization_heading = QLabel("Radar visualization")
        visualization_heading.setObjectName("PageHeading")
        visualization_description = QLabel(
            "Signal profiles, range-angle maps, 3D detections and point measurements")
        visualization_description.setObjectName("PageDescription")
        self.popout_point_cloud_button = QPushButton("Open 3D viewer")
        self.popout_point_cloud_button.setObjectName("SecondaryButton")
        self.popout_point_cloud_button.clicked.connect(self.open_point_cloud_viewer)
        visualization_header.addWidget(visualization_heading)
        visualization_header.addStretch(1)
        visualization_header.addWidget(visualization_description)
        visualization_header.addWidget(self.popout_point_cloud_button)
        visualization_layout.addLayout(visualization_header)

        self.visualization_tabs = QTabWidget()
        self.visualization_tabs.setObjectName("VisualizationTabs")
        self.visualization_tabs.setDocumentMode(True)
        self.visualization_tabs.setTabPosition(QTabWidget.South)
        self.visualization_tabs.addTab(legacy_tabs["3D scatter plot"], "3D Point Cloud")
        self.visualization_tabs.addTab(legacy_tabs["Detected Points"], "Detected Points")
        visualization_layout.addWidget(self.visualization_tabs, 1)
        self.visualization_page = visualization_page

        # Keep the detailed command transcript available for troubleshooting,
        # but remove it from the primary configuration/operation workspace.
        command_panel = QFrame()
        command_panel.setObjectName("CommandPanel")
        command_panel_layout = QVBoxLayout(command_panel)
        command_panel_layout.setContentsMargins(12, 8, 12, 8)
        command_panel_layout.setSpacing(6)
        command_header = QHBoxLayout()
        command_title = QLabel("Command execution log")
        command_title.setObjectName("PanelTitle")
        self.command_execution_status = QLabel("Waiting for configuration")
        self.command_execution_status.setObjectName("ExecutionStatus")
        command_header.addWidget(command_title)
        command_header.addStretch(1)
        command_header.addWidget(self.command_execution_status)
        command_panel_layout.addLayout(command_header)
        self.command_progress = QProgressBar()
        self.command_progress.setObjectName("CommandProgress")
        self.command_progress.setRange(0, 100)
        self.command_progress.setValue(0)
        self.command_progress.setTextVisible(True)
        self.command_progress.setFormat("No configuration sequence running")
        self.command_progress.setMaximumHeight(17)
        command_panel_layout.addWidget(self.command_progress)
        self.command_textbox.setReadOnly(True)
        self.command_textbox.setMinimumHeight(82)
        self.command_textbox.setMaximumHeight(16777215)
        self.command_textbox.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.command_textbox.setPlaceholderText("Commands, device responses and errors will appear here during configuration transmission…")
        command_panel_layout.addWidget(self.command_textbox)
        command_panel.setMinimumHeight(170)
        command_panel.setMaximumHeight(16777215)
        command_panel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.command_panel = command_panel

        # Add command management and execution feedback directly to the
        # original CFG editor tab bar. This preserves the editor's existing
        # parameter tabs and all callbacks while consolidating navigation.
        cfg_commands_page = QWidget()
        cfg_commands_layout = QVBoxLayout(cfg_commands_page)
        cfg_commands_layout.setContentsMargins(8, 8, 8, 8)
        cfg_commands_layout.setSpacing(6)
        cfg_commands_heading = QLabel("Commands generated from the current configuration")
        cfg_commands_heading.setObjectName("PageDescription")
        command_table.setMinimumHeight(120)
        command_table.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        cfg_commands_layout.addWidget(cfg_commands_heading)
        cfg_commands_layout.addWidget(command_table, 1)
        save_cfg_button.setObjectName("SecondaryButton")
        save_cfg_button.setMinimumHeight(34)
        cfg_commands_layout.addWidget(save_cfg_button)
        self.tab_widget_cfg.addTab(cfg_commands_page, "CFG Commands & Save")
        self.tab_widget_cfg.addTab(command_panel, "Command Execution Log")

        # Overview page with useful live values derived from the existing model.
        self.dashboard_page = self._create_dashboard_page()

        dashboard_scroll = QScrollArea()
        dashboard_scroll.setWidgetResizable(True)
        dashboard_scroll.setFrameShape(QFrame.NoFrame)
        dashboard_scroll.setWidget(self.dashboard_page)

        # Visualization is deliberately not inserted into the main page stack.
        # It opens as a dedicated second top-level window so plots and the
        # point-cloud view can use the full display without shrinking the
        # configuration workspace.
        self._main_page_index_by_nav = {0: 0, 1: 1, 2: 2}
        pages = [
            ("Radar Control", live_page),
            ("Device Setup", config_page),
            ("Overview", dashboard_scroll),
        ]
        nav_names = ["Radar Control", "Device Setup", "Overview"]
        for nav_index, (name, page) in enumerate(zip(nav_names, pages)):
            button = QPushButton(name)
            button.setObjectName("NavButton")
            button.setCheckable(True)
            button.setMinimumHeight(38)
            button.setSizePolicy(QSizePolicy.Minimum, QSizePolicy.Fixed)
            stack_index = nav_index
            button.clicked.connect(
                lambda checked=False, i=stack_index, n=nav_index: self._select_page(i, n)
            )
            self.page_stack.addWidget(page[1])
            self.navigation_buttons.append(button)

        shell_layout.addWidget(self.page_stack, 1)
        self._visualization_window = None
        self._allow_visualization_close = False

        # Bottom workspace navigation: all former sidebar elements (caption,
        # page buttons and version label) are consolidated in this footer.
        bottom_navigation = QFrame()
        bottom_navigation.setObjectName("BottomNavigation")
        bottom_navigation.setMinimumHeight(62)
        bottom_navigation.setMaximumHeight(72)
        bottom_layout = QHBoxLayout(bottom_navigation)
        bottom_layout.setContentsMargins(16, 8, 18, 8)
        bottom_layout.setSpacing(8)

        nav_caption = QLabel("WORKSPACE")
        nav_caption.setObjectName("BottomNavCaption")
        bottom_layout.addWidget(nav_caption)
        bottom_layout.addSpacing(8)
        for button in self.navigation_buttons:
            bottom_layout.addWidget(button)
        bottom_layout.addStretch(1)

        version = QLabel("SPARC  ·  v2.0")
        version.setObjectName("BottomVersionLabel")
        bottom_layout.addWidget(version, 0, Qt.AlignVCenter)
        shell_layout.addWidget(bottom_navigation)
        self.setCentralWidget(shell)
        self._select_page(0)
        self.connect_button.setEnabled(True)
        # Sending is only available after both UART ports are connected and a
        # configuration is present. A preloaded default preset alone must not
        # make the action look ready at application startup.
        self.send_button.setText("Send configuration + start")
        self.send_button.setEnabled(False)
        self.send_button.setToolTip("Connect both radar serial ports before starting the sensor.")
        self.send_button.setIcon(QIcon())
        self.send_button.setAutoDefault(False)
        self.send_button.setDefault(False)
        self.stop_device_button.setEnabled(False)
        self._refresh_action_states()

        # The previous central widget is now empty of all reparented content.
        if old_central is not None:
            old_central.deleteLater()

    def _refresh_action_states(self):
        """Keep operation controls synchronized with device/configuration state."""
        connected = bool(
            getattr(self, "command_port_connected", False)
            and getattr(self, "data_port_connected", False)
        )
        has_configuration = bool(
            getattr(self, "command_table", None) is not None
            and self.command_table.rowCount() > 0
        )
        ready = connected and has_configuration
        if hasattr(self, "send_button"):
            self.send_button.setEnabled(ready)
            if not connected:
                reason = "Connect both command and data ports to enable this action."
            elif not has_configuration:
                reason = "Load a CFG file or select a configuration preset first."
            else:
                reason = "Send the loaded configuration and start radar acquisition."
            self.send_button.setToolTip(reason)
        if hasattr(self, "stop_device_button"):
            running = bool(getattr(self, "sensor_running", False))
            self.stop_device_button.setEnabled(connected and running)

    def attach_radar_visualizations(self, radar_application):
        """Add each live signal plot as an individual tab in Visualization."""
        from .plot_workspace import PlotPanel

        # Remove previously attached signal-plot tabs before rebuilding them.
        plot_titles = {"Range Profile", "Range-Doppler", "Range-Azimuth"}
        for index in reversed(range(self.visualization_tabs.count())):
            if self.visualization_tabs.tabText(index) in plot_titles:
                widget = self.visualization_tabs.widget(index)
                self.visualization_tabs.removeTab(index)
                # Detach the Matplotlib/Qt plot before deleting its old panel;
                # otherwise deleting the panel would also destroy the plot.
                if hasattr(widget, "plot_widget"):
                    widget.plot_layout.removeWidget(widget.plot_widget)
                    widget.plot_widget.setParent(None)
                widget.deleteLater()

        plot_definitions = [
            ("Range Profile", radar_application.range_profile_figure,
             "Range profile and noise profile across the measured range."),
            ("Range-Doppler", radar_application.range_doppler_heatmap_figure,
             "Range versus radial velocity; Doppler bins are centered around zero."),
            ("Range-Azimuth", radar_application.range_azimuth_heatmap_figure,
             "Static range-angle response across the radar field of view."),
        ]
        # Keep signal-analysis tabs first, followed by the 3D view and table.
        for index, (title, plot_widget, description) in enumerate(plot_definitions):
            panel = PlotPanel(title, plot_widget, description, title.lower().replace(" ", "_"))
            self.visualization_tabs.insertTab(index, panel, title)
        self.visualization_tabs.setCurrentIndex(0)

    def open_point_cloud_viewer(self):
        """Pop the live 3D point-cloud widget into a standalone viewer window."""
        if getattr(self, "_point_cloud_dialog", None) is not None:
            self._point_cloud_dialog.raise_()
            self._point_cloud_dialog.activateWindow()
            return
        widget = getattr(self, "three_d_plot_widget", None)
        if widget is None:
            return
        self.three_d_plot_layout.removeWidget(widget)
        dialog = QDialog(self)
        dialog.setWindowTitle("SPARC mmWave Studio — 3D Point Cloud Viewer")
        dialog.setWindowFlag(Qt.Window, True)
        dialog.setMinimumSize(800, 600)
        dialog_layout = QVBoxLayout(dialog)
        dialog_layout.setContentsMargins(8, 8, 8, 8)
        dialog_layout.addWidget(widget)
        self._point_cloud_dialog = dialog

        def restore_point_cloud(_result=None):
            if getattr(self, "_point_cloud_dialog", None) is not dialog:
                return
            dialog_layout.removeWidget(widget)
            widget.setParent(self.three_d_plot_tab)
            self.three_d_plot_layout.addWidget(widget)
            self._point_cloud_dialog = None

        dialog.finished.connect(restore_point_cloud)
        dialog.showMaximized()

    def update_command_execution(self, status=None, progress=None, progress_text=None):
        """Update the command sequence feedback available under Diagnostics → Command Log."""
        if status is not None and hasattr(self, "command_execution_status"):
            self.command_execution_status.setText(status)
        if progress is not None and hasattr(self, "command_progress"):
            self.command_progress.setValue(max(0, min(100, int(progress))))
        if progress_text is not None and hasattr(self, "command_progress"):
            self.command_progress.setFormat(progress_text)

    @staticmethod
    def _header_selector(caption, combo, object_name):
        """Build a compact selector group integrated into the global header."""
        group = QFrame()
        group.setObjectName(object_name)
        group.setMinimumWidth(158 if object_name == "PlatformSelector" else 220)
        layout = QVBoxLayout(group)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(4)
        label = QLabel(caption)
        label.setObjectName("HeaderFieldCaption")
        layout.addWidget(label)
        combo.setMinimumHeight(34)
        combo.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        layout.addWidget(combo)
        return group

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
            ("idle_time", "Idle time", "—"),
            ("frame_utilization", "Frame duty cycle", "—"),
            ("rf_duty", "Aggregate RF duty cycle (est.)", "—"),
            ("configured_fps", "Configured frame rate", "—"),
            ("chirp_cycle", "Chirp repetition period", "—"),
            ("ramp_duration", "RF ramp duration", "—"),
            ("chirp_rf_duty", "RF ramp duty cycle / chirp", "—"),
            ("adc_acquisition", "ADC acquisition duration", "—"),
            ("adc_duty", "ADC acquisition duty / chirp", "—"),
            ("chirps", "Chirps per frame", "—"),
            ("tx1_duty", "TX1 duty cycle (est.)", "—"),
            ("tx2_duty", "TX2 duty cycle (est.)", "—"),
            ("tx3_duty", "TX3 duty cycle (est.)", "—"),
        ]
        for index, (key, label_text, initial) in enumerate(metrics):
            card = QFrame()
            card.setObjectName("MetricCard")
            card_layout = QVBoxLayout(card)
            card_layout.setContentsMargins(15, 13, 15, 13)
            caption = QLabel(label_text)
            caption.setObjectName("MetricCaption")
            caption.setWordWrap(True)
            value = QLabel(initial)
            value.setObjectName("MetricValue")
            value.setTextInteractionFlags(Qt.TextSelectableByMouse)
            if key == "frame_utilization":
                caption.setToolTip("Active frame time divided by frame periodicity. This is the frame-level duty cycle.")
                value.setToolTip("Frame duty cycle = active frame time / frame period × 100%.")
            elif key == "rf_duty":
                caption.setToolTip("Estimated aggregate RF-on time across configured chirps. This is not a per-transmitter duty-cycle measurement.")
                value.setToolTip("Estimated aggregate RF duty cycle = chirps per frame × ramp duration / frame period × 100%.")
            elif key == "chirp_rf_duty":
                caption.setToolTip("Ramp duration divided by chirp repetition period. This is a timing ratio, not a direct PA-on measurement.")
            elif key == "adc_duty":
                caption.setToolTip("ADC acquisition window divided by chirp repetition period. This is receiver sampling activity, not TX duty cycle.")
            card_layout.addWidget(caption)
            card_layout.addWidget(value)
            cards.addWidget(card, index // 3, index % 3)
            self.dashboard_values[key] = value
        layout.addLayout(cards)

        runtime_title = QLabel("Live acquisition performance")
        runtime_title.setObjectName("PanelTitle")
        layout.addWidget(runtime_title)
        runtime_cards = QGridLayout()
        runtime_cards.setHorizontalSpacing(12)
        runtime_cards.setVerticalSpacing(10)
        self.runtime_dashboard_values = {}
        runtime_metrics = [
            ("measured_fps", "Measured FPS"),
            ("avg_interval", "Average frame interval"),
            ("jitter", "Frame interval jitter"),
            ("minmax_interval", "Min / max interval"),
            ("missing_frames", "Missing frame numbers"),
            ("throughput", "Data throughput"),
            ("receive_state", "Data reception"),
        ]
        for index, (key, caption_text) in enumerate(runtime_metrics):
            card = QFrame()
            card.setObjectName("MetricCard")
            card_layout = QVBoxLayout(card)
            card_layout.setContentsMargins(12, 9, 12, 9)
            caption = QLabel(caption_text)
            caption.setObjectName("MetricCaption")
            caption.setWordWrap(True)
            value = QLabel("—")
            value.setObjectName("MetricValue")
            value.setTextInteractionFlags(Qt.TextSelectableByMouse)
            card_layout.addWidget(caption)
            card_layout.addWidget(value)
            runtime_cards.addWidget(card, index // 4, index % 4)
            self.runtime_dashboard_values[key] = value
        layout.addLayout(runtime_cards)
        timing_note = QLabel(
            "Per-chirp RF ramp duty = ramp duration / chirp repetition period. ADC acquisition duty = "
            "ADC sampling duration / chirp repetition period. Frame duty = active frame time / frame period. "
            "Aggregate RF duty is an estimate based on chirps per frame × ramp duration / frame period; "
            "it assumes the ramp is RF-active and is not a per-transmitter PA-on measurement. ADC duty "
            "describes receiver sampling, not transmitter activity. Live intervals are measured at complete "
            "UART packet reception and may include interface buffering."
        )
        timing_note.setObjectName("PageDescription")
        timing_note.setWordWrap(True)
        layout.addWidget(timing_note)

        note = QFrame()
        note.setObjectName("InfoPanel")
        note_layout = QVBoxLayout(note)
        note_layout.setContentsMargins(16, 14, 16, 14)
        note_title = QLabel("Getting started")
        note_title.setObjectName("PanelTitle")
        note_text = QLabel(
            "1. Load and edit a TI .cfg file directly on the Radar Control page.\n"
            "2. Select command and data COM ports under Device Setup.\n"
            "3. Use Connect device and Send configuration & start on the same Radar Control page.\n"
            "4. Open Visualization to view signal plots, the 3D point cloud and detections in a separate window.\n"
            "5. Open Diagnostics → Command Log only when you need the detailed UART transcript."
        )
        note_text.setObjectName("PanelText")
        note_text.setWordWrap(True)
        note_layout.addWidget(note_title)
        note_layout.addWidget(note_text)
        layout.addWidget(note)
        layout.addStretch(1)
        return page

    def _select_page(self, index, nav_index=None):
        """Select a main-window page while keeping Visualization independent."""
        self.page_stack.setCurrentIndex(index)
        if nav_index is None:
            nav_index = next(
                (nav_i for nav_i, stack_i in self._main_page_index_by_nav.items()
                 if stack_i == index), 0
            )
        for i, button in enumerate(self.navigation_buttons):
            button.setChecked(i == nav_index)

    def open_visualization_window(self):
        """Show the persistent companion visualization window."""
        if self._visualization_window is None:
            from PyQt5.QtWidgets import QMainWindow

            # Deliberately omit the native close-button hint. The close event
            # is also ignored so Alt+F4 or a window-manager close request cannot
            # terminate the companion window independently of the main app.
            window_flags = (
                Qt.Window | Qt.WindowTitleHint
                | Qt.WindowMinimizeButtonHint | Qt.WindowMaximizeButtonHint
            )
            window = QMainWindow(self, window_flags)
            window.setWindowTitle("SPARC | Radar Visualization")
            window.setMinimumSize(900, 650)
            window.resize(1450, 900)
            window.setAttribute(Qt.WA_DeleteOnClose, False)
            window.setCentralWidget(self.visualization_page)
            window.closeEvent = self._ignore_visualization_close
            self._visualization_window = window

        self._visualization_window.showMaximized()
        self._visualization_window.raise_()
        self._visualization_window.activateWindow()
        return self._visualization_window

    def _ignore_visualization_close(self, event):
        """Keep the companion visualization open until the main app exits."""
        if self._allow_visualization_close:
            event.accept()
        else:
            event.ignore()
            if self._visualization_window is not None:
                self._visualization_window.show()
                self._visualization_window.raise_()

    def close_visualization_for_shutdown(self):
        """Close the companion window as part of main-application shutdown."""
        if self._visualization_window is not None:
            self._allow_visualization_close = True
            self._visualization_window.close()
            self._visualization_window = None

    def set_runtime_statistics_provider(self, provider):
        """Attach the thread-safe runtime statistics snapshot provider."""
        self._runtime_statistics_provider = provider
        self._refresh_dashboard()

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

        timing = calculate_timing_metrics(params)
        self.dashboard_values["active_time"].setText(f"{timing['active_frame_ms']:.3f} ms" if timing['active_frame_ms'] else "—")
        if timing["frame_period_ms"]:
            if timing["frame_overrun"]:
                self.dashboard_values["idle_time"].setText(f"Overrun {abs(timing['idle_time_ms']):.3f} ms")
            else:
                self.dashboard_values["idle_time"].setText(f"{timing['idle_time_ms']:.3f} ms")
        else:
            self.dashboard_values["idle_time"].setText("—")
        self.dashboard_values["frame_utilization"].setText(f"{timing['frame_utilization_pct']:.1f} %" if timing['frame_period_ms'] else "—")
        self.dashboard_values["rf_duty"].setText(f"{timing['estimated_rf_duty_pct']:.1f} %*" if timing['estimated_rf_duty_pct'] else "—")
        self.dashboard_values["configured_fps"].setText(f"{timing['configured_fps']:.2f} FPS" if timing['configured_fps'] else "—")
        self.dashboard_values["chirp_cycle"].setText(f"{timing['chirp_cycle_us']:.3f} µs" if timing['chirp_cycle_us'] else "—")
        self.dashboard_values["ramp_duration"].setText(f"{timing['ramp_duration_us']:.3f} µs" if timing['ramp_duration_us'] else "—")
        self.dashboard_values["chirp_rf_duty"].setText(f"{timing['chirp_rf_duty_pct']:.2f} %*" if timing['chirp_rf_duty_pct'] else "—")
        self.dashboard_values["adc_acquisition"].setText(f"{timing['adc_acquisition_us']:.3f} µs" if timing['adc_acquisition_us'] else "—")
        self.dashboard_values["adc_duty"].setText(f"{timing['adc_duty_pct']:.2f} %" if timing['adc_duty_pct'] else "—")
        self.dashboard_values["chirps"].setText(str(timing['chirps_per_frame']) if timing['chirps_per_frame'] else "—")
        for key, metric_key in (("tx1_duty", "tx1_duty_pct"), ("tx2_duty", "tx2_duty_pct"), ("tx3_duty", "tx3_duty_pct")):
            duty = timing[metric_key]
            self.dashboard_values[key].setText(f"{duty:.2f} %*" if duty else "—")

        provider = getattr(self, "_runtime_statistics_provider", None)
        if provider is not None:
            stats = provider()
            self.runtime_dashboard_values["measured_fps"].setText(f"{stats['measured_fps']:.2f} FPS" if stats['frames_received'] > 1 else "—")
            self.runtime_dashboard_values["avg_interval"].setText(f"{stats['average_interval_ms']:.2f} ms" if stats['average_interval_ms'] else "—")
            self.runtime_dashboard_values["jitter"].setText(f"{stats['interval_jitter_ms']:.2f} ms" if stats['average_interval_ms'] else "—")
            self.runtime_dashboard_values["minmax_interval"].setText(
                f"{stats['minimum_interval_ms']:.1f} / {stats['maximum_interval_ms']:.1f} ms" if stats['average_interval_ms'] else "—")
            self.runtime_dashboard_values["missing_frames"].setText(str(stats['missing_frames']))
            self.runtime_dashboard_values["throughput"].setText(f"{stats['throughput_kBps']:.1f} kB/s")
            self.runtime_dashboard_values["receive_state"].setText("Receiving" if stats['is_receiving'] else "No recent data")
        else:
            for value in self.runtime_dashboard_values.values():
                value.setText("Waiting for radar data")

    def _apply_theme(self):
        """Apply a consistent contemporary engineering-dashboard visual theme."""
        self.setStyleSheet("""
            QMainWindow, QWidget {
                background: #f4f6fa;
                color: #182438;
                font-family: "Segoe UI", "Inter", Arial;
                font-size: 10pt;
            }
            #AppHeader {
                background: #ffffff;
                border: 0;
                border-bottom: 1px solid #dfe6ef;
            }
            #BrandLogo { background: transparent; }
            #AppTitle { color: #15243a; font-size: 20pt; font-weight: 700; }
            #AppSubtitle { color: #78869a; font-size: 8.5pt; }
            #HeaderSeparator { color: #e1e7ef; background: #e1e7ef; max-width: 1px; }
            #PlatformSelector, #PresetSelector { background: transparent; border: 0; }
            #HeaderFieldCaption { color: #718096; font-size: 7.5pt; font-weight: 700; letter-spacing: 0.6px; }
            #BottomNavigation {
                background: #17283f;
                border-top: 1px solid #263d59;
            }
            #BottomNavCaption {
                color: #91a4bb; font-size: 8pt; font-weight: 700;
                letter-spacing: 0.8px; padding: 0 8px;
            }
            QPushButton#NavButton {
                color: #c7d2e0; background: transparent; border: 0;
                border-radius: 7px; text-align: center; padding: 8px 17px;
                font-weight: 600; min-width: 92px;
            }
            QPushButton#NavButton:hover { background: #243b57; color: #ffffff; }
            QPushButton#NavButton:checked { background: #31577b; color: #ffffff; }
            #BottomVersionLabel {
                color: #91a4bb; font-size: 8pt; padding: 0 8px;
            }
            #PageStack { background: #f4f6fa; border: 0; }
            #PageHeading { color: #15243a; font-size: 21pt; font-weight: 700; }
            #PageDescription { color: #738198; font-size: 9pt; }
            #WorkflowPanel, #MetricCard, #RadarPlotPanel, #CommandPanel, #InfoPanel {
                background: #ffffff; border: 1px solid #e3e9f1; border-radius: 11px;
            }
            #PanelTitle, #RadarPlotTitle { color: #1a2a40; font-weight: 700; font-size: 9pt; }
            #PanelText { color: #53647b; }
            #MetricCaption { color: #75849a; font-size: 9pt; }
            #MetricValue { color: #172b45; font-size: 15pt; font-weight: 700; }
            #FieldLabel { color: #697991; font-size: 9pt; font-weight: 600; }
            #RadarPlotDescription { color: #7b899d; font-size: 8pt; }
            #ExecutionStatus { color: #52657e; font-size: 9pt; font-weight: 600; }
            #AdvancedBar { background: #ffffff; border: 1px solid #e3e9f1; border-radius: 9px; }
            QPushButton {
                color: #34445b; background: #ffffff;
                border: 1px solid #d8e0eb; border-radius: 8px;
                padding: 9px 14px; font-weight: 600;
            }
            QPushButton:hover { background: #f2f6fb; border-color: #bdcadb; }
            QPushButton:pressed { background: #e8eef6; }
            QPushButton:disabled {
                color: #9aa6b6; background: #edf0f4;
                border: 1px solid #e3e7ed;
            }
            QPushButton#PrimaryButton {
                color: #ffffff; background: #1769aa;
                border: 1px solid #1769aa; border-radius: 8px;
                font-weight: 700; padding: 10px 17px;
            }
            QPushButton#PrimaryButton:hover { background: #125b96; border-color: #125b96; }
            QPushButton#PrimaryButton:pressed { background: #0e4d80; }
            QPushButton#PrimaryButton:disabled {
                color: #8d99a8; background: #e9edf2;
                border-color: #dce2e9;
            }
            QPushButton#SecondaryButton {
                color: #315b83; background: #f5f8fc;
                border: 1px solid #d8e3ef; font-weight: 600;
            }
            QPushButton#SecondaryButton:hover { background: #eaf1f8; }
            QPushButton#DangerButton { color: #b54747; background: #fffafa; border-color: #efdada; }
            QPushButton#DangerButton:hover { background: #fff0f0; }
            QPushButton#PlotFloatButton { color: #315b83; background: #f6f9fc; border: 1px solid #d8e3ef; padding: 6px 11px; }
            QComboBox, QLineEdit, QSpinBox, QDoubleSpinBox {
                background: #ffffff; color: #26364d;
                border: 1px solid #d6deea; border-radius: 7px;
                padding: 7px 9px; min-height: 20px;
            }
            QComboBox:hover, QLineEdit:hover { border-color: #9eb2ca; }
            QComboBox:focus, QLineEdit:focus { border: 1px solid #4384bd; }
            QTabWidget { background: transparent; }
            QTabWidget::pane { border: 1px solid #e2e8f0; background: #ffffff; border-radius: 8px; top: -1px; }
            QTabBar { qproperty-drawBase: 0; }
            QTabBar::tab { color: #65758b; background: transparent; padding: 9px 13px; min-width: 72px; min-height: 20px; margin-right: 3px; border: 0; border-bottom: 2px solid transparent; font-weight: 600; }
            QTabBar::tab:selected { color: #1769aa; border-bottom: 2px solid #1769aa; }
            QTabBar::tab:hover { color: #244e77; background: #f0f4f9; }
            QTableWidget, QPlainTextEdit {
                font-size: 9pt;
                background: #ffffff; color: #26364d;
                alternate-background-color: #f7f9fc;
                gridline-color: #e8edf3; border: 1px solid #e0e6ee;
                border-radius: 7px;
            }
            QHeaderView::section { background: #f3f6fa; color: #53647a; padding: 6px; border: 0; border-bottom: 1px solid #e0e6ee; font-weight: 700; }
            QProgressBar#CommandProgress { border: 0; border-radius: 5px; background: #edf1f5; text-align: center; color: #42536a; min-height: 12px; }
            QProgressBar#CommandProgress::chunk { background: #26966b; border-radius: 5px; }
            QScrollBar:vertical { background: transparent; width: 10px; margin: 2px; }
            QScrollBar::handle:vertical { background: #c7d1de; border-radius: 5px; min-height: 24px; }
            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
            QStatusBar { background: #ffffff; color: #66758a; border-top: 1px solid #e3e9f1; }
        """)

