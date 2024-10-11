import time
import serial.tools.list_ports
from PyQt5.QtWidgets import QMainWindow, QPushButton, QTableWidget, QTableWidgetItem, QVBoxLayout, \
    QWidget, QCheckBox, QStatusBar, QLabel, QPlainTextEdit, QTabWidget, QHBoxLayout, QSpacerItem, QSizePolicy, \
    QLineEdit
from PyQt5.QtGui import QPainter, QBrush
from PyQt5.QtCore import Qt
import serial
from PyQt5.QtWidgets import QFileDialog, QMessageBox
# import re

# commands = [
#     'sensorStop',
#     'flushCfg',
#     'dfeDataOutputMode 1',
#     'channelCfg 15 5 0',
#     'adcCfg 2 1',
#     'adcbufCfg -1 0 1 1 1',
#     'profileCfg 0 77 8 7 13.12 0 0 30 1 64 12499 0 0 30',
#     'chirpCfg 0 0 0 0 0 0 0 1',
#     'chirpCfg 1 1 0 0 0 0 0 4',
#     'frameCfg 0 1 16 0 100 1 0',
#     'lowPower 0 0',
#     'guiMonitor -1 1 1 0 0 0 1',
#     'cfarCfg -1 0 2 8 4 3 0 15 1',
#     'cfarCfg -1 1 0 4 2 3 1 15 1',
#     'multiObjBeamForming -1 1 0.5',
#     'clutterRemoval -1 0',
#     'calibDcRangeSig -1 0 -5 8 256',
#     'extendedMaxVelocity -1 0',
#     'lvdsStreamCfg -1 0 0 0',
#     'compRangeBiasAndRxChanPhase 0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0',
#     'measureRangeBiasAndRxChanPhase 0 1.5 0.2',
#     'CQRxSatMonitor 0 3 4 15 0',
#     'CQSigImgMonitor 0 31 4',
#     'analogMonitor 0 0',
#     'aoaFovCfg -1 -90 90 -90 90',
#     'cfarFovCfg -1 0 0 49.99',
#     'cfarFovCfg -1 1 -23.05 23.05',
#     'calibData 0 0 0',
#     'sensorStart'
# ]

class CircleWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setMinimumSize(20, 20)
        self.connection_status = "Unavailable"  # Default status is "Unavailable"
        self.setToolTip("Connection status: Unavailable")
        self.command_port_name = ''  # Initialize command port name variable
        self.data_port_name = ''

    def set_status(self, status):
        self.connection_status = status
        self.setToolTip(f"Connection status: {status}")
        self.update()  # Trigger repaint

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        if self.connection_status == "Connected":
            painter.setBrush(QBrush(Qt.green))
        elif self.connection_status == "Disconnected":
            painter.setBrush(QBrush(Qt.red))
        else:
            painter.setBrush(QBrush(Qt.gray))

        painter.drawEllipse(0, 0, 20, 20)

# UI class
class SensorSetupUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Main Window")

        # Create a button to refresh the list of serial ports
        self.refresh_button = QPushButton("Refresh Serial Ports")
        # self.refresh_button.setStyleSheet("background-color: #f0f0f0; color: #808080; border: 1px solid #d0d0d0;")
        # self.refresh_button.setEnabled(False)
        self.refresh_button.clicked.connect(self.refresh_serial_ports)

        self.connect_button = QPushButton("Connect")
        self.connect_button.clicked.connect(self.connect_checked_ports)

        # Create a table to display serial ports
        self.table = QTableWidget()
        self.table.setColumnCount(6)  # Add two additional columns for checkboxes

        # Add the columns and labels
        self.table.setHorizontalHeaderLabels(["Port", "Data", "Command", "Description", "Manufacturer", "Hardware ID"])

        # Set the width of the Description column
        self.table.setColumnWidth(3, 300)  # Adjust the width as needed

        # Create circle widgets for connection status
        self.data_circle = CircleWidget()
        self.command_circle = CircleWidget()

        # Create labels for displaying port statuses
        self.data_status_label = QLabel("Data Port: Unavailable")
        self.command_status_label = QLabel("Command Port: Unavailable")

        # Create a plain text edit for entering commands
        self.command_textbox = QPlainTextEdit()
        # self.command_textbox.setPlaceholderText("Enter commands here...")

        # Create a button to load configuration to the device
        self.browse_config_button = QPushButton("Browse Config (*.CFG) ...")
        self.browse_config_button.clicked.connect(self.browse_configuration)

        # Create a button to send configuration to the device
        self.send_button = QPushButton("Send Configuration")
        self.send_button.clicked.connect(self.send_configuration)
        self.send_button.setEnabled(False)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.chirp_cfg_table = QTableWidget()
        self.chirp_cfg_caption = QLabel("<font color='blue'><b>Chirp Configuration</b>")
        self.chirp_cfg_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.chirp_cfg_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.chirp_cfg_table.setColumnWidth(1, 100)
        self.chirp_cfg_table.setHorizontalHeaderLabels(["Parameter", "Value"])

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.radar_cfg_table = QTableWidget()
        self.radar_cfg_caption = QLabel("<font color='blue'><b>Radar Parameters</b></font>")
        self.radar_cfg_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.radar_cfg_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.radar_cfg_table.setColumnWidth(1, 100)
        self.radar_cfg_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.frame_table_caption = QLabel("<font color='green'><b>Frame Content</b></font>")
        self.frame_table = QTableWidget()
        self.frame_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.frame_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.frame_table.setColumnWidth(1, 100)
        self.frame_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.statistics_table_caption = QLabel("<font color='green'><b>Statistics Content</b></font>")
        self.statistics_table = QTableWidget()
        self.statistics_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.statistics_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.statistics_table.setColumnWidth(1, 100)
        self.statistics_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.temperature_table_caption = QLabel("<font color='magenta'><b>Temperature</b></font>")
        self.temperature_table = QTableWidget()
        self.temperature_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.temperature_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.temperature_table.setColumnWidth(1, 100)
        self.temperature_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.tab_widget = QTabWidget()
        # Layout setup
        self.serial_port_tab = QWidget()
        button_layout = QHBoxLayout()
        button_layout.addWidget(self.refresh_button)
        button_layout.addWidget(self.connect_button)

        # Create a vertical layout for the serial port tab
        self.serial_port_layout = QVBoxLayout(self.serial_port_tab)
        self.serial_port_layout.addLayout(button_layout)  # Add the button layout
        self.serial_port_layout.addWidget(self.table)
        self.serial_port_layout.addWidget(self.browse_config_button)
        self.serial_port_layout.addWidget(self.send_button)
        self.serial_port_layout.addWidget(self.command_textbox)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Add the frame table to the frame header tab
        self.settings_tab = QWidget()
        self.checkbox1 = QCheckBox("Checkbox 1")
        self.checkbox2 = QCheckBox("Checkbox 2")

        self.editbox = QLineEdit()
        # Create a table to show parameters
        self.settings_table = QTableWidget()
        self.settings_table.setColumnCount(2)
        self.settings_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # Layout for settings tab
        settings_layout = QVBoxLayout()
        # settings_layout.addWidget(self.vital_signs_group_box)
        settings_layout.addWidget(self.checkbox1)
        settings_layout.addWidget(self.checkbox2)
        settings_layout.addWidget(self.editbox)
        settings_layout.addWidget(self.settings_table)

        # Add other UI elements for settings
        self.settings_tab.setLayout(settings_layout)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.cfg_design_tab = QWidget()

        self.chirp_frame_height = 100
        self.spacer_item = QSpacerItem(20, self.chirp_frame_height, QSizePolicy.Minimum, QSizePolicy.Expanding)

        # Create layouts for chirp_cfg_table and its caption
        self.chirp_layout = QVBoxLayout()
        self.chirp_layout.addWidget(self.chirp_cfg_caption)
        self.chirp_layout.addWidget(self.chirp_cfg_table)
        self.chirp_layout.addWidget(self.radar_cfg_caption)
        self.chirp_layout.addWidget(self.radar_cfg_table)
        # self.chirp_layout.addSpacerItem(self.spacer_item)

        # Create layouts for frame_table and its caption
        self.frame_layout = QVBoxLayout()
        self.frame_layout.addWidget(self.frame_table_caption)
        self.frame_layout.addWidget(self.frame_table)
        self.frame_layout.addWidget(self.statistics_table_caption)
        self.frame_layout.addWidget(self.statistics_table)
        # self.frame_layout.addSpacerItem(self.spacer_item)

        # Create layouts for temperature_table and its caption
        self.temperature_layout = QVBoxLayout()
        self.temperature_layout.addWidget(self.temperature_table_caption)
        self.temperature_layout.addWidget(self.temperature_table)

        # Create a horizontal layout to hold chirp_layout and frame_layout side by side
        self.chirp_frame_layout_h = QHBoxLayout()
        self.chirp_frame_layout_h.addLayout(self.chirp_layout)
        self.chirp_frame_layout_h.addLayout(self.frame_layout)
        self.chirp_frame_layout_h.addLayout(self.temperature_layout)
        # self.chirp_frame_layout_h.addSpacerItem(self.spacer_item)

        # Create layouts for radar_cfg_table and its caption
        # self.temp_layout = QVBoxLayout()
        # self.temp_layout.addWidget(self.radar_cfg_caption)
        # self.temp_layout.addWidget(self.radar_cfg_table)

        # Create a vertical layout to hold chirp_frame_layout_h and radar_layout
        self.cfg_design_layout_v = QVBoxLayout(self.cfg_design_tab)
        self.cfg_design_layout_v.addLayout(self.chirp_frame_layout_h)
        # self.cfg_design_layout_v.addSpacerItem(self.spacer_item)
        # self.cfg_design_layout_v.addLayout(self.temp_layout)

        self.cfg_design_tab.setLayout(self.cfg_design_layout_v)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Add tabs to the tab widget
        self.tab_widget.addTab(self.serial_port_tab, "Serial Ports")
        self.tab_widget.addTab(self.cfg_design_tab, "Device Parameters")
        self.tab_widget.addTab(self.settings_tab, "Settings")
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        main_layout = QVBoxLayout()
        main_layout.addWidget(self.tab_widget)

        self.setLayout(main_layout)

        # Widget to hold the layout
        widget = QWidget()
        widget.setLayout(main_layout)
        self.setCentralWidget(widget)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Status bar
        self.statusBar = QStatusBar()
        self.setStatusBar(self.statusBar)
        self.statusBar.addPermanentWidget(self.data_circle)
        self.statusBar.addPermanentWidget(self.data_status_label)
        self.statusBar.addPermanentWidget(self.command_circle)
        self.statusBar.addPermanentWidget(self.command_status_label)

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Flags to track connection status
        self.data_port_connected = False
        self.command_port_connected = False
        # self.data_port_ready = False
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Show the serial ports automatically when the application starts
        self.show_serial_ports()
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    def show_serial_ports(self):
        # Clear existing data from the table
        self.table.setRowCount(0)

        # Get a list of available serial ports
        ports = serial.tools.list_ports.comports()

        # Populate the table with serial ports
        for idx, port in enumerate(ports):
            self.table.insertRow(idx)
            self.table.setItem(idx, 0, QTableWidgetItem(port.device))

            # Add checkboxes in the Data and Command columns
            data_checkbox = QCheckBox()
            command_checkbox = QCheckBox()
            self.table.setCellWidget(idx, 1, data_checkbox)
            self.table.setCellWidget(idx, 2, command_checkbox)

            # Set the "Data" checkbox if the port description matches
            if "Silicon Labs Dual CP2105 USB to UART Bridge: Standard COM Port" in port.description or "Auxiliary" in port.description:
                data_checkbox.setChecked(True)
            if "Silicon Labs Dual CP2105 USB to UART Bridge: Enhanced COM Port" in port.description or "Application" in port.description:
                command_checkbox.setChecked(True)
            # Populate other columns
            self.table.setItem(idx, 3, QTableWidgetItem(port.description))
            self.table.setItem(idx, 4, QTableWidgetItem(port.manufacturer))
            self.table.setItem(idx, 5, QTableWidgetItem(port.hwid))

    def refresh_serial_ports(self):
        self.show_serial_ports()
    def connect_checked_ports(self):
        # Disconnect from the current ports
        self.disconnect_ports()
        time.sleep(1)

        # Get the number of rows in the table
        num_rows = self.table.rowCount()

        # Iterate over the rows
        for row in range(num_rows):
            # Get the checkboxes in the Data and Command columns
            data_checkbox = self.table.cellWidget(row, 1)
            command_checkbox = self.table.cellWidget(row, 2)

            # Get the port name from the first column
            port_name = self.table.item(row, 0).text()

            # Check if the Data or Command checkboxes are checked and connect accordingly
            if command_checkbox.isChecked():
                self.connect_to_port(port_name, "Command")
            if data_checkbox.isChecked():
                self.connect_to_port(port_name, "Data")

    def disconnect_ports(self):
        # Disconnect from the data port
        if self.data_port_connected:
            self.data_port_connected = False
            self.data_port.close()
            print("Disconnected from data port")
            self.command_textbox.appendPlainText(f"Disconnected from data port {self.data_port.name}")

        # Disconnect from the command port
        if self.command_port_connected:
            self.command_port_connected = False
            self.command_port.close()
            print("Disconnected from command port")
            self.command_textbox.appendPlainText(f"Disconnected from command port {self.command_port.name}")
        self.command_textbox.appendPlainText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

        # Update circle widgets and status labels
        self.update_circle_widgets()

    def connect_to_port(self, port_name, connection_type):
        # Set baud rate and data bits based on the connection type
        if connection_type == "Data":
            self.data_port = serial.Serial(port_name, 921600)
            self.data_port_connected = True
            self.command_textbox.appendPlainText(f"Connected to data port {self.data_port.name}")
            # self.permission_to_connect_to_data_port = True
        elif connection_type == "Command":
            self.command_port = serial.Serial(port_name, 115200)
            self.command_port_connected = True
            self.command_textbox.appendPlainText(f"Connected to command port {self.command_port.name}")
            # self.send_configuration()
        # Update circle widgets and status labels
        self.update_circle_widgets()

    def update_circle_widgets(self):
        # Update data port circle and status label
        if self.data_port_connected:
            self.data_circle.set_status("Connected")
            self.data_status_label.setText("Data Port: Connected")
        else:
            self.data_circle.set_status("Disconnected")
            self.data_status_label.setText("Data Port: Disconnected")

        # Update command port circle and status label
        if self.command_port_connected:
            self.command_circle.set_status("Connected")
            self.command_status_label.setText("Command Port: Connected")
        else:
            self.command_circle.set_status("Disconnected")
            self.command_status_label.setText("Command Port: Disconnected")


        # self.connect_checked_ports()

    def send_configuration(self):
        self.command_textbox.appendPlainText(f"Sending device configurations to command port {self.command_port.name}")
        # Set the event before sending configuration

        # Check if the command port is connected
        if not self.command_port_connected:
            print("Error: Command port is not connected")
            self.command_textbox.appendPlainText("Error: Command port is not connected")
            return

        # self.refresh_button.setDisabled(True)
        # Initialize QSerialPort object for the command port if not already initialized
        self.command_textbox.appendPlainText(f"Sending command to {self.command_port.name}")
        self.command_textbox.appendPlainText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
        for command in self.commands:
            print("Sending command:", command)
            command_bytes = command.encode('latin1') + b'\n'
            self.command_port.write(command_bytes)
            time.sleep(0.1)
            byteCount = self.command_port.in_waiting
            if byteCount > 0:
                response_bytes = self.command_port.read(byteCount)
                # Convert bytes to string and remove newline characters and additional macros
                response_str = response_bytes.decode('latin1').strip().replace("\n", "\n\t")
                print(response_str)
                self.command_textbox.appendPlainText(f"Response : {response_str}")
        self.command_textbox.appendPlainText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
        self.send_button.setEnabled(False)
        time.sleep(0.2)

    def browse_configuration(self):
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        file_filter = "Config Files (*.CFG);;All Files (*)"

        file_path, _ = QFileDialog.getOpenFileName(self, "Select Configuration File", "", file_filter, options=options)

        if file_path:
            # try:
            commands = self.load_configuration(file_path)
            self.commands = commands
            self.parse_commands_information(self.commands)
            self.send_button.setEnabled(True)
            self.command_textbox.appendPlainText("".join(file_path))
            # with open(file_path, 'r') as file:
            #     self.commands = file.readlines()  # Load commands from the file
            # self.command_textbox.setPlainText("".join(self.commands))
            # except Exception as e:
            #     QMessageBox.critical(self, "Error", f"Failed to load configuration file: {str(e)}")

            # print(f"Selected configuration file: {file_path}")
            # commands = self.load_configuration(file_path)
            # self.parse_commands_information(commands)
            # self.send_button.setEnabled(True)
            # print(commands)
        # else:
        #     QMessageBox.information(self, "No file selected", "Please select a valid configuration file.")

    def load_configuration(self, file_path):
        commands = []
        with open(file_path, 'r') as file:
            for line in file:
                if line.strip() and not line.startswith('%'):
                    commands.append(line.strip())
        return commands

    def parse_commands_information(self,commands):
        profile_cfg_command = next((cmd for cmd in commands if cmd.startswith('profileCfg')), None)
        parts_profile_cfg = profile_cfg_command.split()[1:]  # Remove the 'profileCfg' part

        frame_cfg_command = next((cmd for cmd in commands if cmd.startswith('frameCfg')), None)
        parts_frame_cfg = frame_cfg_command.split()[1:]  # Remove the 'profileCfg' part

        freq_slope = float(parts_profile_cfg[7]) * 1e12
        idle_time = float(parts_profile_cfg[2])
        ramp_end_time = float(parts_profile_cfg[4])
        chirp_time = (ramp_end_time - idle_time) * 1e-6
        bandwidth = freq_slope * chirp_time
        range_resolution = 3e8 / (2 * bandwidth)
        sample_rate = float(parts_profile_cfg[10]) * 1e3
        beat_freq = 0.8 * sample_rate
        unambiguous_range = 3e8 * beat_freq / (2 * freq_slope)
        samples_per_chirp = int(parts_profile_cfg[9])
        # print("bandwidth = ", bandwidth)
        print("range_resolution = ", range_resolution)
        print("unambiguous_range = ", unambiguous_range)

        frame_periodicity = float(parts_frame_cfg[4]) * 1e-3
        chirp_cfg_info = {}
        chirp_cfg_info["Frequency Start [GHz]"] = float(parts_profile_cfg[1])
        chirp_cfg_info["Frequency Slope [MHz/us]"] = freq_slope / 1e12
        chirp_cfg_info["Sample Rate [MHz]"] = sample_rate / 1e6
        chirp_cfg_info["# of Samples per Chirp"] = samples_per_chirp
        chirp_cfg_info["# of Burst in a Frame"] = int(parts_profile_cfg[8])

        chirp_cfg_info["# of Chirp Loops"] = int(parts_frame_cfg[2])
        chirp_cfg_info["Frame Periodicity [ms]"] = frame_periodicity * 1e3
        chirp_cfg_info["Idle Time [us]"] = idle_time
        chirp_cfg_info["ADC Valid Start Time [us]"] = int(parts_profile_cfg[3])
        chirp_cfg_info["Ramp End Time [us]"] = ramp_end_time
        chirp_cfg_info["# of Chirps in a Burst"] = int(parts_frame_cfg[2]) * int(parts_frame_cfg[1])
        self.update_table(self.chirp_cfg_table, chirp_cfg_info)

        radar_cfg_info = {}
        radar_cfg_info["Bandwidth [MHz]"] = round(bandwidth / 1e6, 3)
        radar_cfg_info["Maximum Beat Frequency [MHz]"] = round(beat_freq / 1e6, 3)
        radar_cfg_info["Unambiguous Range [m]"] = round(unambiguous_range, 3)
        radar_cfg_info["Range Resolution [cm]"] = round(range_resolution * 100)
        self.update_table(self.radar_cfg_table, radar_cfg_info)
    def update_table(self, table_id, table_info):
        # Clear existing data from the table
        table_id.setRowCount(0)
        if table_info is None:
            print("ERROR: table_info is None")
            return  # or handle the error appropriately

        # Add frame header information to the table
        for idx, (param, value) in enumerate(table_info.items()):
            table_id.insertRow(idx)
            table_id.setItem(idx, 0, QTableWidgetItem(param))
            table_id.setItem(idx, 1, QTableWidgetItem(str(value)))

    def closeEvent(self, event):
        # Disconnect from the ports when the application is closed
        event.accept()
        self.disconnect_ports()

