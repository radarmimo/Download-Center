# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# % Copyright (c) 2024, <Mohammad Alaee>, university of luxembourg
# % website: https://radarmimo.com/
# % All rights reserved.
# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# % Redistribution and use in source and binary forms, with or without
# % modification, are permitted provided that the following conditions are met:
# % 1. Redistributions of source code must retain the above copyright
# %    notice, this list of conditions and the following disclaimer.
# % 2. Redistributions in binary form must reproduce the above copyright
# %    notice, this list of conditions and the following disclaimer in the
# %    documentation and/or other materials provided with the distribution.
# % 3. All advertising materials mentioning features or use of this software
# %    must display the following acknowledgement:
# %    "This product includes software developed by <Mohammad Alaee>,
# %    https://radarmimo.com/"
# %
# % THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
# % EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# % WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# % DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
# % DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# % (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# % LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# % ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# % (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# % SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# % Website: https://radarmimo.com/
# % Email: info@radarmimo.com, mohammad.alaee@uni.lu
# % Code written by : Mohammad Alaee
# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

import pprint
import numpy as np
import threading
import queue
import scipy.signal as signal
from scipy.signal import lfilter, firwin, find_peaks, filtfilt
from scipy.ndimage import uniform_filter1d
import pyqtgraph as pg
from PyQt5.QtCore import QTimer
from pyqtgraph.Qt import QtCore
import sys
from PyQt5.QtWidgets import QApplication, QGridLayout, \
    QLabel, QVBoxLayout, QWidget, QFrame
import time
from neulog import neulog
import statsmodels.api as sm
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
from ifxradarsdk import get_version
from ifxradarsdk.ltr11 import DeviceLtr11
from ifxradarsdk.ltr11.types import Ltr11Config
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ENABLE_NEULOG = True
if ENABLE_NEULOG:
    neulog_sensors = neulog.Device(port="COM18")
    res_connect = neulog_sensors.connect()
    if not neulog_sensors.connect():
        print("Neulog sensors connection failed")
        ENABLE_NEULOG = False
    else:
        print("connected to neulog sensors", neulog_sensors)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
prt_index = 0  # 0 = 4000 Hz,  1 = 2000 Hz, 2 = 1000 Hz, 3 = 500 Hz
if prt_index == 0:
    sample_rate = 4000
elif prt_index == 1:
    sample_rate = 2000
elif prt_index == 2:
    sample_rate = 1000
else:
    sample_rate = 500
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
processing_window_time = 20  # second
buffer_time = 5 * processing_window_time  # second
estimation_time = 5  # second
time_offset_synch_plots = 1.0  # second
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
figure_update_time = 25  # m second
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ENABLE_PHASE_UNWRAP_PLOT = True
ENABLE_VITALSIGNS_SPECTRUM = True
ENABLE_ESTIMATION_PLOT = True
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
num_rx_antennas = 1
rate_index = 200
num_of_samples = int(3 * rate_index)
samples_time = num_of_samples/sample_rate
vital_signs_sample_rate = int(sample_rate/rate_index)    # Hz
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
raw_data_size = int(processing_window_time * sample_rate)
buffer_data_size = int(buffer_time * vital_signs_sample_rate)
processing_data_size = int(processing_window_time * vital_signs_sample_rate)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fft_size_vital_signs = processing_data_size*4
estimation_rate = vital_signs_sample_rate  # Hz
estimation_size_vital_signs = buffer_time*estimation_rate
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
estimation_index_breathing = buffer_data_size - estimation_time * estimation_rate
estimation_index_heart = buffer_data_size - estimation_time * estimation_rate
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# filter initial coefficients
# Calculate normalized cutoff frequencies for breathing
low_breathing = 0.15
high_breathing = 0.6
# Calculate normalized cutoff frequencies for heat rate
low_heart = 0.85
high_heart = 4
nyquist_freq = 0.5 * vital_signs_sample_rate
filter_order = vital_signs_sample_rate + 1
breathing_b = firwin(filter_order, [low_breathing/nyquist_freq, high_breathing/nyquist_freq],pass_zero=False)
heart_b = firwin(filter_order, [low_heart/nyquist_freq, high_heart/nyquist_freq],pass_zero=False)
index_start_breathing = int(low_breathing/vital_signs_sample_rate * fft_size_vital_signs)
index_end_breathing = int(high_breathing/vital_signs_sample_rate * fft_size_vital_signs)
index_start_heart = int(low_heart/vital_signs_sample_rate * fft_size_vital_signs)
index_end_heart = int(high_heart/vital_signs_sample_rate * fft_size_vital_signs)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# peak detection
peak_finding_distance = 0.01
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# plots
x_axis_vital_signs_spectrum = np.linspace(-vital_signs_sample_rate/2, vital_signs_sample_rate/2, fft_size_vital_signs)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
frame_counter = 0
data_queue = queue.Queue()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Initial time
# Initial time
start_time = time.time()
neulog_start_time = start_time
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# neulog
neulog_respiration_sample_rate = 10     # Hz
neulog_estimation_size_respiration = buffer_time*neulog_respiration_sample_rate
neulog_processing_size_respiration = processing_window_time*neulog_respiration_sample_rate
neulog_fft_size_respiration = neulog_processing_size_respiration*4
neulog_first_index_respiration = int(low_breathing/neulog_respiration_sample_rate * neulog_fft_size_respiration)
neulog_last_index_respiration = int(high_breathing/neulog_respiration_sample_rate * neulog_fft_size_respiration)
neulog_x_axis_respiration_spectrum = np.linspace(-neulog_respiration_sample_rate/2, neulog_respiration_sample_rate/2, neulog_fft_size_respiration)

neulog_pulse_sample_rate = 10     # Hz
neulog_estimation_size_pulse = buffer_time*neulog_pulse_sample_rate
neulog_processing_size_pulse = processing_window_time*neulog_pulse_sample_rate
neulog_fft_size_pulse = neulog_processing_size_pulse*4
neulog_first_index_pulse = int(low_heart/neulog_pulse_sample_rate * neulog_fft_size_pulse)
neulog_last_index_pulse = int(high_heart/neulog_pulse_sample_rate * neulog_fft_size_pulse)
neulog_x_axis_pulse_spectrum = np.linspace(-neulog_pulse_sample_rate/2, neulog_pulse_sample_rate/2, neulog_fft_size_pulse)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
epsilon_value = 0.00000001
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# data queue
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def read_data(device):
    global frame_counter
    while True:
        frame_contents = device.get_next_frame()
        for frame in frame_contents:
            data_queue.put(frame)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def read_neulog(device):
    global neulog_start_time, neulog_respiration_values, neulog_time_stamp, \
        neulog_pulse_values
    time_test = 0
    sample_counter = 0
    while True:
        time.sleep(1 / (2 * neulog_pulse_sample_rate))
        # if window.data_port_connected:
        respiration_value = float(device.getSensorsData('Respiration', 1))
        neulog_respiration_values = np.roll(neulog_respiration_values, -1)
        neulog_respiration_values[-1] = respiration_value

        current_respiration_time = time.time()
        time_passed_neulog = current_respiration_time - neulog_start_time
        neulog_time_stamp = np.roll(neulog_time_stamp, -1)
        neulog_time_stamp[-1] = neulog_time_stamp[-2] + time_passed_neulog
        neulog_start_time = current_respiration_time
        time_test = time_passed_neulog + time_test
        sample_counter += 1
        pulse_value = float(device.getSensorsData('Pulse', 1))
        neulog_pulse_values = np.roll(neulog_pulse_values, -1)
        neulog_pulse_values[-1] = pulse_value
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# UI class
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class HeartBreathingWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Heart, Breathing, Respiration, and Pulse Rate")

        self.layout = QVBoxLayout()
        # Labels and values
        grid_layout = QGridLayout()

        # Horizontal line
        line0 = QFrame()
        line0.setFrameShape(QFrame.HLine)
        line0.setFrameShadow(QFrame.Sunken)
        self.layout.addWidget(line0)
        # # Title
        self.radar_title_label = QLabel("Radar")
        self.radar_title_label.setStyleSheet("font-weight: bold; color: black; font-size: 28px;")
        self.neulog_title_label = QLabel("  NeuLog")
        self.neulog_title_label.setStyleSheet("font-weight: bold; color: orange; font-size: 28px;")

        grid_layout.addWidget(self.radar_title_label, 0, 0)
        grid_layout.addWidget(self.neulog_title_label, 0, 2)

        # Horizontal line
        line1 = QFrame()
        line1.setFrameShape(QFrame.HLine)
        line1.setFrameShadow(QFrame.Sunken)
        grid_layout.addWidget(line1, 1, 0, 1, 4)

        # Vertical line
        line1v = QFrame()
        line1v.setFrameShape(QFrame.VLine)
        line1v.setFrameShadow(QFrame.Sunken)
        grid_layout.addWidget(line1v, 0, 2, 6, 2)

        # Heart Rate components
        self.heart_rate_label = QLabel("Heart Rate [b.p.m.]")
        self.heart_rate_label.setStyleSheet("font-weight: bold; color: black; font-size: 20px;")
        self.heart_rate_value = QLabel("N/A")
        self.heart_rate_value.setStyleSheet("font-weight: bold; color: blue; font-size: 20px;")

        grid_layout.addWidget(self.heart_rate_label, 2, 0)
        grid_layout.addWidget(self.heart_rate_value, 2, 1)

        # Pulse Rate components
        self.pulse_rate_label = QLabel("  Pulse Rate [b.p.m.]")
        self.pulse_rate_label.setStyleSheet("font-weight: bold; color: orange; font-size: 20px;")
        self.pulse_rate_value = QLabel("N/A")
        self.pulse_rate_value.setStyleSheet("font-weight: bold; color: orange; font-size: 20px;")

        grid_layout.addWidget(self.pulse_rate_label, 2, 2)
        grid_layout.addWidget(self.pulse_rate_value, 2, 3)

        # Horizontal line
        line2 = QFrame()
        line2.setFrameShape(QFrame.HLine)
        line2.setFrameShadow(QFrame.Sunken)
        grid_layout.addWidget(line2, 3, 0, 1, 4)

        # Breathing Rate components
        self.breathing_rate_label = QLabel("Breathing Rate [b.p.m.]")
        self.breathing_rate_label.setStyleSheet("font-weight: bold; color: black; font-size: 20px;")
        self.breathing_rate_value = QLabel("N/A")
        self.breathing_rate_value.setStyleSheet("font-weight: bold; color: blue; font-size: 20px;")

        grid_layout.addWidget(self.breathing_rate_label, 4, 0)
        grid_layout.addWidget(self.breathing_rate_value, 4, 1)

        # Respiration Rate components
        self.respiration_rate_label = QLabel("  Respiration Rate [b.p.m.]")
        self.respiration_rate_label.setStyleSheet("font-weight: bold; color: orange; font-size: 20px;")
        self.respiration_rate_value = QLabel("N/A")
        self.respiration_rate_value.setStyleSheet("font-weight: bold; color: orange; font-size: 20px;")

        grid_layout.addWidget(self.respiration_rate_label, 4, 2)
        grid_layout.addWidget(self.respiration_rate_value, 4, 3)

        # Horizontal line
        line3 = QFrame()
        line3.setFrameShape(QFrame.HLine)
        line3.setFrameShadow(QFrame.Sunken)
        grid_layout.addWidget(line3, 5, 0, 1, 4)

        self.layout.addLayout(grid_layout)
        self.setLayout(self.layout)

    def set_heart_rate(self, heart_rate):
        self.heart_rate_value.setText(str(heart_rate))

    def set_pulse_rate(self, pulse_rate):
        self.pulse_rate_value.setText(str(pulse_rate))

    def set_breathing_rate(self, breathing_rate):
        self.breathing_rate_value.setText(str(breathing_rate))

    def set_respiration_rate(self, respiration_rate):
        self.respiration_rate_value.setText(str(respiration_rate))

def update_plots():
    global breathing_rate_estimation_value, heart_rate_estimation_value, \
            breathing_rate_estimation_time_stamp, heart_rate_estimation_time_stamp
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # range profile plot
    if ENABLE_PHASE_UNWRAP_PLOT:
        phase_unwrap_plots[0][0].setData(radar_time_stamp, np.real(buffer_data_dds))
        phase_unwrap_plots[1][0].setData(radar_time_stamp, np.imag(buffer_data_dds))
        phase_unwrap_plots[2][0].setData(radar_time_stamp, I_Q_envelop)
        phase_unwrap_plots[3][0].setData(radar_time_stamp, wrapped_phase_plot*180/np.pi)
        phase_unwrap_plots[4][0].setData(radar_time_stamp, unwrapped_phase_plot*180/np.pi)
        phase_unwrap_plots[5][0].setData(radar_time_stamp, filtered_breathing_plot * 180 / np.pi)
        phase_unwrap_plots[6][0].setData(radar_time_stamp, filtered_heart_plot * 180 / np.pi)
        if ENABLE_NEULOG:
            phase_unwrap_plots[7][0].setData(neulog_time_stamp,
                                              neulog_respiration_values - np.mean(neulog_respiration_values))
            phase_unwrap_plots[8][0].setData(neulog_time_stamp,
                                              neulog_pulse_values - np.mean(neulog_pulse_values))
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # breathing fft plot
    if ENABLE_VITALSIGNS_SPECTRUM:
        vital_signs_plots[0][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(buffer_dds_fft))
        vital_signs_plots[1][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(phase_unwrap_fft))
        vital_signs_plots[2][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(breathing_fft))
        vital_signs_plots[3][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(heart_fft))
        if breathing_rate_estimation_index[estimation_index_breathing] > 0:
            xb = x_axis_vital_signs_spectrum[int(fft_size_vital_signs/2+np.mean(breathing_rate_estimation_index[estimation_index_breathing:]))]
            yb = breathing_fft[int(np.mean(breathing_rate_estimation_index[estimation_index_breathing:]))]
            vital_signs_plots[4][0].setData([xb], [yb])
            heart_breathing_window.set_breathing_rate(round(xb * 60) )
        if heart_rate_estimation_index[estimation_index_heart] > 0:
            xh = x_axis_vital_signs_spectrum[int(fft_size_vital_signs/2+np.mean(heart_rate_estimation_index[estimation_index_heart:]))]
            yh = heart_fft[int(np.mean(heart_rate_estimation_index[estimation_index_heart:]))]
            vital_signs_plots[5][0].setData([xh], [yh])
            heart_breathing_window.set_heart_rate(round(xh*60) )
        if ENABLE_NEULOG:
            vital_signs_plots[6][0].setData(neulog_x_axis_respiration_spectrum, np.fft.fftshift(neulog_respiration_fft))
            vital_signs_plots[7][0].setData(neulog_x_axis_pulse_spectrum, np.fft.fftshift(neulog_pulse_fft))
            if neulog_respiration_peak_index[-1] > 0:
                xr = neulog_x_axis_respiration_spectrum[int(neulog_respiration_peak_index[-1]+neulog_fft_size_respiration/2)]
                yr = neulog_respiration_fft[int(neulog_respiration_peak_index[-1])]
                vital_signs_plots[8][0].setData([xr], [yr])
                heart_breathing_window.set_respiration_rate(round(xr * 60))
            if neulog_pulse_peak_index[-1] > 0:
                xp = neulog_x_axis_pulse_spectrum[int(neulog_pulse_peak_index[-1]+neulog_fft_size_pulse/2)]
                yp = neulog_pulse_fft[int(neulog_pulse_peak_index[-1])]
                vital_signs_plots[9][0].setData([xp], [yp])
                heart_breathing_window.set_pulse_rate(round(xp * 60))
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ENABLE_ESTIMATION_PLOT:
        global breathing_rate_estimation_value, heart_rate_estimation_value
        if breathing_rate_estimation_index[estimation_index_breathing] > 0:
            breathing_rate_estimation_value = np.roll(breathing_rate_estimation_value, -1)
            xb = x_axis_vital_signs_spectrum[
                round(fft_size_vital_signs / 2 + np.mean(breathing_rate_estimation_index[estimation_index_breathing:]))]*60
            breathing_rate_estimation_value[-1] = round(xb)
            estimation_plots[0][0].setData(radar_time_stamp, breathing_rate_estimation_value)

        if heart_rate_estimation_index[estimation_index_heart] > 0:
            heart_rate_estimation_value = np.roll(heart_rate_estimation_value, -1)
            xh = x_axis_vital_signs_spectrum[
                round(fft_size_vital_signs / 2 + np.mean(heart_rate_estimation_index[estimation_index_heart:]))] * 60
            heart_rate_estimation_value[-1] = round(xh)
            estimation_plots[1][0].setData(radar_time_stamp, heart_rate_estimation_value)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if ENABLE_NEULOG:
            indices_values_r = [neulog_x_axis_respiration_spectrum[int(index + neulog_fft_size_respiration / 2)] for index in neulog_respiration_peak_index]
            multiplied_values_r = [value * 60 for value in indices_values_r]
            estimation_plots[2][0].setData(neulog_time_stamp , multiplied_values_r)

            indices_values_p = [neulog_x_axis_pulse_spectrum[int(index + neulog_fft_size_pulse / 2)] for index in neulog_pulse_peak_index]
            multiplied_values_p = [value * 60 for value in indices_values_p]
            estimation_plots[3][0].setData(neulog_time_stamp,multiplied_values_p)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# processing class
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class RadarDataProcessor:
    def find_signal_peaks(self,fft_windowed_signal, index_start,index_end, distance):
        signal_region = fft_windowed_signal[index_start: index_end]
        peaks, _ = find_peaks(signal_region,
                              distance=int(max(1,distance*fft_size_vital_signs/vital_signs_sample_rate)))
        # Filter peaks within the boundaries
        # filtered_peaks = peaks[(peaks > 0) & (peaks < len(signal_region) - 1)]
        rate_index = 0
        filtered_peaks = peaks
        if len(filtered_peaks) > 0:
            best_peak_index = np.argmax(signal_region[filtered_peaks])
            rate_index = filtered_peaks[best_peak_index] + index_start
        return rate_index
    def vital_signs_fft(self,data,nFFT,data_length):
        windowed_signal = np.multiply(data, signal.windows.blackmanharris(data_length))
        zp2 = np.zeros(nFFT, dtype=np.complex128)
        zp2[:data_length] = windowed_signal
        fft_result = 1.0 / nFFT * np.abs(np.fft.fft(zp2)) + epsilon_value
        return fft_result
    def process_data(self):
        global raw_data, filtered_raw_data, buffer_data_dds, wrapped_phase_plot, \
            unwrapped_phase_plot, filtered_breathing_plot, filtered_heart_plot, \
            buffer_dds_fft, phase_unwrap_fft, breathing_fft, heart_fft, \
            breathing_rate_estimation_index, heart_rate_estimation_index, I_Q_envelop, \
            neulog_respiration_fft, neulog_respiration_peak_index, \
            neulog_pulse_fft, neulog_pulse_peak_index, breathing_b, heart_b, index_start_heart, index_end_heart, \
            index_end_breathing, index_end_breathing, start_time, radar_time_stamp

        counter = 0
        while True:
            time.sleep(0.001)
            if not data_queue.empty():
                frame = data_queue.get()
                if np.size(frame) == num_of_samples:
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # Apply the filter to the complex data
                    raw_data = np.roll(raw_data, -num_of_samples)
                    raw_data[-num_of_samples:] = frame
                    # x_axis_raw_data = np.roll(x_axis_raw_data, -num_of_samples)
                    # x_axis_raw_data[-num_of_samples:] = x_axis_raw_data[-num_of_samples:] + buffer_time

                    avg = np.mean(raw_data)

                    filtered_raw_data = filtfilt(low_pass_filter_coeffs, 1.0, raw_data - avg)
                    new_data = filtered_raw_data[-num_of_samples::dds_rate]
                    new_data_size = len(new_data)
                    # print("new_data_size = ", new_data_size)
                    #
                    buffer_data_dds = np.roll(buffer_data_dds, -new_data_size)
                    buffer_data_dds[-new_data_size:] = new_data

                    I_Q_envelop = np.roll(I_Q_envelop, -new_data_size)
                    I_Q_envelop[-new_data_size:] = np.abs(new_data)

                    counter += new_data_size
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    current_time = time.time()
                    time_passed = current_time - start_time
                    start_time = current_time

                    radar_time_stamp = np.roll(radar_time_stamp, -counter)
                    radar_time_stamp[-counter:] = radar_time_stamp[-counter-1] + time_passed
                    # if counter > processing_update_interval * vital_signs_sample_rate:
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # phase unwrap
                    wrapped_phase = np.angle(buffer_data_dds[-counter:])
                    wrapped_phase_plot = np.roll(wrapped_phase_plot, -counter)
                    wrapped_phase_plot[-counter:] = wrapped_phase[-counter:]

                    unwrapped_phase_plot = np.roll(unwrapped_phase_plot, -counter)
                    unwrapped_phase_plot[-counter:] = wrapped_phase_plot[-counter:]

                    unwrapped_phase = np.unwrap(unwrapped_phase_plot[-processing_data_size:])
                    unwrapped_phase_plot[-processing_data_size:] = unwrapped_phase
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # filter
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    filtered_breathing = lfilter(breathing_b, 1, unwrapped_phase_plot[-processing_data_size:])
                    cycle1, trend = sm.tsa.filters.hpfilter(filtered_breathing)
                    filtered_breathing = uniform_filter1d(cycle1, size=2 * vital_signs_sample_rate)
                    filtered_breathing_plot = np.roll(filtered_breathing_plot, -counter)
                    filtered_breathing_plot[-counter:] = filtered_breathing[-counter:]

                    cycle2, trend = sm.tsa.filters.hpfilter(unwrapped_phase_plot[-processing_data_size:],
                                                            3 * vital_signs_sample_rate)
                    filtered_heart = lfilter(heart_b, 1, cycle2)
                    filtered_heart_plot = np.roll(filtered_heart_plot, -counter)
                    filtered_heart_plot[-counter:] = filtered_heart[-counter:]
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # Vital Signs FFT
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    buffer_dds_fft = self.vital_signs_fft(I_Q_envelop[-processing_data_size:], fft_size_vital_signs,
                                                              processing_data_size)
                    phase_unwrap_fft = self.vital_signs_fft(unwrapped_phase_plot[-processing_data_size:], fft_size_vital_signs,
                                                            processing_data_size)
                    breathing_fft = self.vital_signs_fft(filtered_breathing_plot[-processing_data_size:], fft_size_vital_signs,
                                                         processing_data_size)
                    heart_fft = self.vital_signs_fft(filtered_heart_plot[-processing_data_size:], fft_size_vital_signs,
                                                     processing_data_size)
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # Breathing and heart rate estimation
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    breathing_rate_estimation_index = np.roll(breathing_rate_estimation_index, -1)
                    breathing_rate_estimation_index[-1] = breathing_rate_estimation_index[-2]
                    rate_index_br = self.find_signal_peaks(breathing_fft, index_start_breathing,
                                                           index_end_breathing, peak_finding_distance)
                    if rate_index_br != 0:
                        breathing_rate_estimation_index[-1] = rate_index_br
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    heart_rate_estimation_index = np.roll(heart_rate_estimation_index, -1)
                    heart_rate_estimation_index[-1] = heart_rate_estimation_index[-2]
                    rate_index_hr = self.find_signal_peaks(heart_fft, index_start_heart,
                                                           index_end_heart, peak_finding_distance)
                    if rate_index_hr != 0:
                        heart_rate_estimation_index[-1] = rate_index_hr
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # neulog
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # respiration
                    neulog_respiration_peak_index = np.roll(neulog_respiration_peak_index, -1)
                    neulog_respiration_peak_index[-1] = neulog_respiration_peak_index[-2]

                    neulog_respiration_fft = self.vital_signs_fft(
                        neulog_respiration_values[-neulog_processing_size_respiration:] - np.mean(
                            neulog_respiration_values[-neulog_processing_size_respiration:]),
                        neulog_fft_size_respiration,
                        neulog_processing_size_respiration) / np.sqrt(neulog_processing_size_respiration)
                    neulog_respiration_current_index = self.find_signal_peaks(neulog_respiration_fft,
                                                                              neulog_first_index_respiration,
                                                                              neulog_last_index_respiration,
                                                                              peak_finding_distance)
                    if neulog_respiration_current_index > 0:
                        neulog_respiration_peak_index[-1] = neulog_respiration_current_index
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # pulse
                    neulog_pulse_peak_index = np.roll(neulog_pulse_peak_index, -1)
                    neulog_pulse_peak_index[-1] = neulog_pulse_peak_index[-2]
                    neulog_pulse_fft = self.vital_signs_fft(
                        neulog_pulse_values[-neulog_processing_size_pulse:] - np.mean(
                            neulog_pulse_values[-neulog_processing_size_pulse:]), neulog_fft_size_pulse,
                        neulog_processing_size_pulse) / np.sqrt(neulog_processing_size_pulse)
                    neulog_pulse_current_index = self.find_signal_peaks(neulog_pulse_fft, neulog_first_index_pulse,
                                                                        neulog_last_index_pulse,
                                                                        peak_finding_distance)
                    if neulog_pulse_current_index > 0:
                        neulog_pulse_peak_index[-1] = neulog_pulse_current_index
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    counter = 0
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_phase_unwrap_plot():
    plot = pg.plot(title='Phase Estimation')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Time [s]')
    plot.setLabel('left', 'Amplitude')
    plot.addLegend()
    plots = [
        ('lightblue', 'DDS Data [I]'),
        ('gold', 'DDS Data [Q]'),
        ('hotpink', 'Envelop'),
        ('y', 'Wrapped Angle'),
        ('m', 'Phase Unwrap'),
        ('g', 'Breathing'),
        ('c', 'Heart'),
        ('moccasin', 'NeuLog Respiration'),
        ('skyblue', 'NeuLog Pulse')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    for j, (color, name) in enumerate(plots):
        line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][0]}
        plot_obj = plot.plot(pen=line_style, name=f'{name}')
        plot_obj.setVisible(False)
        plot_objects[j].append(plot_obj)
    plot_objects[4][0].setVisible(True)
    plot_objects[6][0].setVisible(True)

    return plot, plot_objects
# Usage:
if ENABLE_PHASE_UNWRAP_PLOT:
    phase_unwrap_figure, phase_unwrap_plots = generate_phase_unwrap_plot()
    phase_unwrap_figure.show()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_vitalsigns_spectrum_plot(num_rx_antennas):
    global low_breathing, high_breathing, low_heart, high_heart, breathing_b, heart_b, \
        index_start_breathing, index_end_breathing, index_start_heart, index_end_heart
    plot = pg.plot(title='Vital Signs Spectrum')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Frequency [Hz]')
    plot.setLabel('left', 'Amplitude')
    plot.addLegend()
    plots = [
        ('orange', 'Envelop'),
        ('m', 'Phase Unwrap'),
        ('g', 'Breathing'),
        ('c', 'Heart '),
        ('g', 'Breathing Peak'),
        ('c', 'Heart Peak'),
        ('moccasin', 'NeuLog Respiration'),
        ('skyblue', 'NeuLog Pulse'),
        ('moccasin', 'NeuLog Respiration Peak'),
        ('skyblue', 'NeuLog Pulse Peak'),
    ]
    plot_objects = [[] for _ in range(len(plots))]
    for i in range(num_rx_antennas):
        for j, (color, name) in enumerate(plots):
            if name == 'Breathing Peak':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('g')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=12, name=f'{name} (Rx {i + 1})')
            elif name == 'Heart Peak':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('c')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='d', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=12, name=f'{name} (Rx {i + 1})')
            elif name == 'NeuLog Respiration Peak':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('moccasin')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=12, name=f'{name}')
            elif name == 'NeuLog Pulse Peak':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('skyblue')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='d', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=12, name=f'{name}')
            else:
                line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][i]}
                plot_obj = plot.plot(pen=line_style, name=f'{name} (Rx {i + 1})')
            plot_obj.setVisible(False)
            plot_objects[j].append(plot_obj)
    # plot_objects[0][0].setVisible(True)
    # plot_objects[1][0].setVisible(True)
    # plot_objects[2][0].setVisible(True)
    plot_objects[2][0].setVisible(True)
    plot_objects[3][0].setVisible(True)
    plot_objects[4][0].setVisible(True)
    plot_objects[5][0].setVisible(True)
    # plot_objects[6][0].setVisible(True)
    # plot_objects[7][0].setVisible(True)
    # plot_objects[8][0].setVisible(True)
    # plot_objects[9][0].setVisible(True)

    linear_region_breathing = pg.LinearRegionItem([low_breathing, high_breathing], brush=(255, 255, 0, 20))
    plot.addItem(linear_region_breathing, 'Breathing Linear Region')
    def linear_region_breathing_changed():
        global low_breathing, high_breathing, breathing_b,index_start_breathing,index_end_breathing
        region = linear_region_breathing.getRegion()
        if (region[0] < vital_signs_sample_rate / 4 and region[1] < vital_signs_sample_rate / 2 and
                region[0] > 0 and region[1] > 0):
            low_breathing = region[0]
            high_breathing = region[1]
            breathing_b = firwin(filter_order, [low_breathing / nyquist_freq, high_breathing / nyquist_freq],
                                 pass_zero=False)
            index_start_breathing = int(low_breathing / vital_signs_sample_rate * fft_size_vital_signs)
            index_end_breathing = int(high_breathing / vital_signs_sample_rate * fft_size_vital_signs)

    linear_region_breathing.sigRegionChanged.connect(linear_region_breathing_changed)

    linear_region_heart = pg.LinearRegionItem([low_heart, high_heart], brush=(255, 255, 0, 20))
    plot.addItem(linear_region_heart)
    def linear_region_heart_changed():
        global low_heart, high_heart, heart_b, index_start_heart, index_end_heart
        region = linear_region_heart.getRegion()
        if (region[0] < vital_signs_sample_rate / 4 and region[1] < vital_signs_sample_rate / 2 and
                region[0] > 0 and region[1] > 0):
            low_heart = region[0]
            high_heart = region[1]
            heart_b = firwin(filter_order, [low_heart / nyquist_freq, high_heart / nyquist_freq], pass_zero=False)
            index_start_heart = int(low_heart / vital_signs_sample_rate * fft_size_vital_signs)
            index_end_heart = int(high_heart / vital_signs_sample_rate * fft_size_vital_signs)
    linear_region_heart.sigRegionChanged.connect(linear_region_heart_changed)
    plot.setXRange(low_breathing , high_heart + 0.5)
    return plot, plot_objects

# Usage:
if ENABLE_VITALSIGNS_SPECTRUM:
    vital_signs_spectrum_figure, vital_signs_plots = generate_vitalsigns_spectrum_plot(num_rx_antennas)
    vital_signs_spectrum_figure.show()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_estimation_plot():
    plot = pg.plot(title='Vital Signs Estimation')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Time [s]')
    plot.setLabel('left', 'Rate [b.p.m.]')
    plot.addLegend()
    plots = [
        ('g', 'Breathing'),
        ('c', 'Heart'),
        ('moccasin', 'NeuLog Respiration'),
        ('skyblue', 'NeuLog Pulse')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    # for i in range(num_rx_antennas):
    for j, (color, name) in enumerate(plots):
        line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][0]}
        if name == 'Breathing ':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('g')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8, name=f'{name}')
        elif name == 'Heart ':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('c')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8, name=f'{name}')
        elif name == 'NeuLog Respiration':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('moccasin')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8, name=f'{name}')
        elif name == 'NeuLog Pulse':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('skyblue')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8, name=f'{name}')
        else:
            plot_obj = plot.plot(pen=line_style, name=f'{name}')
        plot_obj.setVisible(True)
        plot_objects[j].append(plot_obj)
    # plot_objects[0][0].setVisible(True)
    # plot_objects[1][0].setVisible(True)
    return plot, plot_objects
# Usage:
if ENABLE_ESTIMATION_PLOT:
    estimation_figure, estimation_plots = generate_estimation_plot()
    estimation_figure.show()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
app = QApplication([])
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
timer = QTimer()
timer.timeout.connect(update_plots)
timer.start(figure_update_time)  # Update the plots every figure_update_time milliseconds
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if __name__ == "__main__":
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # Create an instance of HeartBreathingWindow
    heart_breathing_window = HeartBreathingWindow()
    heart_breathing_window.show()
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # connect to the device
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    pp = pprint.PrettyPrinter()
    with DeviceLtr11() as device:
        print("Radar SDK Version: " + get_version())
        print("Sampling Frequency [Hz]: ", sample_rate)
        print("Vital Signs Sampling Rate [Hz]: ", vital_signs_sample_rate)

        sampling_frequency = device.get_sampling_frequency(prt_index)
        dds_rate = int(sampling_frequency/vital_signs_sample_rate)
        print("DDS Rate: ", dds_rate)

        filter_cutoff = vital_signs_sample_rate/sampling_frequency/2
        low_pass_filter_coeffs = firwin(filter_order, filter_cutoff, pass_zero=True)

        config_defaults = device.get_config_defaults()

        config = Ltr11Config(
            aprt_factor=4,
            detector_threshold=80,
            disable_internal_detector=True,
            hold_time=8,
            mode=0,  # 0: continuous wave mode, -- 1: pulse mode
            num_of_samples=num_of_samples,
            prt=prt_index,
            pulse_width=0,
            rf_frequency_Hz=61044000000,
            rx_if_gain=8,
            tx_power_level=7,
        )
        device.set_config(config)

        pp.pprint(device.get_config())
        print('vital_signs_sample_rate = ', vital_signs_sample_rate, 'Hz')
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # initialization
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        raw_data = np.zeros(raw_data_size, dtype=np.complex128)
        filtered_raw_data = np.zeros(raw_data_size, dtype=np.complex128)
        radar_time_stamp = np.zeros(buffer_data_size)
        buffer_data_dds = np.zeros(buffer_data_size, dtype=np.complex128)
        I_Q_envelop = np.zeros(buffer_data_size)
        wrapped_phase_plot = np.zeros(buffer_data_size)
        unwrapped_phase_plot = np.zeros(buffer_data_size)
        filtered_breathing_plot = np.zeros(buffer_data_size)
        filtered_heart_plot = np.zeros(buffer_data_size)

        buffer_dds_fft = np.zeros(fft_size_vital_signs)
        phase_unwrap_fft = np.zeros(fft_size_vital_signs)
        breathing_fft = np.zeros(fft_size_vital_signs)
        heart_fft = np.zeros(fft_size_vital_signs)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        range_profile_peak_indices = np.zeros(buffer_data_size)
        breathing_rate_estimation_index = np.zeros(buffer_data_size)
        heart_rate_estimation_index = np.zeros(buffer_data_size)
        breathing_rate_estimation_value = np.zeros(buffer_data_size)
        heart_rate_estimation_value = np.zeros(buffer_data_size)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # NeuLog
        neulog_time_stamp = np.zeros(neulog_estimation_size_respiration)
        neulog_respiration_values = np.zeros(neulog_estimation_size_respiration)
        neulog_respiration_estimation_value = np.zeros(neulog_estimation_size_respiration)
        neulog_respiration_fft = np.zeros(neulog_fft_size_respiration)
        neulog_respiration_peak_index = np.zeros(neulog_estimation_size_respiration)

        neulog_pulse_values = np.zeros(neulog_estimation_size_pulse)
        neulog_pulse_estimation_value = np.zeros(neulog_estimation_size_pulse)
        neulog_pulse_fft = np.zeros(neulog_fft_size_pulse)
        neulog_pulse_peak_index = np.zeros(neulog_estimation_size_pulse)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Threads for reading data and processing
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        data_thread = threading.Thread(target=read_data, args=(device,))
        data_thread.start()

        radar_processor = RadarDataProcessor()
        process_thread = threading.Thread(target=radar_processor.process_data, args=())
        process_thread.start()

        if ENABLE_NEULOG:
            neulog_thread = threading.Thread(target=read_neulog,args=(neulog_sensors,))
            neulog_thread.start()
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sys.exit(app.exec_())
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
