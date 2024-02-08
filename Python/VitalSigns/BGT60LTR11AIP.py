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
# % Update : 27th January 2024
# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

import pprint
import numpy as np
import threading
import queue
import scipy.fft
import scipy.signal as signal
from scipy.signal import lfilter, firwin, find_peaks, filtfilt
import pyqtgraph as pg
from PyQt5.QtCore import QTimer
from pyqtgraph.Qt import QtCore
import sys
from PyQt5.QtWidgets import QApplication, QGridLayout, \
    QLabel, QVBoxLayout, QWidget
import time
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
from ifxradarsdk import get_version
from ifxradarsdk.ltr11 import DeviceLtr11
from ifxradarsdk.ltr11.types import Ltr11Config
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
num_of_samples = 200
vital_signs_sample_rate = 50    # Hz
nyquist_freq = 0.5 * vital_signs_sample_rate
filter_order = vital_signs_sample_rate + 1
buffer_time = 20  # second
dds_threshold = vital_signs_sample_rate/10
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Initial time
start_time_br = time.time()
start_time_hr = time.time()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
buffer_data_dds_size = int(buffer_time * vital_signs_sample_rate)
estimation_time = 2  # second
index_second_br = buffer_data_dds_size - estimation_time * vital_signs_sample_rate
index_second_hr = buffer_data_dds_size - estimation_time * vital_signs_sample_rate
raw_data_size = int(buffer_time * sample_rate)
num_rx_antennas = 1
frame_counter = 0
DISTANCE_PEAKS = 0.01
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Calculate normalized cutoff frequencies for breathing
low_breathing = 0.15
high_breathing = 0.6
# Calculate normalized cutoff frequencies for heat rate
low_heart = 0.85
high_heart = 2.4
EPS = 0.00000001
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
data_queue = queue.Queue()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FIGURE_UPDATE_TIME = 25  # m second
PROCESSING_UPDATE_INTERVAL = 0.05 # second
FFT_SIZE_RAW_DATA = raw_data_size
FFT_SIZE_VITAL_SIGNS = buffer_data_dds_size*4
VITAL_SIGNS_ESTIMATION_LENGTH = buffer_time*vital_signs_sample_rate

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ENABLE_PHASE_UNWRAP_PLOT = True
ENABLE_VITALSIGNS_SPECTRUM = True
ENABLE_ESTIMATION_PLOT = True
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x_axis_raw_data = np.linspace(0, buffer_time, raw_data_size)
x_axis_phase_unwrap = np.linspace(0, buffer_time, buffer_data_dds_size)

x_axisRawDataFFT = np.linspace(-sample_rate/2, sample_rate/2, FFT_SIZE_RAW_DATA)
x_axisVitalSignsFFT = np.linspace(-vital_signs_sample_rate/2, vital_signs_sample_rate/2, FFT_SIZE_VITAL_SIGNS)
x_axisVitalSignsEstimation = range(VITAL_SIGNS_ESTIMATION_LENGTH)
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
# UI class
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class HeartBreathingWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Heart and Breathing Rate")

        self.layout = QVBoxLayout()
        grid_layout = QGridLayout()
        # Breathing Rate components
        self.breathing_rate_label = QLabel("Breathing Rate [b.p.m.]:")
        self.breathing_rate_label.setStyleSheet("font-weight: bold; color: black; font-size: 32px;")
        self.breathing_rate_value = QLabel("N/A")
        self.breathing_rate_value.setStyleSheet("font-weight: bold; color: green; font-size: 32px;")

        grid_layout.addWidget(self.breathing_rate_label, 1, 0)
        grid_layout.addWidget(self.breathing_rate_value, 1, 1)

        # Heart Rate components
        self.heart_rate_label = QLabel("Heart Rate [b.p.m.]:")
        self.heart_rate_label.setStyleSheet("font-weight: bold; color: black; font-size: 32px;")
        self.heart_rate_value = QLabel("N/A")
        self.heart_rate_value.setStyleSheet("font-weight: bold; color: blue; font-size: 32px;")

        grid_layout.addWidget(self.heart_rate_label, 0, 0)
        grid_layout.addWidget(self.heart_rate_value, 0, 1)

        self.layout.addLayout(grid_layout)
        self.setLayout(self.layout)

    def set_breathing_rate(self,breathing_rate):
        self.breathing_rate_value.setText(str(breathing_rate))

    def set_heart_rate(self,heart_rate):
        self.heart_rate_value.setText(str(heart_rate))

def update_plots():
    global breathing_rate_estimation_value, heart_rate_estimation_value, start_time_br, start_time_hr,\
            breathing_rate_estimation_time_stamp, heart_rate_estimation_time_stamp
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # range profile plot
    if ENABLE_PHASE_UNWRAP_PLOT:
        phase_unwrap_plots[0][0].setData(x_axis_raw_data, np.real(raw_data))
        phase_unwrap_plots[1][0].setData(x_axis_raw_data, np.imag(raw_data))
        phase_unwrap_plots[2][0].setData(x_axis_raw_data, np.real(filtered_raw_data))
        phase_unwrap_plots[3][0].setData(x_axis_raw_data, np.imag(filtered_raw_data))

        phase_unwrap_plots[4][0].setData(x_axis_phase_unwrap, np.real(buffer_data_dds))
        phase_unwrap_plots[5][0].setData(x_axis_phase_unwrap, np.imag(buffer_data_dds))

        phase_unwrap_plots[6][0].setData(x_axis_phase_unwrap, buffer_dds_envelop)
        phase_unwrap_plots[7][0].setData(x_axis_phase_unwrap, threshold_dds_envelop)

        phase_unwrap_plots[8][0].setData(x_axis_phase_unwrap, wrapped_phase_plot*180/np.pi)
        phase_unwrap_plots[9][0].setData(x_axis_phase_unwrap, unwrapped_phase_plot*180/np.pi)

        phase_unwrap_plots[10][0].setData(x_axis_phase_unwrap[filter_order:], filtered_breathing_plot[filter_order:] * 180 / np.pi)
        phase_unwrap_plots[11][0].setData(x_axis_phase_unwrap[filter_order:], filtered_heart_plot[filter_order:] * 180 / np.pi)
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # breathing fft plot
    if ENABLE_VITALSIGNS_SPECTRUM:
        vital_signs_plots[0][0].setData(x_axisVitalSignsFFT, scipy.fft.fftshift(buffer_dds_fft))
        vital_signs_plots[1][0].setData(x_axisVitalSignsFFT, scipy.fft.fftshift(phase_unwrap_fft))
        vital_signs_plots[2][0].setData(x_axisVitalSignsFFT, scipy.fft.fftshift(breathing_fft))
        vital_signs_plots[3][0].setData(x_axisVitalSignsFFT, scipy.fft.fftshift(heart_fft))
        if breathing_rate_estimation_index[index_second_br] > 0:
            xb = x_axisVitalSignsFFT[int(FFT_SIZE_VITAL_SIGNS/2+np.mean(breathing_rate_estimation_index[index_second_br:]))]
            yb = breathing_fft[int(np.mean(breathing_rate_estimation_index[index_second_br:]))]
            vital_signs_plots[4][0].setData([xb], [yb])
            heart_breathing_window.set_breathing_rate(int(xb * 60))
        if heart_rate_estimation_index[index_second_hr] > 0:
            xh = x_axisVitalSignsFFT[int(FFT_SIZE_VITAL_SIGNS/2+np.mean(heart_rate_estimation_index[index_second_hr:]))]
            yh = heart_fft[int(np.mean(heart_rate_estimation_index[index_second_hr:]))]
            vital_signs_plots[5][0].setData([xh], [yh])
            heart_breathing_window.set_heart_rate(int(xh*60))
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ENABLE_ESTIMATION_PLOT:
        if breathing_rate_estimation_index[index_second_br] > 0:
            current_time_br = time.time()
            time_passed_br = current_time_br - start_time_br
            start_time_br = current_time_br

            breathing_rate_estimation_time_stamp = np.roll(breathing_rate_estimation_time_stamp, -1)
            breathing_rate_estimation_time_stamp[-1] = breathing_rate_estimation_time_stamp[-2] + time_passed_br

            last_index_breathing_buffer_time = len(breathing_rate_estimation_time_stamp) - 1
            last_index_br = np.searchsorted(breathing_rate_estimation_time_stamp[:last_index_breathing_buffer_time],
                                            breathing_rate_estimation_time_stamp[
                                                last_index_breathing_buffer_time] - buffer_time, side='right')


            breathing_rate_estimation_value = np.roll(breathing_rate_estimation_value, -1)
            xb = x_axisVitalSignsFFT[
                int(FFT_SIZE_VITAL_SIGNS / 2 + np.mean(breathing_rate_estimation_index[index_second_br:]))]*60
            breathing_rate_estimation_value[-1] = xb
            estimation_plots[0][0].setData(breathing_rate_estimation_time_stamp[last_index_br:], breathing_rate_estimation_value[last_index_br:])

        if heart_rate_estimation_index[index_second_hr] > 0:
            heart_rate_estimation_value = np.roll(heart_rate_estimation_value, -1)
            xh = x_axisVitalSignsFFT[
                int(FFT_SIZE_VITAL_SIGNS / 2 + np.mean(heart_rate_estimation_index[index_second_hr:]))] * 60
            heart_rate_estimation_value[-1] = xh

            current_time_hr = time.time()
            time_passed_hr = current_time_hr - start_time_hr
            start_time_hr = current_time_hr

            heart_rate_estimation_time_stamp = np.roll(heart_rate_estimation_time_stamp, -1)
            heart_rate_estimation_time_stamp[-1] = heart_rate_estimation_time_stamp[-2] + time_passed_hr

            last_index_heart_buffer_time = len(heart_rate_estimation_time_stamp) - 1
            last_index_hr = np.searchsorted(heart_rate_estimation_time_stamp[:last_index_heart_buffer_time],
                                            heart_rate_estimation_time_stamp[
                                                last_index_heart_buffer_time] - buffer_time, side='right')

            # print("indices_hr = ", indices_hr[-1])
            estimation_plots[1][0].setData(heart_rate_estimation_time_stamp[last_index_hr:], heart_rate_estimation_value[last_index_hr:])
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# processing class
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class RadarDataProcessor:
    def find_signal_peaks(self,fft_windowed_signal, index_start,index_end, distance):
        signal_region = fft_windowed_signal[index_start: index_end]
        peaks, _ = find_peaks(signal_region,
                              distance=int(max(1,distance*FFT_SIZE_VITAL_SIGNS/vital_signs_sample_rate)))
        # Filter peaks within the boundaries
        # filtered_peaks = peaks[(peaks > 0) & (peaks < len(signal_region) - 1)]
        rate_index = 0
        filtered_peaks = peaks
        if len(filtered_peaks) > 0:
            best_peak_index = np.argmax(signal_region[filtered_peaks])
            rate_index = filtered_peaks[best_peak_index] + index_start
        return rate_index

    def read_ui_inetrvals(self):
        if ENABLE_VITALSIGNS_SPECTRUM:
            interval_breathing = linear_region_breathing.getRegion()
            freq1_breathing = interval_breathing[0]
            freq2_breathing = interval_breathing[1]
            low_freq_breathing = min(freq1_breathing, freq2_breathing) / nyquist_freq
            high_freq_breathing = max(freq1_breathing, freq2_breathing) / nyquist_freq

            interval_heart = linear_region_heart.getRegion()
            freq1_heart = interval_heart[0]
            freq2_heart = interval_heart[1]
            low_freq_heart = min(freq1_heart, freq2_heart) / nyquist_freq
            high_freq_heart = max(freq1_heart, freq2_heart) / nyquist_freq
        else:
            low_freq_breathing = low_breathing / nyquist_freq
            high_freq_breathing = high_breathing / nyquist_freq
            low_freq_heart = low_heart / nyquist_freq
            high_freq_heart = high_heart / nyquist_freq

        breathing_b = firwin(filter_order, [low_freq_breathing, high_freq_breathing],
                             pass_zero=False)
        breathing_a = 1

        heart_b = firwin(filter_order, [low_freq_heart, high_freq_heart],
                                 pass_zero=False)

        heart_a = 1

        index_start_breathing = int(low_freq_breathing * FFT_SIZE_VITAL_SIGNS/2)
        index_end_breathing = int(high_freq_breathing * FFT_SIZE_VITAL_SIGNS / 2)
        index_start_heart = int(low_freq_heart * FFT_SIZE_VITAL_SIGNS/2)
        index_end_heart = int(high_freq_heart * FFT_SIZE_VITAL_SIGNS / 2)
        return (breathing_b, breathing_a, heart_b, heart_a,index_start_breathing,index_end_breathing,index_start_heart,index_end_heart)
    def vital_signs_fft(self,data,nFFT,data_length):
        windowed_signal = np.multiply(data, signal.windows.blackmanharris(data_length))
        zp2 = np.zeros(nFFT, dtype=np.complex128)
        zp2[:data_length] = windowed_signal
        fft_result = 1.0 / nFFT * np.abs(np.fft.fft(zp2)) + EPS
        return fft_result
    def process_data(self):
        global raw_data, filtered_raw_data, buffer_data_dds, wrapped_phase_plot, \
            unwrapped_phase_plot, filtered_breathing_plot, filtered_heart_plot, \
            buffer_dds_fft, phase_unwrap_fft, breathing_fft, heart_fft, \
            breathing_rate_estimation_index, heart_rate_estimation_index, \
            buffer_dds_envelop
        counter = 0
        while True:
            if not data_queue.empty():
                frame = data_queue.get()
                if np.size(frame) == num_of_samples:
                    # Apply the filter to the complex data
                    raw_data = np.roll(raw_data, -num_of_samples)
                    raw_data[-num_of_samples:] = frame

                    avg = np.mean(raw_data)

                    filtered_raw_data = filtfilt(low_pass_filter_coeffs, 1.0, raw_data - avg)
                    new_data = filtered_raw_data[-num_of_samples::dds_rate]
                    new_data_size = len(new_data)
                    #
                    buffer_data_dds = np.roll(buffer_data_dds, -new_data_size)
                    buffer_data_dds[-new_data_size:] = new_data



                    counter += new_data_size
                    if counter > PROCESSING_UPDATE_INTERVAL * vital_signs_sample_rate:
                        counter = 0

                        buffer_dds_envelop = lfilter(np.ones(vital_signs_sample_rate), 1, np.abs(buffer_data_dds))

                        wrapped_phase_plot = np.angle(buffer_data_dds)

                        # Find indices where buffer_dds_envelop is less than dds_threshold
                        indices_below_threshold = np.where(buffer_dds_envelop > dds_threshold)[0]

                        # Set corresponding indices in buffer_data_dds to zero
                        wrapped_phase_plot[indices_below_threshold] = 0

                        unwrapped_phase_plot = np.unwrap(wrapped_phase_plot)
                        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        # read UI
                        (breathing_b, breathing_a, heart_b, heart_a,index_start_breathing,index_end_breathing,
                         index_start_heart,index_end_heart) = self.read_ui_inetrvals()
                        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        filtered_breathing_plot = lfilter(breathing_b, breathing_a, unwrapped_phase_plot)
                        filtered_heart_plot = lfilter(heart_b, heart_a, unwrapped_phase_plot)
                        #
                        buffer_dds_fft = self.vital_signs_fft(buffer_data_dds, FFT_SIZE_VITAL_SIGNS,
                                                                buffer_data_dds_size)
                        phase_unwrap_fft = self.vital_signs_fft(unwrapped_phase_plot,FFT_SIZE_VITAL_SIGNS,buffer_data_dds_size)
                        breathing_fft = self.vital_signs_fft(filtered_breathing_plot[filter_order:], FFT_SIZE_VITAL_SIGNS,
                                                                buffer_data_dds_size-filter_order)
                        heart_fft = self.vital_signs_fft(filtered_heart_plot[filter_order:], FFT_SIZE_VITAL_SIGNS,
                                                                buffer_data_dds_size-filter_order)

                        rate_index_br = self.find_signal_peaks(breathing_fft, index_start_breathing,
                                                     index_end_breathing, DISTANCE_PEAKS)
                        if rate_index_br != 0:
                            breathing_rate_estimation_index = np.roll(breathing_rate_estimation_index, -1)
                            breathing_rate_estimation_index[-1] = rate_index_br

                        rate_index_hr = self.find_signal_peaks(heart_fft, index_start_heart,
                                                     index_end_heart, DISTANCE_PEAKS)
                        if rate_index_hr != 0:
                            heart_rate_estimation_index = np.roll(heart_rate_estimation_index, -1)
                            heart_rate_estimation_index[-1] = rate_index_hr
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_phase_unwrap_plot(num_rx_antennas):
    plot = pg.plot(title='Phase Estimation')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Time [s]')
    plot.setLabel('left', 'Amplitude')
    plot.addLegend()
    plots = [
        ('bisque', 'Raw Data [I]'),
        ('olive', 'Raw Data [Q]'),
        ('orange', 'Filtered Raw Data [I]'),
        ('khaki', 'Filtered Raw Data [Q]'),
        ('lightblue', 'DDS Data [I]'),
        ('gold', 'DDS Data [Q]'),
        ('hotpink', 'Envelop'),
        ('greenyellow', 'Threshold'),
        ('y', 'Wrapped Angle'),
        ('m', 'Phase Unwrap'),
        ('g', 'Breathing'),
        ('c', 'Heart')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    for i in range(num_rx_antennas):
        for j, (color, name) in enumerate(plots):
            line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][i]}
            plot_obj = plot.plot(pen=line_style, name=f'{name} (Rx {i + 1})')
            plot_obj.setVisible(False)
            plot_objects[j].append(plot_obj)
    plot_objects[8][0].setVisible(True)
    plot_objects[9][0].setVisible(True)

    return plot, plot_objects
# Usage:
if ENABLE_PHASE_UNWRAP_PLOT:
    phase_unwrap_figure, phase_unwrap_plots = generate_phase_unwrap_plot(num_rx_antennas)
    phase_unwrap_figure.show()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_vitalsigns_spectrum_plot(num_rx_antennas, low_breathing, high_breathing, low_heart, high_heart):
    plot = pg.plot(title='Vital Signs Spectrum')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Frequency [Hz]')
    plot.setLabel('left', 'Amplitude')
    plot.addLegend()
    plots = [
        ('orange', 'DDS Raw Data'),
        ('m', 'Phase Unwrap'),
        ('g', 'Breathing'),
        ('c', 'Heart '),
        ('g', 'Breathing Peak'),
        ('c', 'Heart Peak')
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
            elif name == 'Heart Peak [Method 2]':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('m')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='d', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=12, name=f'{name} (Rx {i + 1})')
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

    linear_region_breathing = pg.LinearRegionItem([low_breathing, high_breathing], brush=(255, 255, 0, 20))
    plot.addItem(linear_region_breathing, 'Breathing Linear Region')

    linear_region_heart = pg.LinearRegionItem([low_heart, high_heart], brush=(255, 255, 0, 20))
    plot.addItem(linear_region_heart)
    plot.setXRange(low_breathing , high_heart + 0.5)
    return plot, plot_objects, linear_region_breathing, linear_region_heart

# Usage:
if ENABLE_VITALSIGNS_SPECTRUM:
    vital_signs_spectrum_figure, vital_signs_plots,linear_region_breathing, linear_region_heart = generate_vitalsigns_spectrum_plot(num_rx_antennas, low_breathing, high_breathing, low_heart, high_heart)
    vital_signs_spectrum_figure.show()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_estimation_plot(num_rx_antennas):
    plot = pg.plot(title='Vital Signs Estimation')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Time [s]')
    plot.setLabel('left', 'Rate [b.p.m.]')
    plot.addLegend()
    plots = [
        ('g', 'Breathing'),
        ('c', 'Heart')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    for i in range(num_rx_antennas):
        for j, (color, name) in enumerate(plots):
            # line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][i]}
            if name == 'Breathing':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('g')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8, name=f'{name} (Rx {i + 1})')
            elif name == 'Mean Breathing':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('m')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=12, name=f'{name} (Rx {i + 1})')
            elif name == 'Heart':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('c')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8, name=f'{name} (Rx {i + 1})')
            elif name == 'Mean Heart [Method 1]':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('c')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=12, name=f'{name} (Rx {i + 1})')
            elif name == 'Heart [Method 2]':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('b')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8, name=f'{name} (Rx {i + 1})')
            elif name == 'Mean Heart [Method 2]':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('c')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=12, name=f'{name} (Rx {i + 1})')

            # plot_obj = plot.plot(pen=line_style, name=f'{name} (Rx {i + 1})')
            plot_obj.setVisible(False)
            plot_objects[j].append(plot_obj)
    plot_objects[0][0].setVisible(True)
    plot_objects[1][0].setVisible(True)
    return plot, plot_objects
# Usage:
if ENABLE_ESTIMATION_PLOT:
    estimation_figure, estimation_plots = generate_estimation_plot(num_rx_antennas)
    estimation_figure.show()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
app = QApplication([])
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
timer = QTimer()
timer.timeout.connect(update_plots)
timer.start(FIGURE_UPDATE_TIME)  # Update the plots every FIGURE_UPDATE_TIME milliseconds
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
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # initialization
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        raw_data = np.zeros(raw_data_size, dtype=np.complex128)
        filtered_raw_data = np.zeros(raw_data_size, dtype=np.complex128)
        buffer_data_dds = np.zeros(buffer_data_dds_size, dtype=np.complex128)
        buffer_dds_envelop = np.zeros(buffer_data_dds_size)
        threshold_dds_envelop = np.ones(buffer_data_dds_size) * dds_threshold
        wrapped_phase_plot = np.zeros(buffer_data_dds_size)
        unwrapped_phase_plot = np.zeros(buffer_data_dds_size)
        filtered_breathing_plot = np.zeros(buffer_data_dds_size)
        filtered_heart_plot = np.zeros(buffer_data_dds_size)

        buffer_dds_fft = np.zeros(FFT_SIZE_VITAL_SIGNS)
        phase_unwrap_fft = np.zeros(FFT_SIZE_VITAL_SIGNS)
        breathing_fft = np.zeros(FFT_SIZE_VITAL_SIGNS)
        heart_fft = np.zeros(FFT_SIZE_VITAL_SIGNS)

        breathing_rate_estimation_index = np.zeros(VITAL_SIGNS_ESTIMATION_LENGTH)
        heart_rate_estimation_index = np.zeros(VITAL_SIGNS_ESTIMATION_LENGTH)
        breathing_rate_estimation_value = np.zeros(VITAL_SIGNS_ESTIMATION_LENGTH)
        heart_rate_estimation_value = np.zeros(VITAL_SIGNS_ESTIMATION_LENGTH)
        breathing_rate_estimation_time_stamp = np.zeros(VITAL_SIGNS_ESTIMATION_LENGTH)
        heart_rate_estimation_time_stamp = np.zeros(VITAL_SIGNS_ESTIMATION_LENGTH)


        breathing_rate_mean_values = np.zeros(buffer_time)
        heart_rate_mean_values = np.zeros(buffer_time)
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
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sys.exit(app.exec_())
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        data_thread.join()
        process_thread.join()