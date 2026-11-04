import struct
import logging
import numpy as np

class RadarDataParser:
    """
    A class to parse radar data including detected points, range profiles, noise profiles, statistics, and temperature stats.
    """

    def __init__(self):
        self.radar_params = None  # Placeholder for radar parameters
        self.buffer = b""
        self.expected_length = None


    def parse_frame_header(self, frame_header):
        header = {
            "Magic Word": frame_header[:8],
            "Version": int.from_bytes(frame_header[8:12], byteorder='little'),
            "Total Packet Length": int.from_bytes(frame_header[12:16], byteorder='little'),
            "Platform": int.from_bytes(frame_header[16:20], byteorder='little'),
            "Frame Number": int.from_bytes(frame_header[20:24], byteorder='little'),
            "Time (CPU Cycles)": int.from_bytes(frame_header[24:28], byteorder='little'),
            "Num Detected Obj": int.from_bytes(frame_header[28:32], byteorder='little'),
            "Num TLVs": int.from_bytes(frame_header[32:36], byteorder='little'),
            "Subframe Number": int.from_bytes(frame_header[36:40], byteorder='little'),
        }
        return header

    def parse_tlv(self, type_value, payload, window):
        """
        Parse the TLV data. The TLV header contains Type and Length.
        Depending on the Type, different parsing logic is applied to the payload.
        """

        # Depending on the Type, process the payload differently
        if type_value == 1:  # Detected Points
            return self.parse_detected_points(payload)
        elif type_value == 2:  # Range Profile
            return self.parse_range_profile(payload)
        elif type_value == 3:  # Noise Floor Profile
            return self.parse_noise_profile(payload)
        elif type_value == 4:  # Azimuth Static Heatmap
            return self.parse_azimuth_static_heatmap(payload,window)
        elif type_value == 5:  # Range-Doppler Heatmap
            return self.parse_range_doppler_heatmap(payload, window)
        elif type_value == 6:  # Statistics (Performance)
            return self.parse_statistics(payload)
        elif type_value == 7:  # Side Info for Detected Points
            return self.parse_side_info(payload)
        elif type_value == 8:  # Azimuth/Elevation Static Heatmap
            return self.parse_azimuth_elevation_static_heatmap(payload)
        elif type_value == 9:  # Temperature Statistics
            return self.parse_temperature_stats(payload)
        else:
            # print(f"Unknown Type: {type_value}")
            return None

    def parse_detected_points(self, payload):
        point_size = 16
        detected_points = []
        # expected_length = num_detected_obj * point_size
        num_detected_obj = int(len(payload) / point_size)


        for i in range(num_detected_obj):
            start_index = i * point_size
            try:
                x = struct.unpack('<f', payload[start_index:start_index + 4])[0]
                y = struct.unpack('<f', payload[start_index + 4:start_index + 8])[0]
                z = struct.unpack('<f', payload[start_index + 8:start_index + 12])[0]
                doppler = struct.unpack('<f', payload[start_index + 12:start_index + 16])[0]
            except struct.error as e:
                logging.error(f"Error unpacking data at index {start_index}: {e}")
                continue

            point = {"X": x, "Y": y, "Z": z, "Doppler": doppler}
            detected_points.append(point)

        return detected_points

    def parse_range_profile(self, tlv_payload):
        profile_size = len(tlv_payload) // 4
        range_profile = []

        for i in range(profile_size):
            point_bytes_real = tlv_payload[i * 4: i * 4 + 2]
            point_bytes_imag = tlv_payload[i * 4 + 2: (i + 1) * 4]
            point_value_real = int.from_bytes(point_bytes_real, byteorder='little', signed=True)
            point_value_imag = int.from_bytes(point_bytes_imag, byteorder='little', signed=True)
            range_profile.append(complex(point_value_real, point_value_imag))

        return range_profile

    def parse_noise_profile(self, tlv_payload):
        point_size = 2
        profile_size = len(tlv_payload) // point_size
        noise_profile = []

        for i in range(profile_size):
            point_bytes = tlv_payload[i * point_size:(i + 1) * point_size]
            point_value = int.from_bytes(point_bytes, byteorder='little', signed=True)
            noise_profile.append(point_value)

        return noise_profile

    def _range_fft_bins(self, radar_params):
        return int(radar_params.get("Number of Range FFT Bins") or radar_params.get("Number of Samples per Chirp") or 0)

    def _doppler_fft_bins(self, radar_params):
        # The Doppler dimension is the number of chirps in one coherent
        # processing interval per TX (TDM), not chirps-per-loop.
        if radar_params.get("Waveform Multiplexing") == "Phased-Array":
            chirps = int(radar_params.get("Number of Chirps in Frame") or 0)
        else:
            counts = radar_params.get("TX Chirps per Frame") or {}
            chirps = max((int(v) for v in counts.values()), default=0)
            if not chirps:
                chirps = int(radar_params.get("Number of Loops") or 0)
        if chirps <= 0:
            return 0
        # SDK range-Doppler TLVs are padded to the processing Doppler FFT size.
        return 1 << (chirps - 1).bit_length()

    def parse_azimuth_static_heatmap(self, payload, window):
        """Parse complex16 static azimuth heatmap using actual FFT/array sizes."""
        radar_params = getattr(window, "radar_params", None) or {}
        range_bins = self._range_fft_bins(radar_params)
        antennas = int(radar_params.get("Length of Virtual Array") or 0)
        if range_bins <= 0 or antennas <= 0:
            logging.warning("Cannot parse azimuth heatmap: range FFT bins or virtual-array length is unavailable.")
            return None
        bytes_per_cell = 4  # complex16: imaginary int16 followed by real int16
        expected = range_bins * antennas * bytes_per_cell
        if len(payload) != expected:
            logging.warning("Azimuth heatmap TLV size mismatch: got %d bytes; expected %d (%d x %d complex bins).",
                            len(payload), expected, range_bins, antennas)
            return None
        values = np.frombuffer(payload, dtype="<i2").astype(np.float32)
        values = values.reshape(range_bins, antennas, 2)
        return values[:, :, 1] + 1j * values[:, :, 0]

    def parse_range_doppler_heatmap(self, payload, window):
        """Parse uint16 range-Doppler heatmap with dimensions from frame/TX schedule."""
        radar_params = getattr(window, "radar_params", None) or {}
        range_bins = self._range_fft_bins(radar_params)
        doppler_bins = self._doppler_fft_bins(radar_params)
        if range_bins <= 0 or doppler_bins <= 0:
            logging.warning("Cannot parse range-Doppler heatmap: FFT dimensions are unavailable.")
            return None
        expected = range_bins * doppler_bins * 2
        if len(payload) != expected:
            logging.warning("Range-Doppler TLV size mismatch: got %d bytes; expected %d (%d x %d uint16 bins).",
                            len(payload), expected, range_bins, doppler_bins)
            return None
        return np.frombuffer(payload, dtype="<u2").reshape(range_bins, doppler_bins).copy()

    def parse_statistics(self, tlv_payload):
        expected_length = 24
        if len(tlv_payload) != expected_length:
            logging.error(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")
            return None

        stats_format = '<6I'
        try:
            stats = struct.unpack(stats_format, tlv_payload)
        except struct.error as e:
            logging.error(f"Error unpacking statistics data: {e}")
            return None

        statistics = {
            "interFrameProcessingTime(usec)": stats[0],
            "transmitOutputTime(usec)": stats[1],
            "interFrameProcessingMargin(usec)": stats[2],
            "interChirpProcessingMargin(usec)": stats[3],
            "activeFrameCPULoad(%)": stats[4],
            "interFrameCPULoad": stats[5],
        }
        return statistics

    def parse_side_info(self, payload):
        """
        Parse the side information from the payload. Each detected point contains two 2-byte values:
        - SNR (Signal-to-Noise Ratio)
        - Noise

        Args:
        - payload (bytearray): The raw byte data containing the side information for each detected point.

        Returns:
        - List[dict]: A list of dictionaries where each dictionary contains 'snr' and 'noise' for a point.
        """
        # The payload is expected to be a bytearray with each point taking 4 bytes
        detected_points = []

        # Iterate through the payload in chunks of 4 bytes (2 bytes for snr and 2 bytes for noise per point)
        num_points = len(payload) // 4  # Number of detected points

        for i in range(num_points):
            # Extract the SNR and Noise from the 4-byte chunk
            snr_bytes = payload[i * 4:i * 4 + 2]  # First 2 bytes: snr
            noise_bytes = payload[i * 4 + 2:i * 4 + 4]  # Last 2 bytes: noise

            # Convert the bytes to unsigned 16-bit integers
            snr = int.from_bytes(snr_bytes, byteorder='little')  # SNR in 0.1 dB
            noise = int.from_bytes(noise_bytes, byteorder='little')  # Noise in 0.1 dB

            # Store the parsed values in a dictionary
            point_info = {'snr': snr * 0.1, 'noise': noise * 0.1}  # Convert to dB
            detected_points.append(point_info)

        return detected_points

    def parse_azimuth_elevation_static_heatmap(self, payload):
        # Your parsing logic for azimuth/elevation static heatmap
        pass

    def parse_temperature_stats(self, tlv_payload):
        expected_length = 28
        if len(tlv_payload) != expected_length:
            logging.error(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")
            return None

        try:
            (
                temp_report_valid,
                time,
                tmp_rx0_sens,
                tmp_rx1_sens,
                tmp_rx2_sens,
                tmp_rx3_sens,
                tmp_tx0_sens,
                tmp_tx1_sens,
                tmp_tx2_sens,
                tmp_pm_sens,
                tmp_dig0_sens,
                tmp_dig1_sens
            ) = struct.unpack('<I I H H H H H H H H H H', tlv_payload)
        except struct.error as e:
            logging.error(f"Error unpacking temperature stats: {e}")
            return None

        temperature_stats = {
            "tempReportValid": temp_report_valid,
            "time (ms)": time,
            "tmpRx0Sens (°C)": tmp_rx0_sens,
            "tmpRx1Sens (°C)": tmp_rx1_sens,
            "tmpRx2Sens (°C)": tmp_rx2_sens,
            "tmpRx3Sens (°C)": tmp_rx3_sens,
            "tmpTx0Sens (°C)": tmp_tx0_sens,
            "tmpTx1Sens (°C)": tmp_tx1_sens,
            "tmpTx2Sens (°C)": tmp_tx2_sens,
            "tmpPmSens (°C)": tmp_pm_sens,
            "tmpDig0Sens (°C)": tmp_dig0_sens,
            "tmpDig1Sens (°C)": tmp_dig1_sens
        }
        return temperature_stats
