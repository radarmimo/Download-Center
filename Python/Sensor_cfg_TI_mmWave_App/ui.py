import time, random, os
import serial.tools.list_ports
from PyQt5.QtWidgets import QMainWindow, QPushButton, QTableWidget, QTableWidgetItem, QVBoxLayout, \
    QWidget, QCheckBox, QStatusBar, QLabel, QPlainTextEdit, QTabWidget, QHBoxLayout, QSpacerItem, QSizePolicy, \
    QLineEdit, QComboBox
from PyQt5.QtGui import QPainter, QBrush
from PyQt5.QtCore import Qt
import serial
from PyQt5.QtWidgets import QFileDialog, QMessageBox
from radar_calculator import RadarCalculator
from datetime import datetime
from PyQt5.QtGui import QColor, QIcon
import logging
import pyqtgraph.opengl as gl
import numpy as np

icon_path = os.path.join("/home/bobo/sparcprojects_notes/Sensor_cfg_TI_mmWave_App/icon.png")

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
class MainWindow(QMainWindow, QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("TI mmWave Radar Control Panel")
        self.setWindowIcon(QIcon(icon_path))
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # RadarCalculator instance
        self.radar_calculator = RadarCalculator()
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.light_speed = 3e8

        self.radar_params = {
            "Frequency Slope [MHz/us]": 0,
            "Idle Time [us]": 0,
            "Ramp End Time [us]": 0,
            "ADC Valid Start Time [us]": 0,
            "Chirp Time [us]": 0,
            "Chirp Repetition Period [us]": 0,
            "Chirp Cycle Time [us]": 0,
            "Bandwidth [MHz]": 0,
            "Range Resolution [m]": 0,
            "Sample Rate [KHz]": 0,
            "Beat Frequency [MHz]": 0,
            "Maximum Range [m]": 0,
            "Unambiguous Range [m]": 0,
            "Unambiguous Velocity [km/h]": 0,
            "Number of Samples per Chirp": 0,
            "Frequency Start [GHz]": 0,
            "Number of Bursts in Frame": 0,
            "Number of Chirps in Burst": 0,
            "Frame Periodicity [ms]": 0,
            "Number of Chirps in Loop": 0,
            "Number of Loops": 0,
            "Burst Periodicity [us]": 0,
            "Velocity Resolution [km/h]": 0,
            "Number of Range FFT Bins": 0,
            "Number of Doppler FFT Bins": 0,
            # "Number of Angle Bins": 0,
            "Number of Tx Antennas": 0,
            "Number of Rx Antennas": 0,
            "Length of Virtual Array": 0,
            "Radar Cube Size [KB]": 0,
            "Active Frame Time [ms]": 0,
            "Range-Doppler Heatmap Minimum Value": 2048,
            "Range-Doppler Heatmap Maximum Value": 4096,
            "Range-Doppler Heatmap Grid Size": 128,
            "Azimuth Static Heatmap Minimum Value": 0,
            "Azimuth Static Heatmap Maximum Value": 800,
            "Azimuth Static Heatmap Grid Size": 256,
            "Minimum Bandwidth [MHz]": 15,
            "Maximum Bandwidth [MHz]": 4000,
            "Minimum Range Resolution [m]": 0.0375,
            "Maximum Range Resolution [m]": 10,
            "Minimum Frequency Slope [MHz/us]": 5,
            "Maximum Frequency Slope [MHz/us]": 300,
        }

        ### Parameters from DataSheet
        self.IWR6843ISK = {
            "Transmit Antenna Gain [dB]": 7,
            "Receive Antenna Gain [dB]": 7,
            "Transmit Power [dBm]": 12,
            "Maximum IF Frequency (MHz)": 10,
            "Maximum Complex ADC Sampling Rate [MSps]": 12.5,
            "Minimum Complex ADC Sampling Rate [MSps]": 2,
            "3dB Azimuth FOV [deg.]": 60,
            "3dB Elevation FOV [deg.]": 15,
            "Memory [MB]": 1.75,
            "Radar data cube RAM [KB]": 768,
            "RX noise figure [dB]": 12,
            "Phase noise at 1MHz [dBc/Hz]": -93,
            "Maximum Rx Gain [dB]": 48,
            "Rx Gain Step Size [dB]": 2,
            "Number of Rx Antennas": 4,
            "Number of Tx Antennas": 3,
            "ADC Resolution [bits]": 12,
            "DSP Type": "1 C674x DSP@600MHz"
        }

        self.IWR6843ISK_best_range_resolution = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'),
                                                    ('channelCfg', '15 5 0'), ('adcCfg', '2 1'), ('adcbufCfg', '-1 0 1 1 1'),
                                                    ('profileCfg', '0 60 567 7 57.14 0 0 70 1 256 5209 0 0 158'),
                                                    ('chirpCfg', '0 0 0 0 0 0 0 1'),('chirpCfg', '1 1 0 0 0 0 0 4'),
                                                    ('frameCfg', '0 1 16 0 100 1 0'), ('lowPower', '0 0'),
                                                    ('guiMonitor', '-1 1 1 0 0 0 1'),
                                                    ('cfarCfg', '-1 0 2 8 4 3 0 15 1'), ('cfarCfg', '-1 1 0 4 2 3 1 15 1'),
                                                    ('multiObjBeamForming', '-1 1 0.5'),('clutterRemoval', '-1 0'),
                                                    ('calibDcRangeSig', '-1 0 -5 8 256'), ('extendedMaxVelocity', '-1 0'),
                                                    ('bpmCfg', '-1 0 0 1'), ('lvdsStreamCfg', '-1 0 0 0'),
                                                    ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                                    ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'), ('CQRxSatMonitor', '0 3 5 121 0'),
                                                    ('CQSigImgMonitor', '0 127 4'),
                                                    ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                                    ('cfarFovCfg', '-1 0 0 8.92'), ('cfarFovCfg', '-1 1 -1 1.00'),
                                                    ('calibData', '0 0 0'), ('sensorStart', '')]

        self.IWR6843ISK_best_velocity_resolution = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'),
                                                       ('channelCfg', '15 5 0'), ('adcCfg', '2 1'),
                                                       ('adcbufCfg', '-1 0 1 1 1'), ('profileCfg', '0 60 180 7 15 0 0 100 1 64 9142 0 0 158'),
                                                       ('chirpCfg', '0 0 0 0 0 0 0 1'), ('chirpCfg', '1 1 0 0 0 0 0 4'),
                                                       ('frameCfg', '0 1 128 0 100 1 0'), ('lowPower', '0 0'),
                                                       ('guiMonitor', '-1 1 1 0 0 0 1'), ('cfarCfg', '-1 0 2 8 4 3 0 15 1'),
                                                       ('cfarCfg', '-1 1 0 8 4 4 1 15 1'), ('multiObjBeamForming', '-1 1 0.5'),
                                                       ('clutterRemoval', '-1 0'), ('calibDcRangeSig', '-1 0 -5 8 256'),
                                                       ('extendedMaxVelocity', '-1 0'), ('bpmCfg', '-1 0 0 1'),
                                                       ('lvdsStreamCfg', '-1 0 0 0'),
                                                       ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                                       ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'),
                                                       ('CQRxSatMonitor', '0 3 4 19 0'), ('CQSigImgMonitor', '0 31 4'),
                                                       ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                                       ('cfarFovCfg', '-1 0 0 10.97'), ('cfarFovCfg', '-1 1 -3.2 3.20'),
                                                       ('calibData', '0 0 0'), ('sensorStart', '')]

        self.IWR6843ISK_best_range = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'), ('channelCfg', '15 5 0'),
                                      ('adcCfg', '2 1'), ('adcbufCfg', '-1 0 1 1 1'), ('profileCfg', '0 60 596 7 28.49 0 0 30 1 256 12499 0 0 158'),
                                      ('chirpCfg', '0 0 0 0 0 0 0 1'), ('chirpCfg', '1 1 0 0 0 0 0 4'), ('frameCfg', '0 1 16 0 100 1 0'),
                                      ('lowPower', '0 0'), ('guiMonitor', '-1 1 1 0 0 0 1'), ('cfarCfg', '-1 0 2 8 4 3 0 15 1'),
                                      ('cfarCfg', '-1 1 0 4 2 3 1 15 1'), ('multiObjBeamForming', '-1 1 0.5'),
                                      ('clutterRemoval', '-1 0'), ('calibDcRangeSig', '-1 0 -5 8 256'),
                                      ('extendedMaxVelocity', '-1 0'), ('bpmCfg', '-1 0 0 1'), ('lvdsStreamCfg', '-1 0 0 0'),
                                      ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                      ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'), ('CQRxSatMonitor', '0 3 4 63 0'),
                                      ('CQSigImgMonitor', '0 127 4'), ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                      ('cfarFovCfg', '-1 0 0 49.99'), ('cfarFovCfg', '-1 1 -1 1.00'), ('calibData', '0 0 0'), ('sensorStart', '')]

        #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.AWR1642BOOST = {
            "Transmit Antenna Gain [dB]": 7,
            "Receive Antenna Gain [dB]": 7,
            "Transmit Power [dBm]": 12, #found
            "Maximum IF Frequency (MHz)": 5, #found
            "Maximum Complex ADC Sampling Rate [MSps]": 6.25, # use complex 1x
            "Minimum Complex ADC Sampling Rate [MSps]": 2,
            "3dB Azimuth FOV [deg.]": 60, #check from Antenna Pattern
            "3dB Elevation FOV [deg.]": 15, #check from Antenna Pattern
            "Memory [MB]": 1.5, #found
            "Radar data cube RAM [KB]": 768, # found
            "RX noise figure [dB]": 15, # found use (77 to 81 GHZ range)
            "Phase noise at 1MHz [dBc/Hz]": -93, # found use (77 to 81 GHZ range)
            "Maximum Rx Gain [dB]": 48, #found
            "Rx Gain Step Size [dB]": 2, #found
            "Number of Rx Antennas": 4, #found
            "Number of Tx Antennas": 2, #found
            "ADC Resolution [bits]": 12, # found
            "DSP Type": "1 C674x DSP@600MHz" # found
        }

        self.AWR1642BOOST_best_range_resolution = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'),
                                                   ('channelCfg', '15 3 0'), ('adcCfg', '2 1'), ('adcbufCfg', '-1 0 1 1 0'),
                                                   ('profileCfg', '0 77 429 7 57.14 0 0 70 1 256 5209 0 0 30'),
                                                   ('chirpCfg', '0 0 0 0 0 0 0 1'), ('chirpCfg', '1 1 0 0 0 0 0 2'),
                                                   ('frameCfg', '0 1 16 0 100 1 0'), ('lowPower', '0 1'),
                                                   ('guiMonitor', '-1 1 1 0 0 0 1'), ('cfarCfg', '-1 0 2 8 4 3 0 15 1'),
                                                   ('cfarCfg', '-1 1 0 4 2 3 1 15 1'), ('multiObjBeamForming', '-1 1 0.5'),
                                                   ('clutterRemoval', '-1 0'), ('calibDcRangeSig', '-1 0 -5 8 256'),
                                                   ('extendedMaxVelocity', '-1 0'), ('bpmCfg', '-1 0 0 1'),
                                                   ('lvdsStreamCfg', '-1 0 0 0'), ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                                   ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'), ('CQRxSatMonitor', '0 3 5 121 0'),
                                                   ('CQSigImgMonitor', '0 127 4'), ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                                   ('cfarFovCfg', '-1 0 0 8.92'), ('cfarFovCfg', '-1 1 -1 1.00'), ('calibData', '0 0 0'), ('sensorStart', '')]

        self.AWR1642BOOST_best_velocity_resolution = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'),
                                                      ('channelCfg', '15 3 0'), ('adcCfg', '2 1'), ('adcbufCfg', '-1 0 1 1 0'),
                                                      ('profileCfg', '0 77 177 7 18.24 0 0 82.237 1 64 6249 0 0 30'),
                                                      ('chirpCfg', '0 0 0 0 0 0 0 1'), ('chirpCfg', '1 1 0 0 0 0 0 2'),
                                                      ('frameCfg', '0 1 128 0 100 1 0'), ('lowPower', '0 1'),
                                                      ('guiMonitor', '-1 1 1 0 0 0 1'), ('cfarCfg', '-1 0 2 8 4 3 0 15 1'),
                                                      ('cfarCfg', '-1 1 0 8 4 4 1 15 1'), ('multiObjBeamForming', '-1 1 0.5'),
                                                      ('clutterRemoval', '-1 0'), ('calibDcRangeSig', '-1 0 -5 8 256'),
                                                      ('extendedMaxVelocity', '-1 0'), ('bpmCfg', '-1 0 0 1'),
                                                      ('lvdsStreamCfg', '-1 0 0 0'), ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                                      ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'), ('CQRxSatMonitor', '0 3 4 31 0'),
                                                      ('CQSigImgMonitor', '0 31 4'), ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                                      ('cfarFovCfg', '-1 0 0 9.11'), ('cfarFovCfg', '-1 1 -2.49 2.49'), ('calibData', '0 0 0'), ('sensorStart', '')]

        self.AWR1642BOOST_best_range = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'), ('channelCfg', '15 3 0'),
                                        ('adcCfg', '2 1'), ('adcbufCfg', '-1 0 1 1 0'), ('profileCfg', '0 77 438 7 48.98 0 0 15 1 256 6250 0 0 30'),
                                        ('chirpCfg', '0 0 0 0 0 0 0 1'), ('chirpCfg', '1 1 0 0 0 0 0 2'), ('frameCfg', '0 1 16 0 100 1 0'),
                                        ('lowPower', '0 1'), ('guiMonitor', '-1 1 1 0 0 0 1'), ('cfarCfg', '-1 0 2 8 4 3 0 15 1'),
                                        ('cfarCfg', '-1 1 0 4 2 3 1 15 1'), ('multiObjBeamForming', '-1 1 0.5'), ('clutterRemoval', '-1 0'),
                                        ('calibDcRangeSig', '-1 0 -5 8 256'), ('extendedMaxVelocity', '-1 0'), ('bpmCfg', '-1 0 0 1'),
                                        ('lvdsStreamCfg', '-1 0 0 0'), ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                        ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'), ('CQRxSatMonitor', '0 3 4 127 0'),
                                        ('CQSigImgMonitor', '0 127 4'), ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                        ('cfarFovCfg', '-1 0 0 50.00'), ('cfarFovCfg', '-1 1 -1 1.00'), ('calibData', '0 0 0'), ('sensorStart', '')]
        #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.IWR1843BOOST = {
            "Transmit Antenna Gain [dB]": 7,
            "Receive Antenna Gain [dB]": 7,
            "Transmit Power [dBm]": 12, #found
            "Maximum IF Frequency (MHz)": 10, #found
            "Maximum Complex ADC Sampling Rate [MSps]": 12.5, #found, (complex 1x)
            "Minimum Complex ADC Sampling Rate [MSps]": 2,
            "3dB Azimuth FOV [deg.]": 40, #use from Antenna Pattern
            "3dB Elevation FOV [deg.]": 30, #use from Antenna Pattern
            "Memory [MB]": 2, #found
            "Radar data cube RAM [KB]": 1024, #found
            "RX noise figure [dB]": 14, # found, use 76 to 77 GHz
            "Phase noise at 1MHz [dBc/Hz]": -95, # found, use 76 to 77 GHz
            "Maximum Rx Gain [dB]": 48, #found
            "Rx Gain Step Size [dB]": 2, #found
            "Number of Rx Antennas": 4, # found
            "Number of Tx Antennas": 3, # found
            "ADC Resolution [bits]": 12, # found
            "DSP Type": "1 C674x DSP@400/600MHz" #found
        }

        self.IWR1843BOOST_best_range_resolution = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'),
                                                   ('channelCfg', '15 5 0'), ('adcCfg', '2 1'), ('adcbufCfg', '-1 0 1 1 1'),
                                                   ('profileCfg', '0 77 429 7 57.14 0 0 70 1 256 5209 0 0 30'),
                                                   ('chirpCfg', '0 0 0 0 0 0 0 1'), ('chirpCfg', '1 1 0 0 0 0 0 4'),
                                                   ('frameCfg', '0 1 16 0 100 1 0'), ('lowPower', '0 0'), ('guiMonitor', '-1 1 1 0 0 0 1'),
                                                   ('cfarCfg', '-1 0 2 8 4 3 0 15 1'), ('cfarCfg', '-1 1 0 4 2 3 1 15 1'),
                                                   ('multiObjBeamForming', '-1 1 0.5'), ('clutterRemoval', '-1 0'),
                                                   ('calibDcRangeSig', '-1 0 -5 8 256'), ('extendedMaxVelocity', '-1 0'),
                                                   ('lvdsStreamCfg', '-1 0 0 0'), ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                                   ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'), ('CQRxSatMonitor', '0 3 5 121 0'),
                                                   ('CQSigImgMonitor', '0 127 4'), ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                                   ('cfarFovCfg', '-1 0 0 8.92'), ('cfarFovCfg', '-1 1 -1 1.00'), ('calibData', '0 0 0'), ('sensorStart', '')]

        self.IWR1843BOOST_best_velocity_resolution = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'),
                                                      ('channelCfg', '15 5 0'), ('adcCfg', '2 1'), ('adcbufCfg', '-1 0 1 1 1'),
                                                      ('profileCfg', '0 77 180 7 15 0 0 100 1 64 9142 0 0 30'),
                                                      ('chirpCfg', '0 0 0 0 0 0 0 1'), ('chirpCfg', '1 1 0 0 0 0 0 4'),
                                                      ('frameCfg', '0 1 128 0 100 1 0'), ('lowPower', '0 0'),
                                                      ('guiMonitor', '-1 1 1 0 0 0 1'), ('cfarCfg', '-1 0 2 8 4 3 0 15 1'),
                                                      ('cfarCfg', '-1 1 0 8 4 4 1 15 1'), ('multiObjBeamForming', '-1 1 0.5'),
                                                      ('clutterRemoval', '-1 0'), ('calibDcRangeSig', '-1 0 -5 8 256'),
                                                      ('extendedMaxVelocity', '-1 0'), ('lvdsStreamCfg', '-1 0 0 0'),
                                                      ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                                      ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'), ('CQRxSatMonitor', '0 3 4 19 0'),
                                                      ('CQSigImgMonitor', '0 31 4'), ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                                      ('cfarFovCfg', '-1 0 0 10.97'), ('cfarFovCfg', '-1 1 -2.49 2.49'), ('calibData', '0 0 0'), ('sensorStart', '')]

        self.IWR1843BOOST_best_range = [('sensorStop', ''), ('flushCfg', ''), ('dfeDataOutputMode', '1'), ('channelCfg', '15 5 0'),
                                        ('adcCfg', '2 1'), ('adcbufCfg', '-1 0 1 1 1'), ('profileCfg', '0 77 458 7 28.49 0 0 30 1 256 12499 0 0 30'),
                                        ('chirpCfg', '0 0 0 0 0 0 0 1'), ('chirpCfg', '1 1 0 0 0 0 0 4'), ('frameCfg', '0 1 16 0 100 1 0'),
                                        ('lowPower', '0 0'), ('guiMonitor', '-1 1 1 0 0 0 1'), ('cfarCfg', '-1 0 2 8 4 3 0 15 1'),
                                        ('cfarCfg', '-1 1 0 4 2 3 1 15 1'), ('multiObjBeamForming', '-1 1 0.5'), ('clutterRemoval', '-1 0'),
                                        ('calibDcRangeSig', '-1 0 -5 8 256'), ('extendedMaxVelocity', '-1 0'), ('lvdsStreamCfg', '-1 0 0 0'),
                                        ('compRangeBiasAndRxChanPhase', '0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0'),
                                        ('measureRangeBiasAndRxChanPhase', '0 1.5 0.2'), ('CQRxSatMonitor', '0 3 4 63 0'),
                                        ('CQSigImgMonitor', '0 127 4'), ('analogMonitor', '0 0'), ('aoaFovCfg', '-1 -90 90 -90 90'),
                                        ('cfarFovCfg', '-1 0 0 49.99'), ('cfarFovCfg', '-1 1 -1 1.00'), ('calibData', '0 0 0'), ('sensorStart', '')]

        #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.chirp_cfg_table_headers = {
            "Frequency Slope [MHz/us]",
            "Sample Rate [KHz]",
            "Beat Frequency [MHz]",
            "Number of Samples per Chirp",
            "Number of Bursts in Frame",
            "Number of Chirps in Loop",
            "Number of Loops",
            "Frame Periodicity [ms]",
            "Active Frame Time [ms]",
            "Idle Time [us]",
            "Chirp Time [us]",
            "Chirp Cycle Time [us]",
            "Chirp Repetition Period [us]",
            "ADC Valid Start Time [us]",
            "Ramp End Time [us]",
            "Number of Chirps in Burst",
            "Burst Periodicity [us]",
            "Number of Range FFT Bins",
            "Number of Doppler FFT Bins",
            "Radar Cube Size [KB]",
        }
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Create a button to refresh the list of serial ports
        self.refresh_button = QPushButton("Refresh Serial Ports")
        # self.refresh_button.setStyleSheet("background-color: #f0f0f0; color: #808080; border: 1px solid #d0d0d0;")
        # self.refresh_button.setEnabled(False)
        self.refresh_button.clicked.connect(self.refresh_serial_ports)

        self.connect_button = QPushButton("Connect")
        self.connect_button.setEnabled(False)
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
        self.send_button.setStyleSheet("font-weight: bold;")
        self.send_button.clicked.connect(self.send_configuration)

        # Create a button to stop the device
        self.stop_device_button = QPushButton("Stop Device")
        self.stop_device_button.clicked.connect(self.stop_device)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.chirp_cfg_table = QTableWidget()
        self.chirp_cfg_caption = QLabel("<font color='black'><b>Chirp Configuration</b>")
        # self.chirp_cfg_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        self.chirp_cfg_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.chirp_cfg_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.chirp_cfg_table.setColumnWidth(1, 150)
        self.chirp_cfg_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.radar_cfg_table = QTableWidget()
        self.radar_cfg_caption = QLabel("<font color='blue'><b>Scene Parameters</b></font>")
        self.radar_cfg_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.radar_cfg_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.radar_cfg_table.setColumnWidth(1, 150)
        self.radar_cfg_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # Make the first column non-editable by setting the edit trigger for the whole table
        self.radar_cfg_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.field_of_view_table = QTableWidget()
        self.field_of_view_caption = QLabel("<font color='navy'><b>Azimuth, Elevation, Range & Velocity</b></font>")
        self.field_of_view_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.field_of_view_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.field_of_view_table.setColumnWidth(1, 500)
        self.field_of_view_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.display_table = QTableWidget()
        self.display_caption = QLabel("<font color='magenta'><b>Display</b></font>")
        self.display_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.display_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.display_table.setColumnWidth(1, 500)
        self.display_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.statistics_table_caption = QLabel("<font color='green'><b>Statistics (Performance)</b></font>")
        self.statistics_table = QTableWidget()
        self.statistics_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        self.statistics_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.statistics_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.statistics_table.setColumnWidth(1, 200)
        self.statistics_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.temperature_table_caption = QLabel("<font color='magenta'><b>Temperature</b></font>")
        self.temperature_table = QTableWidget()
        self.temperature_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        self.temperature_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.temperature_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.temperature_table.setColumnWidth(1, 200)
        self.temperature_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.header_table_caption = QLabel("<font color='red'><b>Header</b></font>")
        self.header_table = QTableWidget()
        self.header_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        self.header_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.header_table.setColumnWidth(0, 200)  # Set the width of the first column to 200 pixels
        self.header_table.setColumnWidth(1, 200)
        self.header_table.setHorizontalHeaderLabels(["Parameter", "Value"])

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Table for Commands and Parameters
        self.command_table = QTableWidget()
        self.command_table.setColumnCount(2)
        # self.command_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        self.command_table.setColumnWidth(0, 250)  # Set the width of the first column to 200 pixels
        self.command_table.setColumnWidth(1, 450)
        self.command_table.setHorizontalHeaderLabels(["Command", "Parameters"])
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.tab_widget_main = QTabWidget()
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Layout setup
        self.serial_port_tab = QWidget()
        button_layout = QHBoxLayout()
        button_layout.addWidget(self.refresh_button)
        # button_layout.addWidget(self.connect_button)

        # Create a vertical layout for the serial port tab
        self.serial_port_layout = QVBoxLayout(self.serial_port_tab)
        self.serial_port_layout.addLayout(button_layout)  # Add the button layout
        self.serial_port_layout.addWidget(self.table)
        # self.serial_port_layout.addWidget(self.browse_config_button)
        self.serial_port_layout.addWidget(self.command_textbox)
        # self.serial_port_layout.addWidget(self.send_button)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Add the frame table to the frame header tab
        self.settings_tab = QWidget()
        self.checkbox1 = QCheckBox("Checkbox 1")
        self.checkbox2 = QCheckBox("Checkbox 2")

        self.editbox = QLineEdit()
        self.settings_table_caption = QLabel("<font color='magenta'><b>Display Settings</b></font>")
        # Create a table to show parameters
        self.settings_table = QTableWidget()
        self.settings_table.setColumnCount(2)
        self.settings_table.setHorizontalHeaderLabels(["Parameter", "Value"])
        self.settings_table.setColumnWidth(0, 450)  # Set the width of the first column to 200 pixels
        self.settings_table.setColumnWidth(1, 250)

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
        # Add the frame table to the frame header tab
        self.detected_points_tab = QWidget()
        self.detected_points_layout = QVBoxLayout()
        self.detected_points_table_caption = QLabel("<font color='green'><b>Detected Points</b></font>")
        self.detected_points_table = QTableWidget()
        self.detected_points_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        self.detected_points_table.setColumnCount(5)  # Two columns: Parameter and Value
        self.detected_points_table.setColumnWidth(0, 100)  # Set the width of the first column to 200 pixels
        self.detected_points_table.setColumnWidth(1, 150)
        self.detected_points_table.setColumnWidth(2, 150)
        self.detected_points_table.setColumnWidth(3, 150)
        self.detected_points_table.setColumnWidth(4, 150)
        self.detected_points_table.setHorizontalHeaderLabels(["ID", "X", "Y", "Z", "Doppler"])

        self.points_info_table_caption = QLabel("<font color='green'><b>Detected Points Info</b></font>")
        self.points_info_table = QTableWidget()
        self.points_info_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        self.points_info_table.setColumnCount(3)  # Two columns: Parameter and Value
        self.points_info_table.setColumnWidth(0, 100)  # Set the width of the first column to 200 pixels
        self.points_info_table.setColumnWidth(1, 150)
        self.points_info_table.setColumnWidth(2, 150)
        self.points_info_table.setHorizontalHeaderLabels(["ID", "SNR", "Noise"])

        self.detected_points_layout.addWidget(self.detected_points_table_caption)
        self.detected_points_layout.addWidget(self.detected_points_table)
        self.detected_points_layout.addWidget(self.points_info_table_caption)
        self.detected_points_layout.addWidget(self.points_info_table)
        self.detected_points_tab.setLayout(self.detected_points_layout)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.three_d_plot_tab = QWidget()
        self.three_d_plot_layout = QVBoxLayout()

        three_d_plot_widget = gl.GLViewWidget()
        # # win.setWindowTitle('3D Point Cloud')
        #
        # # Add coordinate axes
        three_d_plot_ax = gl.GLAxisItem()
        three_d_plot_widget.addItem(three_d_plot_ax)
        #
        # # Add grid
        three_d_plot_grid = gl.GLGridItem()
        three_d_plot_widget.addItem(three_d_plot_grid)
        #
        # # Initialize scatter plot item
        self.three_d_plot_item = gl.GLScatterPlotItem()
        three_d_plot_widget.addItem(self.three_d_plot_item)
        #
        # # Set view range for 3D plot
        three_d_plot_widget.opts['distance'] = 30
        three_d_plot_widget.opts['elevation'] = 90  # 90 degrees looks directly down (top view)
        three_d_plot_widget.opts['azimuth'] = 0  # 0 degrees points towards positive X-axis (default)
        #
        num_rings = 10
        radius_interval = 10
        ppi_opacity = 0.2

        num_angles = 10
        max_range = 100
        # Add PPI grids
        for i in range(num_rings):
            radius = radius_interval * (i + 1)
            theta = np.linspace(0, 2 * np.pi, 100)
            x = radius * np.cos(theta)
            y = radius * np.sin(theta)
            z = np.zeros_like(x)
            grid_item = gl.GLLinePlotItem(pos=np.vstack((x, y, z)).T, color=(255, 0, 255, ppi_opacity))
            three_d_plot_widget.addItem(grid_item)

        for i in range(num_angles):
            theta = 2 * np.pi / num_angles * i
            x = np.array([0, max_range * np.cos(theta)])
            y = np.array([0, max_range * np.sin(theta)])
            z = np.zeros_like(x)
            grid_item = gl.GLLinePlotItem(pos=np.vstack((x, y, z)).T, color=(255, 255, 0, ppi_opacity))
            three_d_plot_widget.addItem(grid_item)

        self.three_d_plot_layout.addWidget(three_d_plot_widget)
        self.three_d_plot_tab.setLayout(self.three_d_plot_layout)

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.apply_changes_to_cfg_file_push_button = QPushButton("Apply Changes to cfg Table")
        self.save_cfg_push_button = QPushButton("Save Config (.cfg)")

        self.chirp_frame_height = 100
        self.spacer_item = QSpacerItem(20, self.chirp_frame_height, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.cfg_layout_v = QVBoxLayout()
        # self.cfg_layout_v.addWidget(self.browse_config_button)
        self.cfg_layout_v.addWidget(self.command_table)

        self.chirp_layout_v1 = QVBoxLayout()
        self.chirp_layout_v1.addWidget(self.chirp_cfg_caption)
        self.chirp_layout_v1.addWidget(self.chirp_cfg_table)
        self.chirp_layout_v2 = QVBoxLayout()
        self.chirp_layout_v2.addWidget(self.radar_cfg_caption)
        self.chirp_layout_v2.addWidget(self.radar_cfg_table)

        # Create a horizontal layout
        self.chirp_layout_h1 = QHBoxLayout()
        self.chirp_layout_h1.addLayout(self.chirp_layout_v1)
        self.chirp_layout_h1.addLayout(self.chirp_layout_v2)

        self.evm_param_caption = QLabel("<font color='red'><b>EVM Parameters</b>")
        self.evm_param_table = QTableWidget()
        self.evm_param_table.setEditTriggers(QTableWidget.NoEditTriggers)  # Disable editing
        self.evm_param_table.setColumnCount(2)  # Two columns: Parameter and Value
        self.evm_param_table.setColumnWidth(0, 320)  # Set the width of the first column to 200 pixels
        self.evm_param_table.setColumnWidth(1, 380)
        self.evm_param_table.setHorizontalHeaderLabels(["Parameter", "Value"])

        self.evm_layout_v1 = QVBoxLayout()
        self.evm_layout_v1.addWidget(self.evm_param_caption)
        self.evm_layout_v1.addWidget(self.evm_param_table)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.tab_widget_cfg = QTabWidget()
        self.chirp_tab = QWidget()
        self.chirp_layout = QVBoxLayout(self.chirp_tab)
        self.chirp_layout.addLayout(self.chirp_layout_h1)
        self.chirp_tab.setLayout(self.chirp_layout)
        self.tab_widget_cfg.addTab(self.chirp_tab, "Chirp")

        self.field_of_view_tab = QWidget()
        self.field_of_view_layout = QVBoxLayout(self.field_of_view_tab)
        self.field_of_view_layout.addWidget(self.field_of_view_caption)
        self.field_of_view_layout.addWidget(self.field_of_view_table)
        self.tab_widget_cfg.addTab(self.field_of_view_tab, "Field of View")

        self.display_tab = QWidget()
        self.display_layout = QVBoxLayout(self.display_tab)
        self.display_layout.addWidget(self.display_caption)
        self.display_layout.addWidget(self.display_table)
        self.tab_widget_cfg.addTab(self.display_tab, "Display")

        self.evm_tab = QWidget()
        self.evm_layout = QVBoxLayout(self.evm_tab)
        self.evm_layout.addLayout(self.evm_layout_v1)
        self.evm_tab.setLayout(self.evm_layout)
        self.tab_widget_cfg.addTab(self.evm_tab, "EVM info")

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Create a vertical layout
        self.configuration_tab = QWidget()
        self.configuration_layout = QVBoxLayout(self.configuration_tab)
        self.configuration_layout.addWidget(self.tab_widget_cfg)
        self.configuration_layout.addWidget(self.apply_changes_to_cfg_file_push_button)
        self.configuration_layout.addLayout(self.cfg_layout_v)
        self.configuration_layout.addWidget(self.save_cfg_push_button)
        self.configuration_tab.setLayout(self.configuration_layout)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.frame_content_tab = QWidget()

        # Create layouts for frame_table and its caption
        self.frame_layout = QVBoxLayout()
        self.frame_layout.addWidget(self.statistics_table_caption)
        self.frame_layout.addWidget(self.statistics_table)

        # Create layouts for temperature_table and its caption
        self.temperature_layout = QVBoxLayout()
        self.temperature_layout.addWidget(self.temperature_table_caption)
        self.temperature_layout.addWidget(self.temperature_table)

        # Create layouts for temperature_table and its caption
        self.header_layout = QVBoxLayout()
        self.header_layout.addWidget(self.header_table_caption)
        self.header_layout.addWidget(self.header_table)

        self.frame_content_layout_v1 = QVBoxLayout()
        self.frame_content_layout_v1.addLayout(self.frame_layout)

        self.frame_content_layout_v2 = QVBoxLayout()
        self.frame_content_layout_v2.addLayout(self.header_layout)
        self.frame_content_layout_v2.addLayout(self.temperature_layout)

        self.frame_content_layout_h = QHBoxLayout(self.frame_content_tab)
        self.frame_content_layout_h.addLayout(self.frame_content_layout_v1)
        self.frame_content_layout_h.addLayout(self.frame_content_layout_v2)

        self.frame_content_tab.setLayout(self.frame_content_layout_h)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Add tabs to the tab widget
        self.tab_widget_main.addTab(self.serial_port_tab, "Serial Ports")
        self.tab_widget_main.addTab(self.configuration_tab, "Configuration")
        self.tab_widget_main.addTab(self.frame_content_tab, "Frame Content")
        self.tab_widget_main.addTab(self.detected_points_tab, "Detected Points")
        self.tab_widget_main.addTab(self.three_d_plot_tab, "3D scatter plot")

        self.tab_widget_main.addTab(self.settings_tab, "Settings")

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.select_radar_layout = QHBoxLayout()

        # Create a label
        select_radar_label = QLabel("Radar Module:")

        # Create the combo box
        self.select_radar_combo_box = QComboBox()
        self.select_radar_combo_box.addItems(["IWR6843ISK", "AWR1642BOOST", "IWR1843BOOST"])

        # Add the label and combo box to the layout
        self.select_radar_layout.addWidget(select_radar_label)
        self.select_radar_layout.addWidget(self.select_radar_combo_box)

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Add the Desirable Configuration for Best default value [combo box]
        select_default_best_Config_label = QLabel("             Desirable Configuration:")
        self.select_default_best_Config_combo_box = QComboBox()
        self.select_default_best_Config_combo_box.addItems(["Best Range Resolution", "Best Velocity Resolution", "Best Range"])

        # Add the label and combo box to the layout
        self.select_radar_layout.addWidget(select_default_best_Config_label)
        self.select_radar_layout.addWidget(self.select_default_best_Config_combo_box)

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        main_layout = QVBoxLayout()
        main_layout.addLayout(self.select_radar_layout)
        # main_layout.addWidget(self.evm_param_table)
        main_layout.addWidget(self.tab_widget_main)
        main_layout.addWidget(self.browse_config_button)
        main_layout.addWidget(self.connect_button)
        main_layout.addWidget(self.send_button)
        main_layout.addWidget(self.stop_device_button)

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
        # EVM Information Table Update
        self.on_radar_selection_changed()
        self.select_radar_combo_box.currentTextChanged.connect(self.on_radar_selection_changed)
        self.select_default_best_Config_combo_box.currentTextChanged.connect(self.on_radar_selection_changed)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # self.radar_cfg_table.cellChanged.connect(self.on_radar_cfg_table_cell_changed)
        self.chirp_cfg_table.cellChanged.connect(self.on_chirp_cfg_table_cell_changed)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.apply_changes_to_cfg_file_push_button.clicked.connect(self.on_apply_changes_to_cfg_file_push_button)
        self.save_cfg_push_button.clicked.connect(self.save_updated_configuration)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        self.settings_table.cellChanged.connect(self.on_settings_table_cell_changed)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    def on_settings_table_cell_changed(self, row, column):
        # Get the edited item
        item = self.settings_table.item(row, column)
        if not item:
            return

        try:
            # Retrieve and convert the new value from the cell
            new_value = float(item.text().strip())

            # Get parameter name from the first column of the settings table
            param = self.settings_table.item(row, 0).text()

            # Update radar parameters if valid
            valid_params = {
                "Range-Doppler Heatmap Minimum Value": "Range-Doppler Heatmap Minimum Value",
                "Range-Doppler Heatmap Maximum Value": "Range-Doppler Heatmap Maximum Value",
                "Range-Doppler Heatmap Grid Size": "Range-Doppler Heatmap Grid Size",
                "Azimuth Static Heatmap Minimum Value": "Azimuth Static Heatmap Minimum Value",
                "Azimuth Static Heatmap Maximum Value": "Azimuth Static Heatmap Maximum Value",
                "Azimuth Static Heatmap Grid Size": "Azimuth Static Heatmap Grid Size"
            }

            if param in valid_params:
                self.radar_params[param] = new_value
                print(f"Parameter '{param}' updated to {new_value}")
            else:
                print(f"Unknown parameter: {param}")
        except ValueError:
            print(f"Invalid input: Unable to convert '{item.text().strip()}' to a float.")
        except Exception as e:
            print(f"Error updating parameter: {e}")

    def update_radar_params(self, range_fft_size, doppler_fft_size):
        self.radar_params["Number of Range FFT Bins"] = int(range_fft_size)
        self.radar_params["Number of Doppler FFT Bins"] = int(doppler_fft_size)
        logging.info("Radar parameters updated.")

    def save_updated_configuration(self):
        """Save the updated configuration (self.commands and self.config_params) to a new file."""

        original_base_name = self.select_radar_combo_box.currentText()
        current_date_time = datetime.now().strftime('%Y%m%d_%H%M%S')
        suggested_file_name = f"{original_base_name}_updated_{current_date_time}.cfg"

        # Show "Save As" dialog with suggested name
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        save_path, _ = QFileDialog.getSaveFileName(
            self,
            "Save Updated Config File",
            suggested_file_name,
            "Config Files (*.cfg);;All Files (*)",
            options=options
        )

        if save_path:
            try:
                # Open the file for writing
                with open(save_path, 'w') as file:
                    # First, write comments (if any)
                    comments = [
                        "% ***************************************************************",
                        "% Created for TI-mmWave Radars Configuration",
                        "% ***************************************************************"
                    ]
                    for comment in comments:
                        file.write(comment + "\n")

                    # # Write the commands and their parameters from self.commands
                    # for command, params in self.commands.items():
                    #     file.write(f"{command} {' '.join(params)}\n")
                    for row in range(self.command_table.rowCount()):
                        command_item = self.command_table.item(row, 0)  # First column: Command name
                        param_item = self.command_table.item(row, 1)
                        if not command_item:
                            continue
                        # Get the text from the table items
                        command_text = command_item.text().strip() if command_item else ""
                        param_text = param_item.text().strip() if param_item else ""

                        # Write the command and its parameters
                        file.write(f"{command_text} {param_text}\n")

                self.command_textbox.appendPlainText(f"Configuration saved successfully to: {save_path}")
            except Exception as e:
                self.command_textbox.appendPlainText(f"Failed to save the file: {str(e)}")

    def on_apply_changes_to_cfg_file_push_button(self, update_commands=None):
        """
        Handle the 'Apply Changes to Config File' button click.

        Args:
            update_commands (list or None): List of command names to update.
                If None, updates all commands.
        """
        radar_params = self.radar_params  # Step 1: Read the current radar_params

        # Step 2: Iterate through the rows of the table and apply updates
        for row in range(self.command_table.rowCount()):
            command_item = self.command_table.item(row, 0)  # First column: Command name
            if not command_item:
                continue
            command = command_item.text()

            if update_commands and command not in update_commands:
                continue

            params_item = self.command_table.item(row, 1)  # Second column: Parameters
            if not params_item:
                continue
            params = params_item.text().split()

            row_updated = False  # Flag to track if any parameter in the row is updated

            if command == 'profileCfg':
                row_updated = self.update_profile_cfg(params, radar_params)

            elif command == 'frameCfg':
                row_updated = self.update_frame_cfg(params, radar_params)

            elif command == 'cfarCfg':
                row_updated = self.update_cfar_cfg(params, radar_params)

            elif command == 'aoaFovCfg':
                row_updated = self.update_aoa_fov_cfg(params, radar_params)

            elif command == 'cfarFovCfg':
                row_updated = self.update_cfar_fov_cfg(params, radar_params)

            elif command == 'clutterRemoval':
                row_updated = self.update_clutter_removal(params, radar_params)

            elif command == 'channelCfg':
                # Handle both channelCfg and chirpCfg updates
                row_updated = self.update_channel_cfg(params, radar_params)
                self.update_chirp_cfg(radar_params)

            elif command == 'chirpCfg':
                self.update_chirp_cfg(radar_params)

            elif command == 'guiMonitor':
                params, row_updated = self.update_gui_monitor(radar_params)

            if row_updated:
                self.update_table_row(row, params)

    def get_command_rows(self, command_name):
        """
        Retrieve all rows in the command table that match the given command name.

        Args:
            command_name (str): The name of the command to search for.

        Returns:
            list: A list of row indices corresponding to the command.
        """
        rows = []
        for row in range(self.command_table.rowCount()):
            if self.command_table.item(row, 0) and self.command_table.item(row, 0).text() == command_name:
                rows.append(row)
        return rows

    def update_chirp_cfg(self, radar_params):
        """
        Update the chirpCfg parameters in the command table based on radar parameters.
        """
        waveform_multiplexing = radar_params.get('Waveform Multiplexing', '')
        num_tx = radar_params.get('Number of TX Antennas', 0)

        # Define chirp parameters for various configurations
        chirp_params_map = {
            (1, 'Phased-Array'): [['chirpCfg', '00000001'], ['chirpCfg', '11000001']],
            (1, 'TDM-MIMO'): [['chirpCfg', '00000001'], ['chirpCfg', '11000000']],
            (2, 'Phased-Array'): [['chirpCfg', '00000005'], ['chirpCfg', '11000005']],
            (2, 'TDM-MIMO'): [['chirpCfg', '00000001'], ['chirpCfg', '11000004']],
            (3, 'Phased-Array'): [['chirpCfg', '00000007'], ['chirpCfg', '11000007'],
                                  ['chirpCfg', '22000007']],
            (3, 'TDM-MIMO'): [['chirpCfg', '00000001'], ['chirpCfg', '11000004'],
                              ['chirpCfg', '22000002']],
        }

        # Get the chirpCfg parameters based on radar settings
        chirp_params = chirp_params_map.get((num_tx, waveform_multiplexing), [])

        # Find all chirpCfg rows in the command table
        chirp_cfg_rows = self.get_command_rows('chirpCfg')

        # Update or insert rows in the command table
        for i, chirp_param in enumerate(chirp_params):

            if i < len(chirp_cfg_rows):
                self.update_table_row(chirp_cfg_rows[i], chirp_param[1])
            else:
                # Add new rows if required
                row_index = chirp_cfg_rows[-1] + i - len(
                    chirp_cfg_rows) + 1 if chirp_cfg_rows else self.command_table.rowCount()
                self.command_table.insertRow(row_index)
                self.command_table.setItem(row_index, 0, QTableWidgetItem(chirp_param[0]))
                self.update_table_row(row_index, chirp_param[1])

        # Remove extra chirpCfg rows if the table has more rows than required
        chirp_cfg_rows = self.get_command_rows('chirpCfg')
        num_required_rows = len(chirp_params)
        num_existing_rows = len(chirp_cfg_rows)
        if num_existing_rows > num_required_rows:
            rows_to_remove = chirp_cfg_rows[num_required_rows:]  # Extra rows to delete
            for row_index in reversed(rows_to_remove):  # Remove from bottom to top
                self.command_table.removeRow(row_index)

        return True

    def update_channel_cfg(self, params, radar_params):
        """
        Update parameters for the 'channelCfg' command.
        """
        updated = False

        # Extract current values from radar_params
        num_rx = radar_params.get('Number of RX Antennas', 0)
        num_tx = radar_params.get('Number of TX Antennas', 0)
        cascading = radar_params.get('Cascading', 0)

        # Compute new Rx and Tx bitmasks
        new_rx_en = (1 << num_rx) - 1  # Enable the first num_rx antennas
        new_tx_en = (1 << num_tx) - 1  # Enable the first num_tx antennas
        if new_tx_en == 3:
            new_tx_en = 5
        # print("new_tx_en = ", new_tx_en)

        # Update parameters if they have changed
        if int(params[0]) != new_rx_en:
            params[0] = str(new_rx_en)
            updated = True
        if int(params[1]) != new_tx_en:
            params[1] = str(new_tx_en)
            updated = True
        if int(params[2]) != cascading:
            params[2] = str(cascading)
            updated = True

        return updated

    def update_gui_monitor(self, radar_params):
        params = radar_params["GUI Monitor"]
        return params, True

    def update_cfg_param(self, params, radar_params, index, key, scale=1.0, fmt="{:.2f}"):
        value = radar_params.get(key, None)
        if value is not None:
            scaled_value = float(value) * scale
            # Format as an integer if the value is a whole number
            if scaled_value.is_integer():
                formatted_value = "{}".format(int(scaled_value))
            else:
                formatted_value = fmt.format(scaled_value)

            if params[index] != formatted_value:
                params[index] = formatted_value
                return True
        return False

    def update_profile_cfg(self, params, radar_params):
        """Update parameters for the 'profileCfg' command."""
        updated = False
        updated |= self.update_cfg_param(params, radar_params, 1, 'Frequency Start [GHz]', scale=1.0, fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 2, 'Idle Time [us]', fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 3, 'ADC Valid Start Time [us]', fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 4, 'Ramp End Time [us]', fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 7, 'Frequency Slope [MHz/us]', fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 8, "Number of Bursts in Frame", scale=1, fmt="{}")
        updated |= self.update_cfg_param(params, radar_params, 9, "Number of Samples per Chirp", scale=1, fmt="{}")
        updated |= self.update_cfg_param(params, radar_params, 10, "Sample Rate [KHz]", scale=1, fmt="{}")
        return updated

    def update_frame_cfg(self, params, radar_params):
        """Update parameters for the 'frameCfg' command."""
        updated = False
        updated |= self.update_cfg_param(params, radar_params, 1, 'Number of Loops', scale=1.0, fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 2, 'Number of Chirps in Loop', scale=1.0, fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 4, 'Frame Periodicity [ms]', scale=1.0, fmt="{:.2f}")
        return updated

    def update_cfar_cfg(self, params, radar_params):
        """Update parameters for the 'cfarCfg' command."""
        cfar_type = params[1]  # Range (0) or Doppler (1)
        updated = False

        # Define the CFAR parameters to be updated based on the CFAR type (Range or Doppler)
        if cfar_type == '0':  # Range CFAR
            updated |= self.update_cfg_param(params, radar_params, -2, 'Range Threshold (CFAR) [dB]', scale=1.0,
                                             fmt="{:.2f}")
        elif cfar_type == '1':  # Doppler CFAR
            updated |= self.update_cfg_param(params, radar_params, -2, 'Doppler Threshold (CFAR) [dB]', scale=1.0,
                                             fmt="{:.2f}")

        return updated

    def update_aoa_fov_cfg(self, params, radar_params):
        """Update parameters for the 'aoaFovCfg' command."""
        updated = False
        updated |= self.update_cfg_param(params, radar_params, 1, 'Azimuth Min [deg.]', scale=1.0, fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 2, 'Azimuth Max [deg.]', scale=1.0, fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 3, 'Elevation Min [deg.]', scale=1.0, fmt="{:.2f}")
        updated |= self.update_cfg_param(params, radar_params, 4, 'Elevation Max [deg.]', scale=1.0, fmt="{:.2f}")

        return updated

    def update_cfar_fov_cfg(self, params, radar_params):
        """
        Update the parameters for the 'cfarFovCfg' command in the table.
        """
        fov_type = int(params[1])  # 0 = Range, 1 = Doppler

        # Helper to update the value based on the fov_type (Range or Doppler)
        if fov_type == 0:  # Range FOV
            updated = False
            updated |= self.update_cfg_param(params, radar_params, 2, 'Range Min [m]', scale=1.0, fmt="{:.2f}")
            updated |= self.update_cfg_param(params, radar_params, 3, 'Range Max [m]', scale=1.0, fmt="{:.2f}")
            return updated
        elif fov_type == 1:  # Doppler FOV
            updated = False
            updated |= self.update_cfg_param(params, radar_params, 2, 'Doppler Min [Hz]', scale=1.0, fmt="{:.2f}")
            updated |= self.update_cfg_param(params, radar_params, 3, 'Doppler Max [Hz]', scale=1.0, fmt="{:.2f}")
            return updated
        return False

    def update_clutter_removal(self, params, radar_params):
        """Update parameters for the 'clutterRemoval' command."""

        def update_param(index, key):
            value = radar_params.get(key, None)
            if value is not None:
                value_str = '0' if value is False or value == 0 else '1'
                if params[index] != value_str:
                    params[index] = value_str
                    return True
            return False

        return update_param(1, 'Clutter Removal')

    def update_table_row(self, row, params):
        """Update the table row with the new parameter values."""
        self.command_table.setItem(row, 1, QTableWidgetItem(' '.join(params)))
        # Apply a random background color to the entire row
        random_color = QColor(random.randint(200, 255), random.randint(200, 255), random.randint(200, 255))
        for col in range(self.command_table.columnCount()):
            cell_item = self.command_table.item(row, col)
            if cell_item is None:
                cell_item = QTableWidgetItem("")  # Create a new item if none exists
                self.command_table.setItem(row, col, cell_item)
            cell_item.setBackground(random_color)

    def on_chirp_cfg_table_cell_changed(self, row, column):
        """
        Handle changes made to the chirp configuration table.

        This method processes user modifications to specific parameters and updates
        the radar configuration accordingly while temporarily blocking signals to
        avoid recursive triggers.

        Args:
            row (int): The row index of the changed cell.
            column (int): The column index of the changed cell.
        """
        # Temporarily block signals to prevent recursive updates
        # self.radar_cfg_table.blockSignals(True)
        self.settings_table.blockSignals(True)
        self.chirp_cfg_table.blockSignals(True)

        try:
            # Retrieve the changed item
            item = self.chirp_cfg_table.item(row, column)
            if not item:
                return

            # Get the parameter name from the first column
            param = self.chirp_cfg_table.item(row, 0).text()
            new_value = self.chirp_cfg_table.item(row, 1).text()

            # Process the parameter changes
            calculated_params = {}
            if param == "Frequency Slope [MHz/us]":
                calculated_params["Frequency Slope [MHz/us]"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='profileCfg')

            elif param == "Frequency Start [GHz]":
                calculated_params["Frequency Start [GHz]"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='profileCfg')

            elif param == "Number of Samples per Chirp":
                calculated_params["Number of Samples per Chirp"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='profileCfg')

            elif param == "Number of Chirps in Loop":
                calculated_params["Number of Chirps in Loop"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='frameCfg')

            elif param == "Sample Rate [KHz]":
                calculated_params["Sample Rate [KHz]"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='profileCfg')

            elif param == "Idle Time [us]":
                calculated_params["Idle Time [us]"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='profileCfg')

            elif param == "ADC Valid Start Time [us]":
                calculated_params["ADC Valid Start Time [us]"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='profileCfg')

            elif param == "Number of Loops":
                calculated_params["Number of Loops"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='frameCfg')

            elif param == "Number of Bursts in Frame":
                calculated_params["Number of Bursts in Frame"] = float(new_value)
                self.handle_cfg_update(calculated_params, cfgType='profileCfg')

            elif param == "Measurement Rate [Hz]":
                calculated_params["Frame Periodicity [ms]"] = 1 / float(new_value) * 1000
                self.handle_cfg_update(calculated_params, cfgType='frameCfg')

            elif param == "Range Threshold (CFAR) [dB]":
                self.handle_cfar_update('range', float(new_value))

            elif param == "Doppler Threshold (CFAR) [dB]":
                self.handle_cfar_update('doppler', float(new_value))

            selected_radar = self.select_radar_combo_box.currentText()
            self.parse_commands_information("command_table", self.radar_params)
            self.set_tables_information(self.radar_params, selected_radar)
        finally:
            # Ensure signals are unblocked after processing
            # self.radar_cfg_table.blockSignals(False)
            self.settings_table.blockSignals(False)
            self.chirp_cfg_table.blockSignals(False)

    def handle_cfar_update(self, cfar_type, new_value):
        """
        Handle updates for Range CFAR or Doppler CFAR.

        Parameters:
            cfar_type (str): 'range' or 'doppler' to specify which CFAR to update.
            new_value (float): The new value to be set.
        """

        table = self.command_table
        for row in range(table.rowCount()):
            item = table.item(row, 0)
            if item and item.text().startswith('cfarCfg'):
                item_parts = table.item(row, 1)
                parts_cfar = item_parts.text().split()

                # Determine which CFAR to update
                if cfar_type == 'range' and parts_cfar[1] == '0':  # Range CFAR
                    # Check if the value is a whole number and format accordingly
                    if new_value.is_integer():
                        parts_cfar[-2] = str(int(new_value))  # Format as integer
                    else:
                        parts_cfar[-2] = str(new_value)  # Keep decimal value
                    self.radar_params["Range Threshold (CFAR) [dB]"] = new_value
                elif cfar_type == 'doppler' and parts_cfar[1] == '1':  # Doppler CFAR
                    # Check if the value is a whole number and format accordingly
                    if new_value.is_integer():
                        parts_cfar[-2] = str(int(new_value))  # Format as integer
                    else:
                        parts_cfar[-2] = str(new_value)  # Keep decimal value
                    self.radar_params["Doppler Threshold (CFAR) [dB]"] = new_value
                else:
                    continue  # Skip if it doesn't match the CFAR type

                self.on_apply_changes_to_cfg_file_push_button(update_commands=['cfarCfg'])
                # Check if the command port is connected
                if not self.command_port_connected:
                    print("Error: Command port is not connected")
                    self.command_textbox.appendPlainText("Error: Command port is not connected")
                    return

                # Combine updated parts into a command string
                full_command = " ".join(["cfarCfg"] + parts_cfar)

                # Display the command being sent
                self.command_textbox.appendPlainText(f"Sending commands to {self.command_port.name}")
                self.command_textbox.appendPlainText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
                self.command_textbox.appendPlainText(full_command)

                # Send the command using self.send_command
                self.send_command(full_command)

    def handle_cfg_update(self, calculated_params, cfgType):
        self.radar_params.update(calculated_params)
        self.on_apply_changes_to_cfg_file_push_button(update_commands=[cfgType])

    def update_radar_parameters_and_tables_with_calculated_params(self, calculated_params, parameter_limits=None):
        """
        Updates radar parameters and tables while applying a background color
        if parameters exceed their limits. If no limits are provided, updates normally.

        :param calculated_params: Dictionary of parameters and their calculated values.
        :param parameter_limits: Dictionary of parameter names and their (min, max) limits, or None.
        """
        self.radar_params.update(calculated_params)
        for key, value in calculated_params.items():
            # Determine table to update
            target_table = self.chirp_cfg_table if key in self.chirp_cfg_table_headers else self.radar_cfg_table

            # Default colors
            background_color = None
            text_color = None

            # Check if limits exist and the parameter is in the limits dictionary
            if parameter_limits and key in parameter_limits:
                lower_limit, upper_limit = parameter_limits[key]
                # Determine background color based on whether the value is within limits
                if value < lower_limit or value > upper_limit:
                    background_color = QColor("red")  # Red for out-of-limit values
                    text_color = QColor("white")

            # Update the table cell
            self.update_table_cell(target_table, key, value, text_color=text_color, background_color=background_color)

    @staticmethod
    def update_table_cell(table, parameter_name, value, text_color=None, background_color=None):
        """
        Updates the cell in the specified table for the given parameter name.
        :param table: QTableWidget instance
        :param parameter_name: The name of the parameter to update (first column)
        :param value: The new value to set
        :param text_color: Optional; QColor instance for text color
        :param background_color: Optional; QColor instance for background color
        """
        row_count = table.rowCount()
        for row in range(row_count):
            param = table.item(row, 0).text()
            if param == parameter_name:
                # Format value: Use integer format if it's a whole number
                formatted_value = f"{value:.3f}" if not float(value).is_integer() else str(int(value))
                item = QTableWidgetItem(formatted_value)

                # Set text color if specified
                if text_color:
                    item.setForeground(text_color)

                # Set background color if specified
                if background_color:
                    item.setBackground(background_color)

                # Update the table item
                table.setItem(row, 1, item)
                break

    def update_radar_parameters(self, bandwidth_MHz, range_resolution_m, freq_slope_MHz_us):
        """Update the radar parameters dictionary."""
        self.radar_params["Range Resolution [m]"] = range_resolution_m
        self.radar_params["Frequency Slope [MHz/us]"] = freq_slope_MHz_us
        self.radar_params["Bandwidth [MHz]"] = bandwidth_MHz
        self.radar_params["Beat Frequency [MHz]"] = self.radar_params["Beat Frequency [MHz]"]

    def show_warning(self, message):
        """
        Displays a warning message to the user.
        :param message: The warning message to display
        """
        QMessageBox.warning(self, "Adjustment Notification", message)

    def on_radar_selection_changed(self):
        # This method runs when the selection in the combo box changes
        selected_radar = self.select_radar_combo_box.currentText()
        selected_desirable_config = self.select_default_best_Config_combo_box.currentText()

        evm_info = self.set_evm_info(selected_radar)
        self.update_table(self.evm_param_table, evm_info, selected_radar)

        # adding default best configurations
        self.set_best_default_config(selected_radar, selected_desirable_config)

    def show_serial_ports(self):
        # Clear existing data from the table
        self.table.setRowCount(0)

        # Get a list of available serial ports
        ports = serial.tools.list_ports.comports()
        idx = 0

        # Populate the table with serial ports
        for i in range(len(ports) - 2, len(ports)): # on Linux
        # for i in range(0, len(ports)): # on Window
            port = ports[i]
            self.table.insertRow(idx)
            self.table.setItem(idx, 0, QTableWidgetItem(port.device))

            # Add checkboxes in the Data and Command columns
            data_checkbox = QCheckBox()
            command_checkbox = QCheckBox()
            self.table.setCellWidget(idx, 1, data_checkbox)
            self.table.setCellWidget(idx, 2, command_checkbox)

            # Set the checkboxes automatically but did not work on Window os because of the port ordering system
            first_port = len(ports) - 2
            second_port = len(ports) - 1
            if port.description != "n/a" and i == first_port:
                command_checkbox.setChecked(True)
            elif port.description != "n/a" and i == second_port:
                data_checkbox.setChecked(True)

            # Populate other columns
            self.table.setItem(idx, 3, QTableWidgetItem(port.description))
            self.table.setItem(idx, 4, QTableWidgetItem(port.manufacturer))
            self.table.setItem(idx, 5, QTableWidgetItem(port.hwid))
            idx += 1

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
        """Connect to a specified serial port with given connection type."""
        try:
            self.command_textbox.appendPlainText(f"Attempting to connect to {connection_type} port: {port_name}")

            if connection_type == "Data":
                if self.data_port_connected:
                    self.data_port.close()
                    self.data_port = None
                    self.command_textbox.appendPlainText("Disconnected existing data port connection.")

                self.data_port = serial.Serial(port_name, baudrate=921600, timeout=2)

                # Set buffer size (if supported)
                buffer_size = 16384
                if hasattr(self.data_port, "set_buffer_size"):
                    try:
                        self.data_port.set_buffer_size(rx_size=buffer_size)
                        self.command_textbox.appendPlainText(f"Buffer size set to {buffer_size} bytes")
                    except Exception as e:
                        self.command_textbox.appendPlainText(f"Failed to set buffer size: {e}")

                self.data_port_connected = True
                self.command_textbox.appendPlainText(
                    f"Connected to data port {self.data_port.name} with baudrate {self.data_port.baudrate}")

            elif connection_type == "Command":
                if self.command_port_connected:
                    self.command_port.close()
                    self.command_port = None
                    self.command_textbox.appendPlainText("Disconnected existing command port connection.")

                self.command_port = serial.Serial(port_name, baudrate=115200, timeout=2)
                self.command_port_connected = True
                self.command_textbox.appendPlainText(
                    f"Connected to command port {self.command_port.name} with baudrate {self.command_port.baudrate}")

            # Update UI components
            self.update_circle_widgets()

        except serial.SerialException as e:
            self.command_textbox.appendPlainText(f"Failed to connect to {connection_type} port: {e}")

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

    def send_configuration(self):
        # Check if the command port is defined
        if not hasattr(self, 'command_port') or self.command_port is None:
            self.command_textbox.appendPlainText("Error: Command port is not defined or initialized.")
            return

        # Check if the command port is connected
        self.command_textbox.appendPlainText(f"Sending device configurations to command port {self.command_port.name}")

        if not self.command_port_connected:
            self.command_textbox.appendPlainText("Error: Command port is not connected")
            return

        self.command_textbox.appendPlainText(f"Sending commands to {self.command_port.name}")
        self.command_textbox.appendPlainText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

        # Loop through the command_table to read commands
        for row in range(self.command_table.rowCount()):
            # Extract command from the table (e.g., first column, second column)
            command_item = self.command_table.item(row, 0)  # First column: command
            parameter_item = self.command_table.item(row, 1)  # Second column: parameters

            # Ensure the item is valid (not None)
            if command_item is not None:
                first_part_command = command_item.text().strip()  # Remove any spaces or newlines
                parameters = parameter_item.text().strip()
                full_command = f"{first_part_command} {parameters}"  # Combine command and parameters

                command_bytes = full_command.encode('latin1') + b'\n'
                self.command_port.write(command_bytes)
                time.sleep(0.1)

                # Read the response
                byteCount = self.command_port.in_waiting
                if byteCount > 0:
                    response_bytes = self.command_port.read(byteCount)
                    response_str = response_bytes.decode('latin1').strip().replace("\n", "\n\t")
                    print(response_str)
                    self.command_textbox.appendPlainText(f"Response : {response_str}")
            else:
                print(f"Row {row}: Command is empty or invalid.")
                self.command_textbox.appendPlainText(f"Row {row}: Command is empty or invalid.")

        self.command_textbox.appendPlainText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
        # self.send_button.setEnabled(False)
        time.sleep(0.2)

    def stop_device(self):
        self.command_port.write(b'sensorStop \n')
        time.sleep(0.1)

        # Read the response
        byteCount = self.command_port.in_waiting
        if byteCount > 0:
            response_bytes = self.command_port.read(byteCount)
            response_str = response_bytes.decode('latin1').strip().replace("\n", "\n\t")
            print(response_str)
            self.command_textbox.appendPlainText(f"Response : {response_str}")

    def on_plot_selection_toggled(self, state, row, param):
        """
        This function is called when the state of a checkbox changes.
        Updates the radar parameters based on the checkbox state.

        Args:
            state (Qt.CheckState): The state of the checkbox (checked or unchecked).
            row (int): The row number of the command in the table.
            param (str): The specific parameter (e.g., "Scatter Plot").
        """
        print(f"State: {state}, Row: {row}, Param: {param}")
        # Convert state to a boolean
        is_checked = state == Qt.Checked  # True if checked, False otherwise

        calculated_params = {}

        # update_rate_max_Hz = 1
        # Determine the parameters based on the checkbox state
        if param == "Scatter Plot":
            self.radar_params["GUI Monitor"][1] = "1" if is_checked else "0"
        elif param == "Range Profile":
            self.radar_params["GUI Monitor"][2] = "1" if is_checked else "0"
        elif param == "Noise Profile":
            self.radar_params["GUI Monitor"][3] = "1" if is_checked else "0"

        elif param == "Range Azimuth Heat Map":
            calculated_params["Frame Periodicity [ms]"] = 1000
            self.handle_cfg_update(calculated_params, cfgType='frameCfg')
            self.radar_params["GUI Monitor"][4] = "1" if is_checked else "0"

        elif param == "Range Doppler Heat Map":
            calculated_params["Frame Periodicity [ms]"] = 1000
            self.handle_cfg_update(calculated_params, cfgType='frameCfg')
            self.radar_params["GUI Monitor"][5] = "1" if is_checked else "0"

        elif param == "Statistics":
            self.radar_params["GUI Monitor"][6] = "1" if is_checked else "0"

        gui_monitor_row = self.find_row_by_value(self.command_table, "guiMonitor")
        if gui_monitor_row == -1:
            print("Error: 'guiMonitor' command not found in the command table")
            self.command_textbox.appendPlainText("Error: 'guiMonitor' command not found in the table")
            return

        self.on_apply_changes_to_cfg_file_push_button(update_commands=['guiMonitor'])

    def on_clutter_removal_toggled(self, state, row, params):
        """
        Handle the toggling of the clutter removal option.

        Parameters:
            state (Qt.CheckState): The state of the checkbox (checked or unchecked).
            row (int): The row number of the clutter removal command in the table.
        """
        clutter_removal_row = self.find_row_by_value(self.command_table, "clutterRemoval")
        if clutter_removal_row == -1:
            print("Error: 'clutterRemoval' command not found in the command table")
            self.command_textbox.appendPlainText("Error: 'clutterRemoval' command not found in the table")
            return
        # Determine the clutter removal parameters based on the checkbox state
        parameters = "-1 1" if state == Qt.Checked else "-1 0"
        self.radar_params["Clutter Removal"] = state
        self.on_apply_changes_to_cfg_file_push_button(update_commands=['clutterRemoval'])

        # Check if the command port is connected
        if not self.command_port_connected:
            print("Error: Command port is not connected")
            self.command_textbox.appendPlainText("Error: Command port is not connected")
            return

        # Construct the full command
        full_command = f"clutterRemoval {parameters}"

        # Send the command using the send_command method
        self.send_command(full_command)

    def find_row_by_value(self, table, search_value):
        """
        Search for a row in the table where the first column matches search_value.
        :param table: QTableWidget object
        :param search_value: Value to search in the first column
        :return: Row index if found, -1 otherwise
        """
        for row in range(table.rowCount()):
            item = table.item(row, 0)  # Check the first column
            if item and item.text().strip() == search_value:
                return row  # Return the row index
        return -1  # Not found

    def browse_configuration(self):
        # self.radar_cfg_table.blockSignals(True)
        self.settings_table.blockSignals(True)
        self.chirp_cfg_table.blockSignals(True)
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly
        file_path, _ = QFileDialog.getOpenFileName(self, "Select Config File", "", "Config Files (*.cfg);;All Files (*)")
        if file_path:
            # Store the original file path for later use
            self.original_file_path = file_path
            # try:
            selected_radar = self.select_radar_combo_box.currentText()
            commands1 = self.load_configuration(file_path)
            # print(commands1)
            # Convert commands1 to a list of tuples
            command_tuples = []
            for command in commands1:
                parts = command.split(" ", 1)  # Split into command and parameters
                if len(parts) == 1:
                    command_tuples.append((parts[0], ""))  # No parameters
                else:
                    command_tuples.append((parts[0], parts[1]))  # Command and parameters

            # Use update_specified_table to display command_tuples in command_table
            self.update_specified_table("command_table", command_tuples)

            # self.commands = commands1
            # self.parse_commands_information(self.commands, self.radar_params)
            self.parse_commands_information("command_table", self.radar_params)
            self.set_tables_information(self.radar_params, selected_radar)
            self.connect_button.setEnabled(True)
            self.command_textbox.appendPlainText("".join(file_path))
            # self.radar_cfg_table.blockSignals(False)
            self.settings_table.blockSignals(False)
            self.chirp_cfg_table.blockSignals(False)

    def default_best_configuration(self, command_tuples):
        self.settings_table.blockSignals(True)
        self.chirp_cfg_table.blockSignals(True)
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly

        selected_radar = self.select_radar_combo_box.currentText()
        # Use update_specified_table to display command_tuples in command_table
        self.update_specified_table("command_table", command_tuples)
        self.parse_commands_information("command_table", self.radar_params)
        self.set_tables_information(self.radar_params, selected_radar)
        self.connect_button.setEnabled(True)
        self.settings_table.blockSignals(False)
        self.chirp_cfg_table.blockSignals(False)

    def load_configuration(self, file_path):
        commands = []
        # self.config_params.clear()
        with open(file_path, 'r') as file:
            for line in file:
                if line.strip() and not line.startswith('%'):
                    commands.append(line.strip())
        return commands

    def find_command(self,cmd_name, table_id):
        # Safely get the table widget by table_id
        table = getattr(self, table_id, None)
        if table is None:
            raise AttributeError(f"Table '{table_id}' does not exist in this class.")

        if not hasattr(table, 'rowCount') or not hasattr(table, 'item'):
            raise TypeError(f"The attribute '{table_id}' is not a valid table widget.")

        # Helper function to find a command in the table
        for row in range(table.rowCount()):
            item = table.item(row, 0)
            if item and item.text().startswith(cmd_name):
                return item.text(), row
        return None, None

    def parse_commands_information(self, table_id, radar_params):
        """
        Parse radar command configurations from a table and update radar_params.

        :param table_id: String name of the table widget (e.g., 'commands_table').
        :param radar_params: Dictionary to store radar parameters.
        """

        # Helper function to validate and retrieve table rows
        def get_table_row(command_name):
            text, row = self.find_command(command_name, table_id)
            if not text:
                raise ValueError(f"Missing {command_name} command")
            return row

        # Helper function to extract specific indices from a row
        def extract_values_from_row(row, indices):
            parts = self.command_table.item(row, 1).text().split()
            return [parts[i] for i in indices]

        # Helper function to parse CFAR configuration
        def parse_cfar_configuration():
            range_cfar, doppler_cfar = None, None
            for row in range(table.rowCount()):
                item = table.item(row, 0)
                if item and item.text().startswith('cfarCfg'):
                    parts = table.item(row, 1).text().split()
                    if parts[1] == '0':  # Range CFAR
                        range_cfar = int(parts[-2])
                    elif parts[1] == '1':  # Doppler CFAR
                        doppler_cfar = int(parts[-2])
            return range_cfar, doppler_cfar

        # Helper function to parse AoA FOV configuration
        def parse_aoa_fov():
            aoa_cfg_row = get_table_row('aoaFovCfg')
            return map(float, extract_values_from_row(aoa_cfg_row, range(1, 5)))

        # Helper function to parse range and Doppler limits
        def parse_limits(command_name, fov_type, default_limits):
            for row in range(table.rowCount()):
                item = table.item(row, 0)
                if item and item.text().startswith(command_name):
                    parts = table.item(row, 1).text().split()
                    if parts[1] == fov_type:
                        return [float(parts[-2]), float(parts[-1])]
            return default_limits

        def parse_channel_cfg(command_row):
            """
            Parse the channelCfg command to extract the Rx and Tx antennas configurations.
            """
            parts = self.command_table.item(command_row, 1).text().split()
            rx_en = int(parts[0])  # Receive Enable (RxEn) as bitmask
            tx_en = int(parts[1])  # Transmit Enable (TxEn) as bitmask
            cascading = int(parts[2])  # Cascading configuration (0 or 1)

            # Parse the number of active Rx and Tx antennas based on the bitmask
            num_rx = bin(rx_en).count('1')  # Count the number of '1' bits in RxEn
            num_tx = bin(tx_en).count('1')  # Count the number of '1' bits in TxEn

            return num_rx, num_tx, cascading

        # Validate table
        table = getattr(self, table_id, None)
        if not table or not hasattr(table, 'rowCount') or not hasattr(table, 'item'):
            raise ValueError(f"Invalid or non-existent table widget: '{table_id}'")

        # Parse radar configurations
        selected_radar = self.select_radar_combo_box.currentText()


        # Parse profile configuration
        profile_cfg_row = get_table_row('profileCfg')
        profile_indices = [7, 2, 4, 3, 10, 1, 9, 8]
        profile_values = extract_values_from_row(profile_cfg_row, profile_indices)
        profile_values = list(map(float, profile_values[:-2])) + list(map(int, profile_values[-2:]))  # Fix here
        freq_slope, idle_time, ramp_time, adc_start, sample_rate, freq_start, samples_per_chirp, bursts_per_frame = (
            profile_values)
        chirp_time = self.radar_calculator.calculate_chirp_time_us_from_ramp(ramp_time, adc_start)
        chirp_cycle_time = self.radar_calculator.calculate_chirp_cycle_time_us(idle_time, adc_start, chirp_time)

        adc_sampling_time_us = samples_per_chirp / sample_rate * 1e3

        bandwidth = self.radar_calculator.calculate_bandwidth_from_freq_slope(freq_slope, adc_sampling_time_us)

        range_resolution = self.radar_calculator.calculate_range_resolution(bandwidth)
        beat_freq = round(0.8 * sample_rate * 1e-3, 3)
        unambiguous_range = self.radar_calculator.calculate_unambiguous_range(beat_freq, freq_slope)
        maximum_range = round(samples_per_chirp * range_resolution,1)

        # Parse channelCfg command for number of TX and RX antennas and Cascading
        channel_cfg_row = get_table_row('channelCfg')
        num_rx, num_tx, cascading = parse_channel_cfg(channel_cfg_row)

        chirp_repetition_period = round(num_tx * chirp_cycle_time)

        # Parse frame configuration
        frame_cfg_row = get_table_row('frameCfg')
        frame_indices = [4, 2, 1]
        frame_values = extract_values_from_row(frame_cfg_row, frame_indices)
        frame_values = list(map(float, frame_values[:-1])) + list(map(int, frame_values[-1:]))  # Fix here
        frame_periodicity, chirps_per_loop, num_loops = frame_values
        chirps_per_burst = chirps_per_loop * (num_loops+1)
        chirps_per_frame = chirps_per_burst * bursts_per_frame
        burst_periodicity = self.radar_calculator.calculate_burst_periodicity_us(ramp_time, idle_time, chirps_per_burst)

        active_frame_time = self.radar_calculator.calcuate_active_frame_time_ms(chirp_repetition_period,
                                                                                chirps_per_loop)

        # Parse CFAR, AoA FOV, and limits
        range_cfar, doppler_cfar = parse_cfar_configuration()
        azimuth_min, azimuth_max, elevation_min, elevation_max = parse_aoa_fov()
        range_limits = parse_limits('cfarFovCfg', '0', [0, 0])
        doppler_limits = parse_limits('cfarFovCfg', '1', [0, 0])

        # Parse chirpCfg
        chirp_cfg_row = get_table_row('chirpCfg')
        waveform_multiplexing_value = extract_values_from_row(chirp_cfg_row,[7])
        waveform_multiplexing = self.parse_waveform_multiplexing(waveform_multiplexing_value)

        virtual_array_length = self.radar_calculator.calculate_virtual_array_length(num_tx, num_rx,waveform_multiplexing)
        unambiguous_velocity, velocity_resolution = self.radar_calculator.calculate_unambiguous_velocity_and_velocity_resolution(
            freq_start, chirp_cycle_time, num_tx, chirps_per_loop, chirps_per_frame, waveform_multiplexing
        )

        # Parse clutter removal
        clutter_command, clutter_row = self.find_command('clutterRemoval', table_id)
        clutter_status = (
            int(self.command_table.item(clutter_row, 1).text().split()[-1]) if clutter_command else None
        )

        # Parse guiMonitor
        gui_monitor_row = get_table_row('guiMonitor')
        gui_monitor_values = extract_values_from_row(gui_monitor_row, list(range(0,7)))

        # self.handle_bandwidth_update(bandwidth)
        numb_range_fft_bins = self.radar_calculator.nextpow2(samples_per_chirp)
        numb_doppler_fft_bins = self.radar_calculator.nextpow2(chirps_per_frame)
        # numb_angle_fft_bins = num_tx * num_rx
        self.update_radar_params(numb_range_fft_bins, numb_doppler_fft_bins)

        radar_cube_size_KB = self.radar_calculator.calculate_radar_cube_size_kb(int(samples_per_chirp),
                                                                                int(chirps_per_frame),
                                                                                virtual_array_length)

        # Update radar parameters
        radar_params.update({
            "Frequency Slope [MHz/us]": freq_slope,
            "Idle Time [us]": idle_time,
            "Ramp End Time [us]": ramp_time,
            "ADC Valid Start Time [us]": adc_start,
            "Chirp Time [us]": chirp_time,
            "Chirp Repetition Period [us]": chirp_repetition_period,
            "Chirp Cycle Time [us]": chirp_cycle_time,
            "Bandwidth [MHz]": bandwidth,
            "Range Resolution [m]": range_resolution,
            "Sample Rate [KHz]": sample_rate,
            "Beat Frequency [MHz]": beat_freq,
            "Maximum Range [m]": maximum_range,
            "Unambiguous Range [m]": unambiguous_range,
            "Unambiguous Velocity [km/h]": unambiguous_velocity,
            "Number of Samples per Chirp": samples_per_chirp,
            "Frequency Start [GHz]": freq_start,
            "Number of Bursts in Frame": bursts_per_frame,
            "Number of Chirps in Burst": chirps_per_burst,
            "Number of Chirps in Frame": chirps_per_frame,
            "Frame Periodicity [ms]": frame_periodicity,
            "Number of Chirps in Loop": chirps_per_loop,
            "Number of Loops": num_loops,
            "Burst Periodicity [us]": burst_periodicity,
            "Velocity Resolution [km/h]": velocity_resolution,
            "Range Threshold (CFAR) [dB]": range_cfar,
            "Doppler Threshold (CFAR) [dB]": doppler_cfar,
            "Clutter Removal": clutter_status,
            "Azimuth Min [deg.]": azimuth_min,
            "Azimuth Max [deg.]": azimuth_max,
            "Elevation Min [deg.]": elevation_min,
            "Elevation Max [deg.]": elevation_max,
            "Range Min [m]": range_limits[0],
            "Range Max [m]": range_limits[1],
            "Doppler Min [Hz]": doppler_limits[0],
            "Doppler Max [Hz]": doppler_limits[1],
            "Number of TX Antennas": num_tx,  # Add number of TX antennas
            "Number of RX Antennas": num_rx,  # Add number of RX antennas
            "Length of Virtual Array": virtual_array_length,
            "Cascading": cascading,  # Add cascading configuration
            "Active Frame Time [ms]": active_frame_time,
            "Number of Range FFT Bins": int(numb_range_fft_bins),
            "Number of Doppler FFT Bins": int(numb_doppler_fft_bins),
            # "Number of Angle Bins": int(numb_angle_fft_bins),
            "Radar Cube Size [KB]": radar_cube_size_KB,
            "Waveform Multiplexing": waveform_multiplexing,
            "GUI Monitor": gui_monitor_values,
        })

    def parse_waveform_multiplexing(self, value):
        # print("value = ", value)
        if '7' in value or '5' in value:
            selected_waveform = 'Phased-Array'
        else:
            selected_waveform = 'TDM-MIMO'
        return selected_waveform

    def set_tables_information(self, radar_params, selected_radar):
        # Chirp Configuration Table Information
        chirp_cfg_info = {
            "Antenna Config": 0,  # Placeholder
            "Waveform Multiplexing": radar_params["Waveform Multiplexing"],  # Placeholder
            "Frequency Start [GHz]": radar_params["Frequency Start [GHz]"],
            "Frequency Slope [MHz/us]": radar_params["Frequency Slope [MHz/us]"],
            "Number of Samples per Chirp": radar_params["Number of Samples per Chirp"],
            "Number of Chirps in Loop": radar_params["Number of Chirps in Loop"],
            "Sample Rate [KHz]": radar_params["Sample Rate [KHz]"],
            # "Beat Frequency [MHz]": radar_params["Beat Frequency [MHz]"],
            "Idle Time [us]": radar_params["Idle Time [us]"],
            "ADC Valid Start Time [us]": radar_params["ADC Valid Start Time [us]"],
            # "Chirp Time [us]": radar_params["Chirp Time [us]"],
            "Ramp End Time [us]": radar_params["Ramp End Time [us]"],
            "Measurement Rate [Hz]": 1 / (radar_params["Frame Periodicity [ms]"] * 1e-3),
            "Range Threshold (CFAR) [dB]": radar_params["Range Threshold (CFAR) [dB]"],  # Placeholder
            "Doppler Threshold (CFAR) [dB]": radar_params["Doppler Threshold (CFAR) [dB]"],  # Placeholder
            "Clutter Removal": radar_params["Clutter Removal"],  # Placeholder

        }
        self.update_table(self.chirp_cfg_table, chirp_cfg_info, selected_radar)

        # Radar Configuration Table Information
        radar_cfg_info = {
            "Maximum Range [m]": radar_params["Maximum Range [m]"],
            "Unambiguous Range [m]": radar_params["Unambiguous Range [m]"],
            "Range Resolution [m]": radar_params["Range Resolution [m]"],
            "Bandwidth [MHz]": radar_params["Bandwidth [MHz]"],
            "Unambiguous Velocity [km/h]": radar_params["Unambiguous Velocity [km/h]"],
            "Velocity Resolution [km/h]": radar_params["Velocity Resolution [km/h]"],
            "Length of Virtual Array" : radar_params["Length of Virtual Array"],
            "Number of Chirps in Frame": radar_params["Number of Chirps in Frame"],
            "Number of Loops": radar_params["Number of Loops"] + 1,
            "Number of Bursts in Frame": radar_params["Number of Bursts in Frame"],
            "Radar Cube Size [KB]": radar_params["Radar Cube Size [KB]"],
        }
        self.update_table(self.radar_cfg_table, radar_cfg_info, selected_radar)

        fov_info = {
            "Azimuth Min [deg.]": radar_params["Azimuth Min [deg.]"],
            "Azimuth Max [deg.]": radar_params["Azimuth Max [deg.]"],
            "Elevation Min [deg.]": radar_params["Elevation Min [deg.]"],
            "Elevation Max [deg.]": radar_params["Elevation Max [deg.]"],
            "Range Min [m]": radar_params["Range Min [m]"],
            "Range Max [m]": radar_params["Range Max [m]"],
            "Doppler Min [Hz]": radar_params["Doppler Min [Hz]"],
            "Doppler Max [Hz]": radar_params["Doppler Max [Hz]"],
        }
        self.update_table(self.field_of_view_table, fov_info, selected_radar)

        display_info = {
            "Scatter Plot": bool(int(radar_params["GUI Monitor"][1])),
            "Range Profile": bool(int(radar_params["GUI Monitor"][2])),
            "Noise Profile": bool(int(radar_params["GUI Monitor"][3])),
            "Range Azimuth Heat Map": bool(int(radar_params["GUI Monitor"][4])),
            "Range Doppler Heat Map": bool(int(radar_params["GUI Monitor"][5])),
            "Statistics": bool(int(radar_params["GUI Monitor"][6])),
        }
        self.update_table(self.display_table, display_info, selected_radar)

        settings_info = {
            "Range-Doppler Heatmap Minimum Value": int(radar_params["Range-Doppler Heatmap Minimum Value"]),
            "Range-Doppler Heatmap Maximum Value": int(radar_params["Range-Doppler Heatmap Maximum Value"]),
            "Range-Doppler Heatmap Grid Size": int(radar_params["Range-Doppler Heatmap Grid Size"]),
            "Azimuth Static Heatmap Minimum Value": int(radar_params["Azimuth Static Heatmap Minimum Value"]),
            "Azimuth Static Heatmap Maximum Value": int(radar_params["Azimuth Static Heatmap Maximum Value"]),
            "Azimuth Static Heatmap Grid Size": int(radar_params["Azimuth Static Heatmap Grid Size"]),
        }
        self.update_table(self.settings_table, settings_info, selected_radar)

    def update_table(self, table_id, table_info, selected_radar):
        # Clear existing data from the table
        table_id.setRowCount(0)
        if not table_info:
            print("ERROR: table_info is None")
            return

        # Keep track of already processed parameters to avoid duplicates
        processed_params = set()

        # editable_params = {"Frequency Slope [MHz/us]", "Number of Samples per Chirp", "Number of Chirps in Loop"}

        # Update table dynamically
        for param, value in table_info.items():


            # Handle paired parameters (Min/Max logic)
            if "Min " in param and param not in processed_params:
                limits_param = param.replace("Min", "Limits")
                max_param = param.replace("Min", "Max")
                min_value = value
                max_value = table_info.get(max_param, None)

                # Check if Max exists and hasn't been processed
                if max_value is not None:
                    row_idx = table_id.rowCount()
                    table_id.insertRow(row_idx)
                    table_id.setItem(row_idx, 0, QTableWidgetItem(limits_param))

                    # Use a helper function to create the widget for Min/Max inputs
                    # widget = self.create_limit_widgets(param, min_value, max_value)
                    widget = self.create_limit_widgets(param, min_value, max_value, callback=self.on_limit_edited)

                    table_id.setCellWidget(row_idx, 1, widget)

                    # Set minimum row height for better visibility
                    table_id.setRowHeight(row_idx, 150)

                    # Mark both Min and Max as processed
                    processed_params.add(param)
                    processed_params.add(max_param)
                continue  # Skip adding individual Min/Max rows

            # Skip Max parameters if they have already been handled
            if "Max" in param and param in processed_params:
                continue

            # Add a new row for other parameters
            row_idx = table_id.rowCount()
            table_id.insertRow(row_idx)
            table_id.setItem(row_idx, 0, QTableWidgetItem(param))

            # Handle combo boxes for specific parameters
            if param == "Antenna Config":
                # Map num_tx and num_rx to the correct configuration
                if selected_radar == "IWR6843ISK" or selected_radar == "IWR1843BOOST":
                    antenna_config = f"{self.radar_params['Number of RX Antennas']}Rx, {self.radar_params['Number of TX Antennas']}Tx"
                    antenna_options = ["4Rx, 3Tx", "4Rx, 2Tx", "4Rx, 1Tx", "2Rx, 1Tx", "1Rx, 1Tx"]
                elif selected_radar == "AWR1642BOOST":
                    antenna_config = f"{self.radar_params['Number of RX Antennas']}Rx, {self.radar_params['Number of TX Antennas']}Tx"
                    antenna_options = ["4Rx, 2Tx", "4Rx, 1Tx", "2Rx, 1Tx", "1Rx, 1Tx"]
                else:
                    antenna_config = f"{self.radar_params['Number of RX Antennas']}Rx, {self.radar_params['Number of TX Antennas']}Tx"
                    antenna_options = ["4Rx, 4Tx", "4Rx, 3Tx", "4Rx, 2Tx", "4Rx, 1Tx", "2Rx, 1Tx", "1Rx, 1Tx"]

                # Add the combo box and select the correct item
                self.add_combo_box(table_id, row_idx, antenna_options, selected_value=antenna_config, callback=self.on_antenna_confg)

            elif param == "Waveform Multiplexing":
                selected_waveform = self.radar_params["Waveform Multiplexing"]
                self.add_combo_box(table_id, row_idx, ["TDM-MIMO", "Phased-Array"],selected_value=selected_waveform, callback=self.on_waveform_multiplexing)
            elif param == "Clutter Removal":
                self.add_check_box(table_id, row_idx, value, callback=self.on_clutter_removal_toggled)
                self.radar_params["Clutter Removal"] = bool(value)

            elif param in ["Scatter Plot", "Range Profile", "Noise Profile", "Range Azimuth Heat Map",
                           "Range Doppler Heat Map", "Statistics"]:
                self.add_check_box(table_id, row_idx, value, callback=self.on_plot_selection_toggled, param=param)

            else:
                # Format the value to remove decimals if it's a whole number
                if isinstance(value, (float, int)) and float(value).is_integer():
                    value = int(value)
                table_id.setItem(row_idx, 1, QTableWidgetItem(str(value)))

    def on_waveform_multiplexing(self, selected_value):
        print(f"Waveform Multiplexing Config changed to: {selected_value}")
        self.settings_table.blockSignals(True)
        self.chirp_cfg_table.blockSignals(True)
        calculated_params = {}
        calculated_params["Waveform Multiplexing"] = selected_value
        self.handle_cfg_update(calculated_params, cfgType='chirpCfg')
        # Update the radar configuration and UI
        self.parse_commands_information("command_table", self.radar_params)
        selected_radar = self.select_radar_combo_box.currentText()
        self.set_tables_information(self.radar_params, selected_radar)
        self.settings_table.blockSignals(False)
        self.chirp_cfg_table.blockSignals(False)

    def on_antenna_confg(self, selected_value):
        print(f"Antenna Config changed to: {selected_value}")

        # Parse the selected_value to determine the number of Rx and Tx antennas
        try:
            # Example format: "4Rx, 3Tx"
            parts = selected_value.replace("Rx", "").replace("Tx", "").split(",")
            num_rx = int(parts[0].strip())
            num_tx = int(parts[1].strip())

        except (ValueError, IndexError) as e:
            print(f"ERROR: Invalid antenna configuration format: {selected_value} ({e})")
            return

        # Update radar_params
        self.radar_params['Number of RX Antennas'] = num_rx
        self.radar_params['Number of TX Antennas'] = num_tx
        self.radar_params['Cascading'] = 0  # Default to 0, modify if cascading logic is required
        self.radar_params["Number of Loops"] = num_tx - 1
        # Trigger the update for the 'channelCfg' command
        self.on_apply_changes_to_cfg_file_push_button(update_commands=['channelCfg', 'frameCfg'])

        self.settings_table.blockSignals(True)
        self.chirp_cfg_table.blockSignals(True)
        # Update the radar configuration and UI
        self.parse_commands_information("command_table", self.radar_params)
        selected_radar = self.select_radar_combo_box.currentText()
        self.set_tables_information(self.radar_params, selected_radar)
        self.settings_table.blockSignals(False)
        self.chirp_cfg_table.blockSignals(False)

    def add_combo_box(self, table_id, row_idx, options, selected_value=None, callback=None):
        combo_box = QComboBox()
        combo_box.addItems(options)

        # Set the selected value based on num_tx and num_rx
        if selected_value:
            index = combo_box.findText(selected_value)
            if index != -1:
                combo_box.setCurrentIndex(index)
        if callback:
            combo_box.currentTextChanged.connect(callback)
        # Add the combo box to the table
        table_id.setCellWidget(row_idx, 1, combo_box)

    def on_limit_edited(self, param, limit_type, new_value):
        # Process the edited value and send a command
        print(f"Parameter: {param}, {limit_type}: {new_value}")

        # Ensure the new value is a valid float
        try:
            new_value = float(new_value)
        except ValueError:
            print(f"Invalid value for {param} {limit_type}: {new_value}")
            return

        # Flags for which configuration to update
        aoaFovCfg = 0
        cfarFovCfg_range = 0
        cfarFovCfg_doppler = 0

        # Update radar parameters based on the edited limit
        if limit_type == "min":
            if "Azimuth" in param:
                aoaFovCfg = 1
                self.radar_params["Azimuth Min [deg.]"] = new_value
            elif "Elevation" in param:
                aoaFovCfg = 1
                self.radar_params["Elevation Min [deg.]"] = new_value
            elif "Range" in param:
                cfarFovCfg_range = 1
                self.radar_params["Range Min [m]"] = new_value
            elif "Doppler" in param:
                cfarFovCfg_doppler = 1
                self.radar_params["Doppler Min [Hz]"] = new_value
        elif limit_type == "max":
            if "Azimuth" in param:
                aoaFovCfg = 1
                self.radar_params["Azimuth Max [deg.]"] = new_value
            elif "Elevation" in param:
                aoaFovCfg = 1
                self.radar_params["Elevation Max [deg.]"] = new_value
            elif "Range" in param:
                cfarFovCfg_range = 1
                self.radar_params["Range Max [m]"] = new_value
            elif "Doppler" in param:
                cfarFovCfg_doppler = 1
                self.radar_params["Doppler Max [Hz]"] = new_value

        # Send aoaFovCfg command if required
        if aoaFovCfg == 1:
            command = (f"aoaFovCfg {-1} "
                       f"{self.radar_params['Azimuth Min [deg.]']} "
                       f"{self.radar_params['Azimuth Max [deg.]']} "
                       f"{self.radar_params['Elevation Min [deg.]']} "
                       f"{self.radar_params['Elevation Max [deg.]']}")
            self.send_command(command)
            self.on_apply_changes_to_cfg_file_push_button(update_commands=['aoaFovCfg'])

        # Send cfarFovCfg_range command if required
        if cfarFovCfg_range == 1:
            command = (f"cfarFovCfg {-1} {0} "
                       f"{self.radar_params['Range Min [m]']} "
                       f"{self.radar_params['Range Max [m]']} ")
            self.send_command(command)
            self.on_apply_changes_to_cfg_file_push_button(update_commands=['cfarFovCfg'])

        # Send cfarFovCfg_doppler command if required
        if cfarFovCfg_doppler == 1:
            command = (f"cfarFovCfg {-1} {1} "
                       f"{self.radar_params['Doppler Min [Hz]']} "
                       f"{self.radar_params['Doppler Max [Hz]']} ")
            self.send_command(command)
            self.on_apply_changes_to_cfg_file_push_button(update_commands=['cfarFovCfg'])

    def send_command(self, command):
        """
        Send the specified command to the device via the command port.

        Parameters:
            command (str): The command to be sent.
        """
        # Check if the command port is connected
        if not self.command_port_connected:
            print("Error: Command port is not connected")
            self.command_textbox.appendPlainText("Error: Command port is not connected")
            return

        # Encode the command to bytes and send it via the command port
        command_bytes = command.encode('latin1') + b'\n'

        # Send the command over the command port
        self.command_port.write(command_bytes)
        time.sleep(0.1)  # Wait for a short time to allow the command to be processed

        # Read the response from the device
        byteCount = self.command_port.in_waiting
        if byteCount > 0:
            response_bytes = self.command_port.read(byteCount)
            response_str = response_bytes.decode('latin1').strip().replace("\n", "\n\t")
            print(response_str)
            self.command_textbox.appendPlainText(f"Response: {response_str}")

        # Set the QLineEdits in the corresponding cells

    def create_limit_widgets(self, param, interval1, interval2, callback=None):
        # Format the values to 2 decimal places
        interval1_str = f"{interval1:.2f}"
        interval2_str = f"{interval2:.2f}"

        # Create labels for min and max
        min_label = QLabel("min:")
        max_label = QLabel("max:")

        # Create QLineEdit widgets for the min and max values
        edit_box_1 = QLineEdit(interval1_str)
        edit_box_2 = QLineEdit(interval2_str)

        # If a callback is provided, connect the editingFinished signal to it
        if callback:
            edit_box_1.returnPressed.connect(lambda: callback(param, "min", edit_box_1.text()))
            edit_box_2.returnPressed.connect(lambda: callback(param, "max", edit_box_2.text()))

        # Create layouts for the labels and input fields
        h_layout_1 = QHBoxLayout()
        h_layout_1.addWidget(min_label)
        h_layout_1.addWidget(edit_box_1)

        h_layout_2 = QHBoxLayout()
        h_layout_2.addWidget(max_label)
        h_layout_2.addWidget(edit_box_2)

        # Vertical layout to hold the horizontal layouts
        v_layout_1 = QVBoxLayout()
        v_layout_1.addLayout(h_layout_1)
        v_layout_1.addLayout(h_layout_2)

        # Create a QWidget to hold the layout and return it
        widget_1 = QWidget()
        widget_1.setLayout(v_layout_1)

        return widget_1

    @staticmethod
    def add_check_box(table_id, row, value, param=None, callback=None):
        """
        Adds a checkbox to the table at the specified row and column.

        Args:
            table_id: The table widget to add the checkbox to.
            row: The row index where the checkbox will be placed.
            value: The initial checked state of the checkbox (True or False).
            param: The specific parameter (e.g., "Scatter Plot").
            callback: A function to call when the checkbox state changes.
        """
        # Create the checkbox
        check_box = QCheckBox()
        check_box.setChecked(value)  # Default unchecked

        # If a callback is provided, connect the checkbox signal to the callback
        if callback:
            check_box.stateChanged.connect(lambda state: callback(state, row, param))

        # Optionally use the param information if needed
        if param:
            # Embed param information, you can store it or use it as needed
            check_box.setProperty('param', param)

        table_id.setCellWidget(row, 1, check_box)

    def set_evm_info(self, selected_radar):
        if not hasattr(self, selected_radar):
            raise AttributeError(f"{selected_radar} attribute is not defined in MainWindow.")

        if selected_radar in ["IWR6843ISK", "AWR1642BOOST", "IWR1843BOOST"]:
            radar_obj = getattr(self, selected_radar, None)
            evm_info = radar_obj.copy()
        else:
            print(f"Unsupported radar model: {selected_radar}")
            evm_info = {}
        return evm_info

    def set_best_default_config(self,selected_radar, selected_desirable_config):
        if selected_desirable_config == "Best Range Resolution":
            radar_desirable_config = selected_radar + "_best_range_resolution"
            radar_config_obj = getattr(self, radar_desirable_config, None)
            self.default_best_configuration(radar_config_obj)
        elif selected_desirable_config == "Best Velocity Resolution":
            radar_desirable_config = selected_radar + "_best_velocity_resolution"
            radar_config_obj = getattr(self, radar_desirable_config, None)
            self.default_best_configuration(radar_config_obj)
        else: #Best Range
            radar_desirable_config = selected_radar + "_best_range"
            radar_config_obj = getattr(self, radar_desirable_config, None)
            self.default_best_configuration(radar_config_obj)

    def update_specified_table(self, table_id, content):
        """Updates a specified table with given content."""
        table = getattr(self, table_id)  # Get the table widget by table_id

        table.setRowCount(0)  # Clear the table before updating
        row = 0

        # Check if content is a dictionary (key-value pairs) or list of tuples
        if isinstance(content, dict):
            # If it's a dictionary, insert key-value pairs into the table
            for param, value in content.items():
                table.insertRow(row)
                table.setItem(row, 0, QTableWidgetItem(param))
                table.setItem(row, 1, QTableWidgetItem(str(value)))
                row += 1
        elif isinstance(content, list):
            # If it's a list (assumed to be a list of tuples)
            for item in content:
                if isinstance(item, tuple) and len(item) == 2:
                    table.insertRow(row)
                    table.setItem(row, 0, QTableWidgetItem(str(item[0])))  # Insert first part of tuple
                    table.setItem(row, 1, QTableWidgetItem(str(item[1])))  # Insert second part of tuple
                    row += 1
                elif isinstance(item, dict) and len(item) == 4:
                    table.insertRow(row)
                    table.setItem(row, 0, QTableWidgetItem(str(row)))
                    table.setItem(row, 1, QTableWidgetItem(f"{item['X']:.2f}"))
                    table.setItem(row, 2, QTableWidgetItem(f"{item['Y']:.2f}"))
                    table.setItem(row, 3, QTableWidgetItem(f"{item['Z']:.2f}"))
                    table.setItem(row, 4, QTableWidgetItem(f"{item['Doppler']:.2f}"))
                    row += 1
                elif isinstance(item, dict) and len(item) == 2:
                    table.insertRow(row)
                    table.setItem(row, 0, QTableWidgetItem(str(row)))
                    table.setItem(row, 1, QTableWidgetItem(f"{item['snr']:.2f}"))
                    table.setItem(row, 2, QTableWidgetItem(f"{item['noise']:.2f}"))
                    row += 1
        else:
            print("Unsupported content format. Provide a dictionary or list of tuples.")

    def closeEvent(self, event):
        # Disconnect from the ports when the application is closed
        event.accept()
        self.disconnect_ports()