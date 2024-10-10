# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# % SPS Short Course: Radar Signal Processing Mastery
# % Theory and Hands-On Applications with mmWave MIMO Radar Sensors
# % Date: 7-11 October 2024
# % Time: 9:00AM-11:00AM ET (New York Time)
# % Presenter: Mohammad Alaee-Kerahroodi
# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# % Website: https://radarmimo.com/
# % Email: info@radarmimo.com, mohammad.alaee@uni.lu
# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
import pprint
import queue
import sys
import threading
import time

import numpy as np
import pyqtgraph as pg
import scipy.signal as signal
import statsmodels.api as sm
from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QApplication, QFrame, QGridLayout, QLabel, QVBoxLayout, QWidget
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
from ifxradarsdk import get_version
from ifxradarsdk.fmcw import DeviceFmcw
from ifxradarsdk.fmcw.types import create_dict_from_sequence, FmcwSimpleSequenceConfig, FmcwSequenceChirp
from pyqtgraph.Qt import QtCore
from scipy.ndimage import uniform_filter1d
from scipy.signal import lfilter, firwin, find_peaks

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ENABLE_RANGE_PROFILE_PLOT = True
ENABLE_PHASE_UNWRAP_PLOT = True
ENABLE_VITALSIGNS_SPECTRUM = True
ENABLE_ESTIMATION_PLOT = True
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Device settings
num_rx_antennas = 3
frame_rate = 50  # Hz (equivalent to vital signs sampling rate when number of chirps is 1)
number_of_chirps = 1
samples_per_chirp = 64
vital_signs_sample_rate = int(1 * frame_rate)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Define constants
file_path = ''
number_of_frames = 0
frame_counter = 0
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
processing_window_time = 20  # second
buffer_time = 5 * processing_window_time  # second
estimation_time = 5  # second
time_offset_synch_plots = 1.0  # second
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
figure_update_time = 25  # m second
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fft_size_range_profile = samples_per_chirp * 2
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
object_distance_start_range = 0.5
object_distance_stop_range = 0.6
epsilon_value = 0.00000001
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# peak detection
peak_finding_distance = 0.01
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
buffer_data_size = int(buffer_time * vital_signs_sample_rate)
processing_data_size = int(processing_window_time * vital_signs_sample_rate)
fft_size_vital_signs = processing_data_size * 4
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
estimation_rate = vital_signs_sample_rate  # Hz
estimation_index_breathing = buffer_data_size - estimation_time * estimation_rate
estimation_index_heart = buffer_data_size - estimation_time * estimation_rate
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# filter initial coefficients
# Calculate normalized cutoff frequencies for breathing
low_breathing = 0.15
high_breathing = 0.6
# Calculate normalized cutoff frequencies for heat rate
low_heart = 0.85
high_heart = 2.4
nyquist_freq = 0.5 * vital_signs_sample_rate
filter_order = vital_signs_sample_rate + 1
breathing_b = firwin(filter_order, [low_breathing / nyquist_freq, high_breathing / nyquist_freq], pass_zero=False)
heart_b = firwin(filter_order, [low_heart / nyquist_freq, high_heart / nyquist_freq], pass_zero=False)
index_start_breathing = int(low_breathing / vital_signs_sample_rate * fft_size_vital_signs)
index_end_breathing = int(high_breathing / vital_signs_sample_rate * fft_size_vital_signs)
index_start_heart = int(low_heart / vital_signs_sample_rate * fft_size_vital_signs)
index_end_heart = int(high_heart / vital_signs_sample_rate * fft_size_vital_signs)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
data_queue = queue.Queue()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Initial time
start_time = time.time()
neulog_start_time = start_time
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
range_profile_peak_index = 0
max_index_processing = True
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
# processing class
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class RadarDataProcessor:
    def calc_range_fft(self, data_queue):
        if not data_queue.empty():
            frame = data_queue.get()
            _, num_chirps_per_frame, num_samples_per_chirp = np.shape(frame)
            range_fft_antennas_buffer = np.zeros(int(fft_size_range_profile / 2), dtype=np.complex128)
            for iAnt in range(num_rx_antennas):
                # for iChirps in range(num_chirps_per_frame):
                mat = frame[iAnt, :, :]
                avgs = np.average(mat, 1).reshape(num_chirps_per_frame, 1)
                mat = mat - avgs
                mat = np.multiply(mat,
                                  signal.windows.blackmanharris(num_samples_per_chirp).reshape(1,
                                                                                               num_samples_per_chirp))
                zp1 = np.pad(mat, ((0, 0), (0, fft_size_range_profile - num_samples_per_chirp)), 'constant')
                range_fft = np.fft.fft(zp1, fft_size_range_profile) / num_samples_per_chirp
                range_fft = 2 * range_fft[:, :int(fft_size_range_profile / 2)]
                temp_range_fft = np.sum(range_fft, axis=0)
                range_fft_antennas_buffer = temp_range_fft + range_fft_antennas_buffer
            return range_fft_antennas_buffer / num_rx_antennas
        return None, None

    def find_signal_peaks(self, fft_windowed_signal, index_start, index_end, distance):
        signal_region = fft_windowed_signal[index_start: index_end]
        peaks, _ = find_peaks(signal_region,
                              distance=int(max(1, distance * fft_size_vital_signs / vital_signs_sample_rate)))
        # Filter peaks within the boundaries
        # filtered_peaks = peaks[(peaks > 0) & (peaks < len(signal_region) - 1)]
        rate_index = 0
        filtered_peaks = peaks
        if len(filtered_peaks) > 0:
            best_peak_index = np.argmax(signal_region[filtered_peaks])
            rate_index = filtered_peaks[best_peak_index] + index_start
        return rate_index

    def vital_signs_fft(self, data, nFFT, data_length):
        windowed_signal = np.multiply(data, signal.windows.blackmanharris(data_length))
        zp2 = np.zeros(nFFT, dtype=np.complex128)
        zp2[:data_length] = windowed_signal
        fft_result = 1.0 / nFFT * np.abs(np.fft.fft(zp2)) + epsilon_value
        return fft_result

    def process_data(self):
        global slow_time_buffer_data, I_Q_envelop, range_fft_abs, wrapped_phase_plot, unwrapped_phase_plot, \
            filtered_breathing_plot, filtered_heart_plot, buffer_raw_I_Q_fft, phase_unwrap_fft, breathing_fft, \
            heart_fft, breathing_rate_estimation_index, heart_rate_estimation_index, \
            neulog_respiration_peak_index, neulog_pulse_peak_index, neulog_respiration_fft, neulog_pulse_fft, \
            start_time, radar_time_stamp, range_profile_peak_index, range_profile_peak_indices
        counter = 0
        while True:
            time.sleep(0.001)
            if not data_queue.empty():
                current_time = time.time()
                time_passed = current_time - start_time
                start_time = current_time

                radar_time_stamp = np.roll(radar_time_stamp, -1)
                radar_time_stamp[-1] = radar_time_stamp[-2] + time_passed
                # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                range_fft_antennas_buffer = self.calc_range_fft(data_queue)
                # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                if range_fft_antennas_buffer is not None:
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # slow_time_index += 1
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    range_fft_abs = np.abs(range_fft_antennas_buffer)
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    slow_time_buffer_data = np.roll(slow_time_buffer_data, -1)
                    I_Q_envelop = np.roll(I_Q_envelop, -1)

                    start_index_range = int(object_distance_start_range / max_range * fft_size_range_profile / 2)
                    stop_index_range = int(object_distance_stop_range / max_range * fft_size_range_profile / 2)

                    range_profile_peak_indices = np.roll(range_profile_peak_indices, -1)
                    range_profile_peak_indices[-1] = np.argmax(
                        range_fft_abs[start_index_range: stop_index_range]) + start_index_range

                    range_profile_peak_index = int(np.mean(range_profile_peak_indices[-2 * vital_signs_sample_rate:]))
                    if max_index_processing:
                        slow_time_buffer_data[-1] = range_fft_antennas_buffer[range_profile_peak_index]
                    else:
                        slow_time_buffer_data[-1] = np.mean(
                            range_fft_antennas_buffer[start_index_range:stop_index_range])

                    I_Q_envelop[-1] = np.abs(slow_time_buffer_data[-1])

                    counter += 1
                    # if counter > processing_update_interval * vital_signs_sample_rate:
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    # phase unwrap
                    wrapped_phase = np.angle(slow_time_buffer_data[-counter:])
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
                    buffer_raw_I_Q_fft = self.vital_signs_fft(slow_time_buffer_data[-processing_data_size:],
                                                              fft_size_vital_signs,
                                                              processing_data_size)
                    phase_unwrap_fft = self.vital_signs_fft(unwrapped_phase_plot[-processing_data_size:],
                                                            fft_size_vital_signs,
                                                            processing_data_size)
                    breathing_fft = self.vital_signs_fft(filtered_breathing_plot[-processing_data_size:],
                                                         fft_size_vital_signs,
                                                         processing_data_size)
                    heart_fft = self.vital_signs_fft(filtered_heart_plot[-processing_data_size:], fft_size_vital_signs,
                                                     processing_data_size)
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
                    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    counter = 0
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def update_plots():
    global breathing_rate_estimation_value, heart_rate_estimation_value, \
        breathing_rate_estimation_time_stamp, heart_rate_estimation_time_stamp
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # range profile plot
    if ENABLE_RANGE_PROFILE_PLOT:
        # for k in range(num_rx_antennas):
        range_profile_plots[0][0].setData(x_axis_range_profile[min_range_index:], range_fft_abs[min_range_index:])
        range_profile_plots[3][0].setData([x_axis_range_profile[range_profile_peak_index]],
                                          [range_fft_abs[range_profile_peak_index]])

    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # phase unwrap plot
    if ENABLE_PHASE_UNWRAP_PLOT:
        # for k in range(num_rx_antennas):
        phase_unwrap_plots[0][0].setData(radar_time_stamp, np.real(slow_time_buffer_data))
        phase_unwrap_plots[1][0].setData(radar_time_stamp, np.imag(slow_time_buffer_data))
        phase_unwrap_plots[2][0].setData(radar_time_stamp, I_Q_envelop)
        phase_unwrap_plots[3][0].setData(radar_time_stamp, wrapped_phase_plot * 180 / np.pi)
        phase_unwrap_plots[4][0].setData(radar_time_stamp, unwrapped_phase_plot * 180 / np.pi)
        phase_unwrap_plots[5][0].setData(radar_time_stamp, filtered_breathing_plot * 180 / np.pi)
        phase_unwrap_plots[6][0].setData(radar_time_stamp, filtered_heart_plot * 180 / np.pi)

    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # breathing fft plot
    if ENABLE_VITALSIGNS_SPECTRUM:
        # for k in range(num_rx_antennas):
        vital_signs_plots[0][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(buffer_raw_I_Q_fft))
        vital_signs_plots[1][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(phase_unwrap_fft))
        vital_signs_plots[2][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(breathing_fft))
        vital_signs_plots[3][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(heart_fft))
        if breathing_rate_estimation_index[estimation_index_breathing] > 0:
            xb = x_axis_vital_signs_spectrum[
                int(fft_size_vital_signs / 2 + np.mean(breathing_rate_estimation_index[estimation_index_breathing:]))]
            yb = breathing_fft[int(np.mean(breathing_rate_estimation_index[estimation_index_breathing:]))]
            vital_signs_plots[4][0].setData([xb], [yb])
        if heart_rate_estimation_index[estimation_index_heart] > 0:
            xh = x_axis_vital_signs_spectrum[
                int(fft_size_vital_signs / 2 + np.mean(heart_rate_estimation_index[estimation_index_heart:]))]
            yh = heart_fft[int(np.mean(heart_rate_estimation_index[estimation_index_heart:]))]
            vital_signs_plots[5][0].setData([xh], [yh])
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ENABLE_ESTIMATION_PLOT:
        global breathing_rate_estimation_value, heart_rate_estimation_value
        if breathing_rate_estimation_index[estimation_index_breathing] > 0:
            breathing_rate_estimation_value = np.roll(breathing_rate_estimation_value, -1)
            xb = x_axis_vital_signs_spectrum[
                     round(fft_size_vital_signs / 2 + np.mean(
                         breathing_rate_estimation_index[estimation_index_breathing:]))] * 60
            breathing_rate_estimation_value[-1] = round(xb) - 2
            estimation_plots[0][0].setData(radar_time_stamp, breathing_rate_estimation_value)

        if heart_rate_estimation_index[estimation_index_heart] > 0:
            heart_rate_estimation_value = np.roll(heart_rate_estimation_value, -1)
            xh = x_axis_vital_signs_spectrum[
                     round(
                         fft_size_vital_signs / 2 + np.mean(heart_rate_estimation_index[estimation_index_heart:]))] * 60
            heart_rate_estimation_value[-1] = round(xh) - 2
            estimation_plots[1][0].setData(radar_time_stamp, heart_rate_estimation_value)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
app = QApplication([])


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# range profile plot setting up
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_range_profile_plot():
    global object_distance_start_range, object_distance_stop_range
    plot = pg.plot(title='Range Profile')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Range [m]')
    plot.setLabel('left', 'Amplitude')
    plot.addLegend()
    plots = [
        ('lime', 'Sum of Rx channels'),
        ('red', 'Real'),
        ('blue', 'Imaginary'),
        ('lightcoral', 'Selected Range Index')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    # for i in range(num_rx_antennas):
    for j, (color, name) in enumerate(plots):
        if name == 'TI - rangeBinIndexPhase':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('sandybrown')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=15,
                                 name=f'{name}')
        elif name == 'Selected Range Index':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('lightcoral')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=15,
                                 name=f'{name}')
        else:
            line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][0]}
            plot_obj = plot.plot(pen=line_style, name=f'{name}')
            plot_obj.setVisible(False)
        plot_objects[j].append(plot_obj)
    plot_objects[0][0].setVisible(True)
    linear_region_range_profle = pg.LinearRegionItem([object_distance_start_range, object_distance_stop_range],
                                                     brush=(255, 255, 0, 20))  # Yellow color with opacity
    plot.addItem(linear_region_range_profle)

    def region_changed():
        global object_distance_start_range, object_distance_stop_range
        region = linear_region_range_profle.getRegion()
        object_distance_start_range = region[0]
        object_distance_stop_range = region[1]
        # print("Linear Region Position:", region)

    linear_region_range_profle.sigRegionChanged.connect(region_changed)

    return plot, plot_objects


# Usage:
if ENABLE_RANGE_PROFILE_PLOT:
    range_profile_figure, range_profile_plots = generate_range_profile_plot()
    range_profile_figure.show()


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Phase unwrap plot setting up
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_phase_unwrap_plot():
    plot = pg.plot(title='Slow-Time Phase Unwrap')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Time [s]')
    plot.setLabel('left', 'Unwrapped Phase [deg.]')
    plot.addLegend()
    plots = [
        ('orange', 'Slow-Time Signal [I]'),
        ('beige', 'Slow-Time Signal [Q]'),
        ('hotpink', 'Envelop'),
        ('y', 'Wrapped Angle'),
        ('m', 'Phase Unwrap'),
        ('g', 'Breathing'),
        ('c', 'Heart')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    # for i in range(num_rx_antennas):
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
    slow_time_phase_unwrap_figure, phase_unwrap_plots = generate_phase_unwrap_plot()
    slow_time_phase_unwrap_figure.show()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Breathing Spectrum plot setting up
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_vitalsigns_spectrum_plot():
    global low_breathing, high_breathing, low_heart, high_heart, breathing_b, heart_b, \
        index_start_breathing, index_end_breathing, index_start_heart, index_end_heart
    plot = pg.plot(title='Vital Signs Spectrum')
    plot.showGrid(x=True, y=True)
    plot.setLabel('bottom', 'Frequency [Hz]')
    plot.setLabel('left', 'Amplitude')
    plot.addLegend()
    plots = [
        ('orange', 'I&Q Raw Data'),
        ('m', 'Phase Unwrap'),
        ('g', 'Breathing'),
        ('c', 'Heart'),
        ('g', 'Breathing Peak'),
        ('c', 'Heart Peak')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    # for i in range(num_rx_antennas):
    for j, (color, name) in enumerate(plots):
        # plot_obj = plot.plot(pen=line_style, name=f'{name} (Rx {i + 1})')
        if name == 'Breathing Peak':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('g')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=15,
                                 name=f'{name}')
        elif name == 'Heart Peak':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('c')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='d', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=15,
                                 name=f'{name}')
        else:
            line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][0]}
            plot_obj = plot.plot(pen=line_style, name=f'{name}')
        plot_obj.setVisible(False)
        plot_objects[j].append(plot_obj)
    plot_objects[2][0].setVisible(True)
    plot_objects[3][0].setVisible(True)

    linear_region_breathing = pg.LinearRegionItem([low_breathing, high_breathing], brush=(255, 255, 0, 20))
    plot.addItem(linear_region_breathing, 'Breathing Linear Region')

    def linear_region_breathing_changed():
        global low_breathing, high_breathing, breathing_b, index_start_breathing, index_end_breathing
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
    plot.setXRange(low_breathing, high_heart + 0.5)
    return plot, plot_objects


# Usage:
if ENABLE_VITALSIGNS_SPECTRUM:
    vital_signs_spectrum_figure, vital_signs_plots = generate_vitalsigns_spectrum_plot()
    vital_signs_spectrum_figure.show()


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Estimation plot setting up
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def generate_estimation_plot():
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
    # for i in range(num_rx_antennas):
    for j, (color, name) in enumerate(plots):
        line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][0]}
        if name == 'Breathing ':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('g')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8,
                                 name=f'{name}')
        elif name == 'Heart ':
            symbol_pen = pg.mkPen(None)  # No border for the symbol
            symbol_brush = pg.mkBrush('c')  # Red color for the symbol
            plot_obj = plot.plot(pen=None, symbol='o', symbolPen=symbol_pen, symbolBrush=symbol_brush, symbolSize=8,
                                 name=f'{name}')
        else:
            plot_obj = plot.plot(pen=line_style, name=f'{name}')
        plot_obj.setVisible(True)
        plot_objects[j].append(plot_obj)
    # plot_objects[0][0].setVisible(True)
    plot_objects[1][0].setVisible(False)
    return plot, plot_objects


# Usage:
if ENABLE_ESTIMATION_PLOT:
    estimation_figure, estimation_plots = generate_estimation_plot()
    estimation_figure.show()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
timer = QTimer()
timer.timeout.connect(update_plots)
timer.start(figure_update_time)  # Update the plots every 100 milliseconds
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# main
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if __name__ == "__main__":

    # connect to the device
    with DeviceFmcw() as device:
        print("Radar SDK Version: " + get_version())
        print("UUID of board: " + device.get_board_uuid())
        print("Sensor: " + str(device.get_sensor_type()))

        if num_rx_antennas == 3:
            rx_mask = 7  # rx_mask = 7 means all three receive antennas are activated
        elif num_rx_antennas == 2:
            rx_mask = 3  # rx_mask = 7 means all three receive antennas are activated
        else:
            rx_mask = 1  # rx_mask = 7 means all three receive antennas are activated

        config = FmcwSimpleSequenceConfig(
            frame_repetition_time_s=1 / frame_rate,
            chirp_repetition_time_s=0.001,
            num_chirps=number_of_chirps,
            tdm_mimo=True,
            chirp=FmcwSequenceChirp(
                start_frequency_Hz=58_000_000_000,
                end_frequency_Hz=63_500_000_000,
                sample_rate_Hz=1e6,
                num_samples=samples_per_chirp,
                rx_mask=rx_mask,
                tx_mask=1,
                tx_power_level=31,
                lp_cutoff_Hz=500000,
                hp_cutoff_Hz=80000,
                if_gain_dB=33,
            )
        )
        # num_rx_antennas = device.get_sensor_information()["num_rx_antennas"]
        sequence = device.create_simple_sequence(config)
        device.set_acquisition_sequence(sequence)

        pp = pprint.PrettyPrinter()
        pp.pprint(create_dict_from_sequence(sequence))
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # initialization
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        range_res = 3e8 / (2 * device.get_chirp_sampling_bandwidth(config.chirp))
        print("range resolution = ", range_res * 2)
        max_range = range_res * samples_per_chirp / 2
        print("maximum range = ", max_range)
        min_range = 0.15
        min_range_index = int(min_range * fft_size_range_profile / 2)
        print('vital_signs_sample_rate = ', vital_signs_sample_rate, 'Hz')
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        range_fft_abs = np.zeros(int(fft_size_range_profile / 2))
        radar_time_stamp = np.zeros(buffer_data_size)
        slow_time_buffer_data = np.zeros(buffer_data_size, dtype=np.complex128)
        I_Q_envelop = np.zeros(buffer_data_size)
        wrapped_phase_plot = np.zeros(buffer_data_size)
        unwrapped_phase_plot = np.zeros(buffer_data_size)
        filtered_breathing_plot = np.zeros(buffer_data_size)
        filtered_heart_plot = np.zeros(buffer_data_size)
        buffer_raw_I_Q_fft = np.zeros(fft_size_vital_signs)
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
        x_axis_range_profile = np.linspace(0, max_range, int(fft_size_range_profile / 2))
        x_axis_vital_signs_spectrum = np.linspace(-vital_signs_sample_rate / 2, vital_signs_sample_rate / 2,
                                                  fft_size_vital_signs)
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # Threads for reading data and processing
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        data_thread = threading.Thread(target=read_data, args=(device,))
        data_thread.start()
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # start_index = int(object_distance_start_range/max_range * samples_per_chirp)
        # end_index = int(object_distance_stop_range/max_range * samples_per_chirp)
        radar_processor = RadarDataProcessor()
        process_thread = threading.Thread(target=radar_processor.process_data, args=())
        process_thread.start()

        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # plots
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        sys.exit(app.exec_())

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
