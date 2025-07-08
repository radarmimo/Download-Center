import math
from PyQt5.QtWidgets import QTableWidgetItem

class RadarCalculator:
    light_speed = 299792458 # Speed of light in m/s

    def __init__(self, radar_params=None):
        """
        Initialize RadarCalculator with optional radar parameters.
        :param radar_params: A dictionary of radar parameters.
        """
        self.radar_params = radar_params or {}

    @staticmethod
    def nextpow2(n):
        return 1 if n == 0 else 2 ** math.ceil(math.log2(n))

    @staticmethod
    def prevpow2(n):
        return 1 if n == 0 else 2 ** math.ceil(math.log2(n) - 1)

    @staticmethod
    def calculate_idle_time(bandwidth_MHz):
        if bandwidth_MHz <= 1000:
            return 2  # 2us for BW <= 1 GHz
        elif 1000 < bandwidth_MHz <= 2000:
            return 3.5  # 3.5us for 1 GHz < BW <= 2 GHz
        elif 2000 < bandwidth_MHz <= 3000:
            return 5  # 5us for 2 GHz < BW <= 3 GHz
        else:
            return 7  # 7us for BW > 3 GHz

    @staticmethod
    def clamp_data(new_value, min_value, max_value):
        return max(min_value, min(max_value, new_value))

    @staticmethod
    def is_frequency_slope_within_bounds(freq_slope_MHz_us, min_slope, max_slope):
        return min_slope <= freq_slope_MHz_us <= max_slope

    def calculate_unambiguous_velocity_and_velocity_resolution(self, freq_start_GHz, chirp_cycle_time_us, ntx,
                                                               number_chirp_in_one_loop, chirps_per_frame,
                                                               waveform_multiplexing):
        if waveform_multiplexing == "Phased-Array":
            ntx = 1
            number_of_chirps_in_cpi = chirps_per_frame
        else:
            number_of_chirps_in_cpi = number_chirp_in_one_loop
        lambda_ = self.light_speed / (freq_start_GHz * 1e9)
        unambiguous_velocity_km_h = round(lambda_ / (4 * chirp_cycle_time_us * 1e-6) * 3.6 / ntx, 1)
        velocity_resolution_km_h = round(2 * unambiguous_velocity_km_h / number_of_chirps_in_cpi, 1)
        return unambiguous_velocity_km_h, velocity_resolution_km_h

    def calculate_virtual_array_length(self, ntx, nrx, waveform_multiplexing):
        if waveform_multiplexing == "Phased-Array":
            ntx = 1
        return ntx * nrx

    def calculate_unambiguous_range(self, beat_freq_MHz, freq_slope_MHz_us):
        return round(self.light_speed * beat_freq_MHz / (2 * (freq_slope_MHz_us * 1e6)), 1)

    def calculate_burst_periodicity_us(self, ramp_end_time_us, idle_time_us, number_chirps_in_burst):
        return round((ramp_end_time_us + idle_time_us) * number_chirps_in_burst, 3)

    def calculate_chirp_time_us_from_ramp(self, ramp_end_time_us, adc_start_time_us):
        return round(ramp_end_time_us - adc_start_time_us, 3)

    def calculate_chirp_cycle_time_us(self, idle_time_us, adc_start_time_us, chirp_time_us):
        return round(idle_time_us + adc_start_time_us + chirp_time_us, 3)

    def calculate_chirp_time_us_from_unambiguous_velocity(self, unambiguous_velocity_km_h, freq_start_GHz, ntx,
                                                          idle_time_us, adc_start_time_us, freq_slope_MHz_us,
                                                          velocity_resolution_km_h,beat_freq_MHz, number_of_loops):
        lambda_ = self.light_speed / (freq_start_GHz * 1e9)
        chirp_cycle_time_us = lambda_ * 3.6 / (unambiguous_velocity_km_h * ntx * 4 * 1e-6)
        chirp_time_us = chirp_cycle_time_us - idle_time_us - adc_start_time_us
        if chirp_time_us < 0:
            chirp_time_us = 0
            chirp_cycle_time_us = idle_time_us + adc_start_time_us
        ramp_end_time_us = chirp_time_us + adc_start_time_us
        bandwidth_MHz = self.calculate_bandwidth_from_freq_slope(freq_slope_MHz_us, ramp_end_time_us)
        unambiguous_range_m = self.calculate_unambiguous_range(beat_freq_MHz, freq_slope_MHz_us)
        range_resolution_m = self.calculate_range_resolution(bandwidth_MHz)
        number_chirp_in_one_loop = round(2 * unambiguous_velocity_km_h /velocity_resolution_km_h)

        number_chirps_in_burst = number_chirp_in_one_loop * number_of_loops
        burst_periodicity_us = self.calculate_burst_periodicity_us(ramp_end_time_us, idle_time_us,
                                                                                    number_chirps_in_burst)
        chirp_repetition_period_us = round(ntx * chirp_cycle_time_us)
        active_frame_time_ms = self.calculate_active_frame_time_ms(chirp_repetition_period_us,
                                                                                    number_chirp_in_one_loop)


        return {
            "Chirp Time [us]": chirp_time_us,
            "Ramp End Time [us]": ramp_end_time_us,
            "Chirp Cycle Time [us]":chirp_cycle_time_us,
            "Number of Chirps in Loop":number_chirp_in_one_loop,
            "Bandwidth [MHz]": bandwidth_MHz,
            "Range Resolution [m]": range_resolution_m,
            "Maximum Beat Frequency [MHz]":beat_freq_MHz,
            "Unambiguous Range [m]":unambiguous_range_m,
            "Number of Chirps in Burst": number_chirps_in_burst,
            "Burst Periodicity [us]": burst_periodicity_us,
            "Chirp Repetition Period [us]": chirp_repetition_period_us,
            "Active Frame Time [ms]": active_frame_time_ms,
        }

    def calculate_sample_per_chirp(self,chirp_time_us,sample_rate_KHz,unambiguous_range_m,range_resolution_m):
        samples_per_chirp = min(round(chirp_time_us * sample_rate_KHz * 1000), round(unambiguous_range_m / range_resolution_m))
        return samples_per_chirp

    def calculate_ramp_end_time_us(self, chirp_time_us, adc_start_time_us):
        return chirp_time_us + adc_start_time_us

    def calcuate_active_frame_time_ms(self,chirp_repetition_period_us, number_chirp_in_one_loop):
        active_frame_time_ms = round(chirp_repetition_period_us * number_chirp_in_one_loop / 1000, 3)
        return active_frame_time_ms

    def calculate_radar_cube_size_kb(self, range_bins: int, doppler_bins: int, angle_bins: int,
                                     iq_bytes: int = 2, data_type_bytes: int = 2) -> float:
        """
        Calculate the radar cube size in kilobytes (KB).

        Parameters:
        ----------
        range_bins : int
            Number of FFT bins in the range dimension.
        doppler_bins : int
            Number of FFT bins in the Doppler dimension.
        angle_bins : int
            Number of FFT bins in the angle dimension.
        iq_bytes : int, optional
            Bytes required for storing in-phase and quadrature data. Default is 2 bytes.
        data_type_bytes : int, optional
            Bytes required per data type. Default is 2 bytes.

        Returns:
        -------
        float
            Radar cube size in kilobytes (KB), rounded to three decimal places.

        Example:
        -------
        For a radar system with 256 range bins, 128 Doppler bins, and 4 angle bins:
            radar_cube_size = calculate_radar_cube_size_kb(256, 128, 4)
            # Output: 262.144 KB
        """
        # Calculate radar cube size in bytes
        radar_cube_size_bytes = (range_bins * doppler_bins * angle_bins
                                 * iq_bytes * data_type_bytes)
        # Convert bytes to kilobytes
        radar_cube_size_kb = round(radar_cube_size_bytes / 1000, 3)

        return radar_cube_size_kb

    def calculate_bandwidth_from_range_resolution(self, range_resolution_m):
        return round(self.light_speed / (2 * range_resolution_m * 1e6), 3)

    def calculate_bandwidth_from_freq_slope(self, freq_slope_MHz_us, adc_sampling_time_us):
        return round(freq_slope_MHz_us * adc_sampling_time_us, 3)

    def adjust_freq_slope(self, min_slope, max_slope, freq_slope_MHz_us_in):
        return max(min_slope, min(freq_slope_MHz_us_in, max_slope))

    def calculate_range_resolution(self, bandwidth_MHz):
        return round(self.light_speed / (2 * bandwidth_MHz * 1e6), 3)

    def calculate_frame_periodicity(self, measurement_rate_Hz,active_frame_time_ms):
        frame_periodicity_ms = 1 / measurement_rate_Hz * 1000
        if active_frame_time_ms > frame_periodicity_ms:
            frame_periodicity_ms = active_frame_time_ms
            measurement_rate_Hz = 1000/frame_periodicity_ms
        return {
            "Frame Periodicity [ms]": frame_periodicity_ms,
            "Measurement Rate [Hz]": measurement_rate_Hz,
        }

    def calculate_active_frame_time_ms(self, chirp_repetition_period_us, number_chirp_in_one_loop):
        active_frame_time_ms = round(chirp_repetition_period_us * number_chirp_in_one_loop / 1000, 3)
        return active_frame_time_ms
