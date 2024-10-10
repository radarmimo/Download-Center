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
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
figure_update_time = 25  # m second
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
num_rx_antennas = 1
rate_index = 80
num_of_samples = int(3 * rate_index)
samples_time = num_of_samples / sample_rate
vital_signs_sample_rate = int(sample_rate / rate_index)  # Hz
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
raw_data_size = int(processing_window_time * sample_rate)
buffer_data_size = int(buffer_time * vital_signs_sample_rate)
processing_data_size = int(processing_window_time * vital_signs_sample_rate)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fft_size_vital_signs = processing_data_size * 4
estimation_rate = vital_signs_sample_rate  # Hz
estimation_size_vital_signs = buffer_time * estimation_rate
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
estimation_index_breathing = buffer_data_size - estimation_time * estimation_rate
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
from PyQt5.QtWidgets import QApplication
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
from ifxradarsdk import get_version
from ifxradarsdk.ltr11 import DeviceLtr11
from ifxradarsdk.ltr11.types import Ltr11Config
from pyqtgraph.Qt import QtCore
from scipy.ndimage import uniform_filter1d
from scipy.signal import lfilter, firwin, find_peaks, filtfilt

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ENABLE_PHASE_UNWRAP_PLOT = True
ENABLE_VITALSIGNS_SPECTRUM = True
ENABLE_ESTIMATION_PLOT = True
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
breathing_b = firwin(filter_order, [low_breathing / nyquist_freq, high_breathing / nyquist_freq], pass_zero=False)
heart_b = firwin(filter_order, [low_heart / nyquist_freq, high_heart / nyquist_freq], pass_zero=False)
index_start_breathing = int(low_breathing / vital_signs_sample_rate * fft_size_vital_signs)
index_end_breathing = int(high_breathing / vital_signs_sample_rate * fft_size_vital_signs)
index_start_heart = int(low_heart / vital_signs_sample_rate * fft_size_vital_signs)
index_end_heart = int(high_heart / vital_signs_sample_rate * fft_size_vital_signs)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# peak detection
peak_finding_distance = 0.01
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# plots
x_axis_vital_signs_spectrum = np.linspace(-vital_signs_sample_rate / 2, vital_signs_sample_rate / 2,
                                          fft_size_vital_signs)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
frame_counter = 0
data_queue = queue.Queue()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Initial time
start_time = time.time()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
# processing class
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class RadarDataProcessor:
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
        global raw_data, filtered_raw_data, buffer_data_dds, wrapped_phase_plot, \
            unwrapped_phase_plot, filtered_breathing_plot, filtered_heart_plot, \
            buffer_dds_fft, phase_unwrap_fft, breathing_fft, heart_fft, \
            breathing_rate_estimation_index, heart_rate_estimation_index, I_Q_envelop, \
            breathing_b, heart_b, index_start_heart, index_end_heart, \
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
                    radar_time_stamp[-counter:] = radar_time_stamp[-counter - 1] + time_passed
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
                    # cycle1, trend = sm.tsa.filters.hpfilter(filtered_breathing)
                    # filtered_breathing = uniform_filter1d(cycle1, size=2 * vital_signs_sample_rate)
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
    if ENABLE_PHASE_UNWRAP_PLOT:
        phase_unwrap_plots[0][0].setData(radar_time_stamp, np.real(buffer_data_dds))
        phase_unwrap_plots[1][0].setData(radar_time_stamp, np.imag(buffer_data_dds))
        phase_unwrap_plots[2][0].setData(radar_time_stamp, I_Q_envelop)
        phase_unwrap_plots[3][0].setData(radar_time_stamp, wrapped_phase_plot * 180 / np.pi)
        phase_unwrap_plots[4][0].setData(radar_time_stamp, unwrapped_phase_plot * 180 / np.pi)
        phase_unwrap_plots[5][0].setData(radar_time_stamp, filtered_breathing_plot * 180 / np.pi)
        phase_unwrap_plots[6][0].setData(radar_time_stamp, filtered_heart_plot * 180 / np.pi)
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # breathing fft plot
    if ENABLE_VITALSIGNS_SPECTRUM:
        vital_signs_plots[0][0].setData(x_axis_vital_signs_spectrum, np.fft.fftshift(buffer_dds_fft))
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
            breathing_rate_estimation_value[-1] = round(xb)
            estimation_plots[0][0].setData(radar_time_stamp, breathing_rate_estimation_value)

        if heart_rate_estimation_index[estimation_index_heart] > 0:
            heart_rate_estimation_value = np.roll(heart_rate_estimation_value, -1)
            xh = x_axis_vital_signs_spectrum[
                     round(
                         fft_size_vital_signs / 2 + np.mean(heart_rate_estimation_index[estimation_index_heart:]))] * 60
            heart_rate_estimation_value[-1] = round(xh)
            estimation_plots[1][0].setData(radar_time_stamp, heart_rate_estimation_value)
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
        ('c', 'Heart')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    for j, (color, name) in enumerate(plots):
        line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][0]}
        plot_obj = plot.plot(pen=line_style, name=f'{name}')
        plot_obj.setVisible(False)
        plot_objects[j].append(plot_obj)
    plot_objects[5][0].setVisible(True)
    # plot_objects[6][0].setVisible(True)

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
        ('c', 'Heart Peak')
    ]
    plot_objects = [[] for _ in range(len(plots))]
    for i in range(num_rx_antennas):
        for j, (color, name) in enumerate(plots):
            if name == 'Breathing Peak':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('g')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='s', symbolPen=symbol_pen, symbolBrush=symbol_brush,
                                     symbolSize=12, name=f'{name} (Rx {i + 1})')
            elif name == 'Heart Peak':
                symbol_pen = pg.mkPen(None)  # No border for the symbol
                symbol_brush = pg.mkBrush('c')  # Red color for the symbol
                plot_obj = plot.plot(pen=None, symbol='d', symbolPen=symbol_pen, symbolBrush=symbol_brush,
                                     symbolSize=12, name=f'{name} (Rx {i + 1})')
            else:
                line_style = {'color': color, 'style': [QtCore.Qt.SolidLine, QtCore.Qt.DashLine, QtCore.Qt.DotLine][i]}
                plot_obj = plot.plot(pen=line_style, name=f'{name} (Rx {i + 1})')
            plot_obj.setVisible(False)
            plot_objects[j].append(plot_obj)
    # plot_objects[0][0].setVisible(True)
    # plot_objects[1][0].setVisible(True)
    # plot_objects[2][0].setVisible(True)
    plot_objects[2][0].setVisible(True)
    # plot_objects[3][0].setVisible(True)
    plot_objects[4][0].setVisible(True)
    # plot_objects[5][0].setVisible(True)
    # plot_objects[6][0].setVisible(True)
    # plot_objects[7][0].setVisible(True)
    # plot_objects[8][0].setVisible(True)
    # plot_objects[9][0].setVisible(True)

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
    vital_signs_spectrum_figure, vital_signs_plots = generate_vitalsigns_spectrum_plot(num_rx_antennas)
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
timer.start(figure_update_time)  # Update the plots every 100 milliseconds
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# main
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if __name__ == "__main__":
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # connect to the device
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    pp = pprint.PrettyPrinter()
    with DeviceLtr11() as device:
        print("Radar SDK Version: " + get_version())
        print("Sampling Frequency [Hz]: ", sample_rate)
        print("Vital Signs Sampling Rate [Hz]: ", vital_signs_sample_rate)

        sampling_frequency = device.get_sampling_frequency(prt_index)
        dds_rate = int(sampling_frequency / vital_signs_sample_rate)
        print("DDS Rate: ", dds_rate)

        filter_cutoff = vital_signs_sample_rate / sampling_frequency / 2
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
