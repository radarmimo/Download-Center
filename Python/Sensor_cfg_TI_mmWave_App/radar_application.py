import threading
import time
import queue
import logging
from payload import RadarDataParser
from plots import RadarVisualizer
import numpy as np
from scipy.interpolate import griddata
from scipy.ndimage import zoom
# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

class RadarApplication:
    def __init__(self):
        self._initialize_variables()
        self._setup_visualizations()

    def _initialize_variables(self):
        """Initialize shared variables and components."""
        self.data_queue = queue.Queue(maxsize=100)
        self.parser = RadarDataParser()
        self.radar_visualizer = RadarVisualizer()
        self.stop_event = threading.Event()
        # self.window = MainWindow()
        self.window = []

        self.epsilon = 0.005
        self.range_profile = []
        self.noise_profile = []
        self.range_doppler_heatmap = []
        self.azimuth_static_heatmap = []
        self.detected_points = []
        self.side_info_for_detected_points = []

        self.pos = None
        self.doppler = None

    def _setup_visualizations(self):
        """Setup plots for visualizing radar data."""

        self.enable_range_profile_plot = True
        if self.enable_range_profile_plot:
            self.range_profile_figure, self.range_profile_plot_objects = (
                self.radar_visualizer.generate_range_profile_plot())

        self.enable_range_doppler_heatmap = True
        if self.enable_range_doppler_heatmap:
            self.range_doppler_heatmap_figure, self.range_doppler_heatmap_item = (
                self.radar_visualizer.generate_heatmap_plot(
                    "Range-Doppler Heatmap", "Range [m]", "Speed [km/h]"
                )
            )

        self.enable_range_azimuth_heatmap = True
        if self.enable_range_azimuth_heatmap:
            self.range_azimuth_heatmap_figure, self.range_azimuth_heatmap_item = (
                self.radar_visualizer.generate_heatmap_plot(
                    "Range-Azimuth Static Heatmap (at Doppler = 0)",
                    "Distance [m]", "Range [m]"
                )
            )

    def read_data(self, device):
        """Read data from the radar device and put complete frames into the queue."""
        buffer = b""  # Initialize an empty buffer to accumulate data
        magic_word_pattern = b"\x02\x01\x04\x03\x06\x05\x08\x07"
        expected_header_length = 40  # Length of the frame header
        max_buffer_size = 10 * 1024 * 1024  # Set a reasonable buffer size limit (10 MB)
        discard_threshold = 1024  # Log significant discards only
        debug_log_interval = 100  # Log buffer state every 100 iterations
        iteration_count = 0
        # Variables for timing
        start_time = time.time()
        total_frames = 0

        while not self.stop_event.is_set():
            try:
                if device.data_port_connected:
                    byte_count = device.data_port.in_waiting
                    if byte_count > 0:
                        raw_data = device.data_port.read(byte_count)
                        # print("Data received ... ")
                        buffer += raw_data  # Append new data to the buffer

                        # Prevent buffer overflow
                        if len(buffer) > max_buffer_size:
                            logging.warning("Buffer size exceeded limit. Resetting buffer to prevent memory overflow.")
                            buffer = b""

                        while True:
                            # Look for the magic word in the buffer
                            magic_word_index = buffer.find(magic_word_pattern)
                            if magic_word_index == -1:
                                break  # No valid frame header found yet

                            if magic_word_index > 0:
                                if magic_word_index > discard_threshold:
                                    logging.warning(f"Discarding {magic_word_index} bytes of unaligned data.")
                                buffer = buffer[magic_word_index:]

                            if len(buffer) < expected_header_length:
                                break  # Wait for more data

                            frame_header = buffer[:expected_header_length]
                            total_packet_length = int.from_bytes(frame_header[12:16], byteorder='little')

                            if len(buffer) < total_packet_length:
                                break  # Wait for more data

                            frame_data = buffer[:total_packet_length]
                            buffer = buffer[total_packet_length:]  # Remove processed frame

                            if not self.data_queue.full():
                                self.data_queue.put(frame_data)
                                # logging.info(f"Complete frame added to queue. Queue size: {self.data_queue.qsize()}")
                            else:
                                logging.warning("Queue is full. Frame not added.")

                radar_params = getattr(device, "radar_params", None)
                frame_periodicity = radar_params.get("Frame Periodicity [ms]", 100) / 1000 if radar_params else 0.1
                # self.epsilon = max(self.epsilon, 0.001)
                # time.sleep(frame_periodicity/10 + self.epsilon)
                if frame_periodicity != 0:
                    time.sleep(min(frame_periodicity / 10, 0.01))
                    # print("frame_periodicity = ", frame_periodicity)
                else:
                    time.sleep(0.5)

                # Periodic debug logging
                iteration_count += 1
                if iteration_count % debug_log_interval == 0:
                    elapsed_time = time.time() - start_time
                    avg_processing_time = elapsed_time / max(total_frames, 1)  # Avoid division by zero
                    logging.debug(f"Buffer size: {len(buffer)} bytes, Total frames: {total_frames}, "
                                  f"Avg processing time per frame: {avg_processing_time:.4f} s")
                    start_time = time.time()  # Reset start time for the next interval
                    total_frames = 0  # Reset frame count for the next interval

            except AttributeError as e:
                logging.error(f"Device attribute error: {e}")
            except ValueError as e:
                logging.error(f"Value error during data parsing: {e}")
            except IOError as e:
                logging.error(f"I/O error during data reading: {e}")
            except Exception as e:
                logging.error(f"Unexpected error: {e}")

    def process_data(self, window):
        """Process data from the queue."""
        while not self.stop_event.is_set():
            try:
                if not self.data_queue.empty():
                    raw_data = self.data_queue.get_nowait()  # Non-blocking retrieval
                    magic_word_pattern = b"\x02\x01\x04\x03\x06\x05\x08\x07"
                    magic_word_index = raw_data.find(magic_word_pattern)

                    if magic_word_index == -1:
                        continue  # No valid data found

                    data = raw_data[magic_word_index:]
                    frame_header = data[:40]
                    parsed_header = self.parser.parse_frame_header(frame_header)
                    tlv_data = self.parse_tlvs(data[40:], window)

                    # Handle parsed data with the window passed as a parameter
                    self.handle_data(parsed_header, tlv_data, window)

                    # Check queue size after processing
                    if self.data_queue.qsize() > 1:
                        logging.info(f"Queue size after processing: {self.data_queue.qsize()}")

            except queue.Empty:
                pass  # No data in the queue, continue to next cycle
            except Exception as e:
                logging.error(f"Error processing data: {e}")

            # Short sleep to avoid excessive CPU usage, adjust as necessary
            time.sleep(0.01)  # Keep this small for real-time processing

    def parse_tlvs(self, tlv_data, window):
        """Parse TLV data from the payload."""
        tlv_list = []
        tlv_index = 0
        while tlv_index < len(tlv_data):
            try:
                tlv_type = int.from_bytes(tlv_data[tlv_index:tlv_index+4], byteorder='little')
                tlv_length = int.from_bytes(tlv_data[tlv_index+4:tlv_index+8], byteorder='little')
                tlv_payload = tlv_data[tlv_index+8:tlv_index+8+tlv_length]
                parsed_tlv = self.parser.parse_tlv(tlv_type, tlv_payload,window)
                tlv_list.append({'type': tlv_type, 'data': parsed_tlv, 'length': tlv_length, 'payload':tlv_payload})
                tlv_index += 8 + tlv_length
            except Exception as e:
                logging.error(f"Error parsing TLVs at index {tlv_index}: {e}")
                break
        return tlv_list

    def handle_data(self, parsed_header, tlv_data, window):
        """Handle parsed radar data."""
        try:
            if parsed_header:
                window.update_specified_table('header_table', parsed_header)

            for tlv in tlv_data:
                tlv_info = tlv['data']
                tlv_type = tlv['type']

                if tlv_type == 6:
                    window.update_specified_table('statistics_table', tlv_info)
                elif tlv_type == 9:
                    window.update_specified_table('temperature_table', tlv_info)
                elif tlv_type == 2:
                    self.range_profile = tlv_info
                elif tlv_type == 3:
                    self.noise_profile = tlv_info
                elif tlv_type == 4:
                    self.azimuth_static_heatmap = tlv_info
                elif tlv_type == 5:
                    self.range_doppler_heatmap = tlv_info
                elif tlv_type == 1:
                    self.detected_points = tlv_info
                    window.update_specified_table('detected_points_table', tlv_info)
                elif tlv_type == 7:
                    self.side_info_for_detected_points = tlv_info
                    window.update_specified_table('points_info_table', tlv_info)
        except Exception as e:
            logging.error(f"Error handling data: {e}")

    def update_plots_wrapper(self, window):
        """Wrapper function to update plots with new data."""
        radar_params = getattr(window, "radar_params", None)
        # unambiguous_range_m = radar_params.get("Unambiguous Range [m]", 10)
        maximum_range = radar_params.get("Maximum Range [m]", 10)
        unambiguous_velocity_km_h = radar_params.get("Unambiguous Velocity [km/h]", 10)
        min_value_range_doppler = radar_params.get("Range-Doppler Heatmap Minimum Value", 0)
        max_value_range_doppler = radar_params.get("Range-Doppler Heatmap Maximum Value", 4096)
        num_range_bins = radar_params.get("Number of Range FFT Bins", 256)
        # num_doppler_bins = radar_params.get("Number of Doppler FFT Bins", 16)
        min_value_range_azimuth = radar_params.get("Azimuth Static Heatmap Minimum Value", 0)
        max_value_range_azimuth = radar_params.get("Azimuth Static Heatmap Maximum Value", 2000)
        range_doppler_heatmap_grid_size = int(
            radar_params.get("Range-Doppler Heatmap Grid Size", 250))  # Grid resolution for image
        azimuth_static_heatmap_grid_size = int(radar_params.get("Azimuth Static Heatmap Grid Size", 250))  # Grid resolution for image
        azimuth_limits = 90
        if self.range_profile:
            if radar_params is None:
                x1 = 0
            else:
                num_samples_per_chirp = radar_params.get("Number of Samples per Chirp")
                range_resolution = radar_params.get("Range Resolution [m]")

                if num_samples_per_chirp is not None and range_resolution is not None:
                    x1 = num_samples_per_chirp * range_resolution
                else:
                    x1 = 0
            range_profile = 10 * (np.array(self.range_profile, dtype=np.complex64) / 512.0)
            noise_profile = 10 * (np.array(self.noise_profile, dtype=np.complex64) / 512.0)

            # logging.info(f"Raw Range Profile Shape: {range_profile.shape}")
            # logging.info(f"Raw Noise Profile Shape: {noise_profile.shape}")

            # Update the radar plots
            self.radar_visualizer.update_range_profile_plot(self.range_profile_plot_objects, x1, range_profile, x1,
                                                            noise_profile)
        if self.range_doppler_heatmap:
            #
            range_doppler_heatmap = np.array(self.range_doppler_heatmap)  # Shape: (256, 16)
            range_doppler_heatmap = np.fft.fftshift(range_doppler_heatmap, axes=1)
            desired_rows = max(range_doppler_heatmap_grid_size, range_doppler_heatmap.shape[0])
            desired_cols = max(range_doppler_heatmap_grid_size, range_doppler_heatmap.shape[1])

            # Rescale factors for each dimension
            scale_y = desired_rows / range_doppler_heatmap.shape[0]
            scale_x = desired_cols / range_doppler_heatmap.shape[1]
            interpolated_heatmap = zoom(range_doppler_heatmap, (scale_y, scale_x), order=1)  # Bilinear interpolation

            primary_axis = np.linspace(0, maximum_range, desired_rows)
            secondary_axis = np.linspace(-unambiguous_velocity_km_h, unambiguous_velocity_km_h, desired_cols)

            self.radar_visualizer.update_heatmap_plot(self.range_doppler_heatmap_item, interpolated_heatmap,
                                                      primary_axis, secondary_axis, False,
                                                      min_value_range_doppler, max_value_range_doppler,
                                                      colormap='jet')

        if len(self.azimuth_static_heatmap) > 0:
            logging.debug(f"Azimuth static heatmap dimensions: {np.shape(self.azimuth_static_heatmap)}")

            heatmap_data = np.abs(self.azimuth_static_heatmap).T
            num_azimuth_bins = heatmap_data.shape[0]

            # Index creation
            range_index = np.linspace(0, maximum_range, num_range_bins)
            azimuth_index = np.linspace(-azimuth_limits / 2, azimuth_limits / 2, num_azimuth_bins)

            # Convert azimuth to radians for polar plot
            azimuth_rad = np.deg2rad(azimuth_index)

            # Create a grid of azimuth and range
            azimuth_grid, range_grid = np.meshgrid(azimuth_rad, range_index, indexing='ij')

            # Convert polar coordinates (range, azimuth) to Cartesian (x, y)
            xx = range_grid * np.cos(azimuth_grid)  # x = r * cos(θ)
            yy = range_grid * np.sin(azimuth_grid)  # y = r * sin(θ)

            # Create a grid for the image (rescale to grid_size)
            x_grid = np.linspace(np.min(xx), np.max(xx), azimuth_static_heatmap_grid_size)
            y_grid = np.linspace(np.min(yy), np.max(yy), azimuth_static_heatmap_grid_size)

            # Flatten the original data for interpolation
            points = np.array([xx.flatten(), yy.flatten()]).T
            values = heatmap_data.flatten()

            # Create a 2D grid for the interpolation
            x_grid_2d, y_grid_2d = np.meshgrid(x_grid, y_grid)

            # Interpolate the matrix onto the new grid
            matrix_rescaled = griddata(points, values, (x_grid_2d, y_grid_2d), method='cubic')

            primary_axis = np.linspace(-maximum_range/2, maximum_range/2, num_range_bins)
            secondary_axis = np.linspace(0, maximum_range, num_range_bins)

            self.radar_visualizer.update_heatmap_plot(
                self.range_azimuth_heatmap_item, matrix_rescaled,
                primary_axis, secondary_axis, False,
                min_value_range_azimuth, max_value_range_azimuth,
                colormap='jet'
            )
        if len(self.detected_points) > 0:
            pos = np.array([[point['X'], point['Y'], point['Z']] for point in self.detected_points])
            doppler = np.array([[point['Doppler']] for point in self.detected_points])
            color = np.ones((len(pos), 4))  # Initialize with white color
            color[:, 0] = 1.0  # Red channel
            color[:, 1] = 0.0  # Green channel
            color[:, 2] = 0.0  # Blue channel
            color[:, 3] = 1.0  # Full opacity
            size = np.ones(len(pos)) * 15  # Point size
            window.three_d_plot_item.setData(pos=pos, color=color, size=size)
            # scatter_3d.setData(pos=pos, color=color, size=size)

            # print("pos = ", pos)
            # print("doppler = ", doppler)
        if len(self.side_info_for_detected_points) > 0:
            snr = np.array([[point['snr']] for point in self.side_info_for_detected_points])
            noise = np.array([[point['noise']] for point in self.side_info_for_detected_points])
            # print("snr = ", self.snr)
            # print("noise = ", self.noise)
