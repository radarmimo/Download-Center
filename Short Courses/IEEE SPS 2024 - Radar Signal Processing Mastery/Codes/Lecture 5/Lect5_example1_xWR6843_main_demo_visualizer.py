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
# Compatible Sensors: TI-xWR6843, TI-xWR1843, TI-xWR1642
# % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
import sys
import time
# import queue
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QTimer
import threading
from helpers_ui import SensorSetupUI
from helpers_plots import update_plots
from helpers_payload import (parse_range_profile, parse_detected_points, parse_noise_profile, parse_statistics,
                             parse_temperature_stats, parse_detected_points_side_info)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
first_run_flag = True
figure_update_time = 25  # m second
range_profile = []
noise_profile = []
detected_points = []
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# data_queue = queue.Queue()
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def read_data(device):
    global first_run_flag, range_profile, detected_points, noise_profile
    while True:
        # data_thread.wait(timeout=0.05)  # Wait until the event is set
        # time.sleep(1 / (1 * frame_rate))
        time.sleep(1 / (1 * 100))
        if device.data_port_connected:
            byteCount = device.data_port.in_waiting
            if byteCount > 0:
                rawdata = device.data_port.read(byteCount)
                magicWordPattern = b"\x02\x01\x04\x03\x06\x05\x08\x07"
                magic_word_index = rawdata.find(magicWordPattern)
                # print("magic_word_index", magic_word_index)
                if magic_word_index == 0:
                    if first_run_flag:
                        device.send_button.setEnabled(False)
                        first_run_flag = False
                    # Slice the data from the magic word index
                    data = rawdata[magic_word_index:]

                    # Parse the frame header
                    frame_header = data[:40]
                    magic_word = int.from_bytes(frame_header[:8], byteorder='little')
                    version = int.from_bytes(frame_header[8:12], byteorder='little')
                    total_packet_length = int.from_bytes(frame_header[12:16], byteorder='little')
                    platform = int.from_bytes(frame_header[16:20], byteorder='little')
                    frame_number = int.from_bytes(frame_header[20:24], byteorder='little')
                    device_time = int.from_bytes(frame_header[24:28], byteorder='little')
                    num_detected_obj = int.from_bytes(frame_header[28:32], byteorder='little')
                    num_tlv = int.from_bytes(frame_header[32:36], byteorder='little')
                    subframe_number = int.from_bytes(frame_header[36:40], byteorder='little')
                    # print("magic_word = ", magic_word)
                    # print("total_packet_length = ", total_packet_length)
                    # print("num_tlv", num_tlv)
                    # print("subframe_number", subframe_number)
                    frame_header_info = {}
                    frame_header_info["Magic Word"] = magic_word
                    frame_header_info["Version"] = version
                    frame_header_info["Total Packet Length"] = total_packet_length
                    frame_header_info["Platform"] = platform
                    frame_header_info["Frame Number"] = frame_number
                    frame_header_info["Time"] = device_time
                    frame_header_info["Num Detected Obj"] = num_detected_obj
                    frame_header_info["Num TLVs"] = num_tlv
                    frame_header_info["Subframe Number"] = subframe_number
                    device.update_table(device.frame_table, frame_header_info)

                    # Parse TLVs
                    tlv_header_size = 8
                    tlv_data = data[40:]
                    tlv_index = 0
                    for t in range(num_tlv):
                        tlv_type = int.from_bytes(tlv_data[tlv_index:tlv_index + 4], byteorder='little')
                        # print("tlv_type = ", tlv_type)
                        tlv_length = int.from_bytes(tlv_data[tlv_index + 4:tlv_index + 8], byteorder='little')
                        tlv_payload = tlv_data[tlv_index + tlv_header_size:tlv_index + tlv_header_size + tlv_length]

                        if tlv_type == 1:  # Detected Points
                            detected_points = parse_detected_points(tlv_payload, num_detected_obj)
                        elif tlv_type == 2:  # Detected Points
                            range_profile = parse_range_profile(tlv_payload)
                        elif tlv_type == 3:
                            noise_profile = parse_noise_profile(tlv_payload)
                        elif tlv_type == 6:  # Statistics (Performance)
                            sensor_statistics = parse_statistics(tlv_payload)
                            device.update_table(device.statistics_table, sensor_statistics)
                        elif tlv_type == 7:
                            side_info = parse_detected_points_side_info(tlv_payload, num_detected_obj)
                        elif tlv_type == 9:
                            sensor_temperature = parse_temperature_stats(tlv_payload)
                            device.update_table(device.temperature_table, sensor_temperature)
                        # Add conditions for other TLV types based on guiMonitor parameters

                        # Move to the next TLV
                        tlv_index += tlv_header_size + tlv_length

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def update_plots_wrapper():
    global range_profile
    update_plots(range_profile,detected_points, noise_profile)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
timer = QTimer()
timer.timeout.connect(update_plots_wrapper)
timer.start(figure_update_time)  # Update the plots
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# main
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if __name__ == "__main__":
    app = QApplication([])
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    window = SensorSetupUI()
    window.setGeometry(100, 100, 800, 600)
    window.show()
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    data_thread = threading.Thread(target=read_data, args=(window,))
    data_thread.start()
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sys.exit(app.exec_())
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # data_thread.join()
    # process_thread.join()
    # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
