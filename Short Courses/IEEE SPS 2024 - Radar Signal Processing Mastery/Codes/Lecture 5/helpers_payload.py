import struct
import logging
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_detected_points(payload, num_detected_obj):
    # Assuming each detected point is 16 bytes long
    point_size = 16
    detected_points = []

    # Calculate the expected length
    expected_length = num_detected_obj * point_size

    # Log the actual and expected payload lengths
    # print(f"Actual payload length: {len(payload)}, Expected payload length: {expected_length}")

    # # Check if the payload length is as expected
    # if len(payload) != expected_length:
    #     raise ValueError(f"Payload length {len(payload)} does not match expected length {expected_length}")
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    for i in range(num_detected_obj):
        start_index = i * point_size
        try:
            x = struct.unpack('<f', payload[start_index:start_index + 4])[0]
            y = struct.unpack('<f', payload[start_index + 4:start_index + 8])[0]
            z = struct.unpack('<f', payload[start_index + 8:start_index + 12])[0]
            doppler = struct.unpack('<f', payload[start_index + 12:start_index + 16])[0]
        except struct.error as e:
            # raise struct.error(f"Error unpacking data at index {start_index}: {e}")
            logging.error(f"Error unpacking data at index {start_index}: {e}")
            continue  # Skip this point and continue with the next

        point = {
            "X": x,
            "Y": y,
            "Z": z,
            "Doppler": doppler
        }
        detected_points.append(point)
    return detected_points
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# xWR6843, xWR1843, xWR1642, xWR1443
def parse_range_profile(tlv_payload):
    # global range_profile
    profile_size = int(len(tlv_payload) / 4)

    # Iterate through the payload to extract each profile point
    range_profile = []
    for i in range(0, profile_size):
        # Extract 2 bytes for real part
        point_bytes_real = tlv_payload[i * 4: i * 4 + 2]
        # Extract 2 bytes for imaginary part
        point_bytes_imag = tlv_payload[i * 4 + 2: (i + 1) * 4]
        # Convert bytes to an integer (assuming little-endian byte order)
        point_value_real = int.from_bytes(point_bytes_real, byteorder='little', signed=True)
        point_value_imag = int.from_bytes(point_bytes_imag, byteorder='little', signed=True)
        # Append the profile point to the profile list
        range_profile.append(complex(point_value_real, point_value_imag))
    return range_profile
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# xWRLx432
def parse_range_profile_major(tlv_payload, num_range_bins):
    # Calculate the expected length based on the number of range bins
    expected_length = num_range_bins * 4  # 4 bytes per range bin value

    # Check if the payload length matches the expected length
    if len(tlv_payload) != expected_length:
        raise ValueError(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")

    # Unpack the payload into an array of unsigned integers
    range_profile_major = struct.unpack(f'<{num_range_bins}I', tlv_payload)

    # Return the array of range profile major values
    return range_profile_major
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# xWRLx432
def parse_range_profile_minor(tlv_payload, num_range_bins):
    # Calculate the expected length based on the number of range bins
    expected_length = num_range_bins * 4  # 4 bytes per range bin value

    # Check if the payload length matches the expected length
    if len(tlv_payload) != expected_length:
        logging.error(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy
        # raise ValueError(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")

    # Unpack the payload into an array of unsigned integers
    range_profile_minor = struct.unpack(f'<{num_range_bins}I', tlv_payload)

    # Return the array of range profile minor values
    return range_profile_minor
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_noise_profile(tlv_payload):
    # Each profile point is 2 bytes long
    point_size = 2
    profile_size = len(tlv_payload) // point_size  # Calculate number of profile points

    noise_profile = []

    for i in range(profile_size):
        # Extract 2 bytes for the profile point
        point_bytes = tlv_payload[i * point_size:(i + 1) * point_size]
        # Convert bytes to an integer (assuming little-endian byte order)
        point_value = int.from_bytes(point_bytes, byteorder='little', signed=True)
        # Append the profile point to the noise profile list
        noise_profile.append(point_value)

    return noise_profile
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_azimuth_static_heatmap(tlv_payload, num_range_bins, num_virtual_ant_azim):
    # Each sample is 4 bytes (float)
    sample_size = 4
    expected_length = num_range_bins * num_virtual_ant_azim * sample_size

    # Log the actual and expected payload lengths
    print(f"Actual payload length: {len(tlv_payload)}, Expected payload length: {expected_length}")

    # Check if the payload length is as expected
    if len(tlv_payload) != expected_length:
        raise ValueError(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")

    azimuth_static_heatmap = []

    for i in range(num_range_bins):
        row = []
        for j in range(num_virtual_ant_azim):
            start_index = (i * num_virtual_ant_azim + j) * sample_size
            try:
                sample = struct.unpack('<f', tlv_payload[start_index:start_index + sample_size])[0]
            except struct.error as e:
                raise struct.error(f"Error unpacking data at index {start_index}: {e}")
            row.append(sample)
        azimuth_static_heatmap.append(row)

    return azimuth_static_heatmap
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_range_doppler_heatmap(tlv_payload, num_range_bins, num_doppler_bins):
    # Each heatmap entry is 2 bytes (unsigned integer)
    entry_size = 2
    expected_length = num_range_bins * num_doppler_bins * entry_size

    # Log the actual and expected payload lengths
    print(f"Actual payload length: {len(tlv_payload)}, Expected payload length: {expected_length}")

    # Check if the payload length is as expected
    if len(tlv_payload) != expected_length:
        logging.error(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    range_doppler_heatmap = []

    for i in range(num_range_bins):
        row = []
        for j in range(num_doppler_bins):
            start_index = (i * num_doppler_bins + j) * entry_size
            try:
                entry = struct.unpack('<H', tlv_payload[start_index:start_index + entry_size])[0]
            except struct.error as e:
                raise struct.error(f"Error unpacking data at index {start_index}: {e}")
            row.append(entry)
        range_doppler_heatmap.append(row)

    return range_doppler_heatmap
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_statistics(tlv_payload):
    # Check if the payload length is as expected (24 bytes)
    expected_length = 24
    if len(tlv_payload) != expected_length:
        logging.error(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    stats_format = '<6I'  # Format string for 6 unsigned 4-byte integers (little-endian)
    try:
        stats = struct.unpack(stats_format, tlv_payload)
    except struct.error as e:
        raise struct.error(f"Error unpacking statistics data: {e}")

    # Create a dictionary to store the statistics
    statistics = {
        "interFrameProcessingTime(usec)": stats[0],
        "transmitOutputTime(usec)": stats[1],
        "interFrameProcessingMargin(usec)": stats[2],
        "interChirpProcessingMargin(usec)": stats[3],
        "activeFrameCPULoad(%)": stats[4],
        "interFrameCPULoad": stats[5],
    }
    return statistics

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_detected_points_side_info(tlv_payload, num_detected_obj):
    # Each side info entry is 4 bytes (2 bytes for SNR and 2 bytes for noise)
    entry_size = 4
    expected_length = num_detected_obj * entry_size

    # Log the actual and expected payload lengths
    # print(f"Actual payload length: {len(tlv_payload)}, Expected payload length: {expected_length}")

    # Check if the payload length is as expected
    if len(tlv_payload) != expected_length:
        logging.error(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy
        # raise ValueError(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")

    side_info = []

    for i in range(num_detected_obj):
        start_index = i * entry_size
        try:
            snr, noise = struct.unpack('<HH', tlv_payload[start_index:start_index + entry_size])
            # Convert the SNR and noise values to dB (measured in multiples of 0.1 dB)
            snr_db = snr * 0.1
            noise_db = noise * 0.1
        except struct.error as e:
            # raise struct.error(f"Error unpacking data at index {start_index}: {e}")
            logging.error(f"Error unpacking data at index {start_index}: {e}")
            continue  # Skip this point and continue with the next

        side_info_entry = {
            "SNR (dB)": snr_db,
            "Noise (dB)": noise_db
        }
        side_info.append(side_info_entry)

    return side_info
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_azimuth_elevation_static_heatmap(tlv_payload, num_range_bins, num_virtual_antennas):
    # Each heatmap entry is 4 bytes (float)
    entry_size = 4
    expected_length = num_range_bins * num_virtual_antennas * entry_size

    # Log the actual and expected payload lengths
    print(f"Actual payload length: {len(tlv_payload)}, Expected payload length: {expected_length}")

    # Check if the payload length is as expected
    if len(tlv_payload) != expected_length:
        raise ValueError(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")

    azimuth_elevation_heatmap = []

    for i in range(num_range_bins):
        row = []
        for j in range(num_virtual_antennas):
            start_index = (i * num_virtual_antennas + j) * entry_size
            try:
                entry = struct.unpack('<f', tlv_payload[start_index:start_index + entry_size])[0]
            except struct.error as e:
                raise struct.error(f"Error unpacking data at index {start_index}: {e}")
            row.append(entry)
        azimuth_elevation_heatmap.append(row)

    return azimuth_elevation_heatmap
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def parse_temperature_stats(tlv_payload):
    expected_length = 28

    # Log the actual and expected payload lengths
    # print(f"Actual payload length: {len(tlv_payload)}, Expected payload length: {expected_length}")

    # Check if the payload length is as expected
    if len(tlv_payload) != expected_length:
        logging.error(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy
        # raise ValueError(f"Payload length {len(tlv_payload)} does not match expected length {expected_length}")

    try:
        # Unpack the payload
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
        # raise struct.error(f"Error unpacking data: {e}")
        logging.error(f"Error unpacking data: {e}")
        # continue # Skip this point and continue with the next

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
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_detected_points_compressed(payload):
    # The first part of the payload contains the unit values
    header_size = 16  # 4 bytes each for xyzUnit, dopplerUnit, snrUnit, noiseUnit
    units_format = '<f f f f H'
    units_size = struct.calcsize(units_format)

    if len(payload) < units_size:
        # raise ValueError(f"Payload length {len(payload)} is too short to contain unit values and numDetectedPoints")
        logging.error(f"Payload length {len(payload)} is too short to contain unit values and numDetectedPoints")
        return None  # Return None or an empty list based on your error handling strategy

    # Unpack the unit values and number of detected points
    xyz_unit, doppler_unit, snr_unit, noise_unit, num_detected_points = struct.unpack(units_format,
                                                                                      payload[:units_size])

    # Calculate the expected length
    expected_length = header_size + (10 * num_detected_points)

    # print(f"Actual payload length: {len(payload)}, Expected payload length: {expected_length}")

    if len(payload) != expected_length:
        # raise ValueError(f"Payload length {len(payload)} does not match expected length {expected_length}")
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    # Remaining part of the payload contains the detected points
    detected_points = []
    points_format = '<H H H H B B'
    points_size = struct.calcsize(points_format)

    for i in range(num_detected_points):
        start_index = units_size + i * points_size
        point_data = payload[start_index:start_index + points_size]

        x, y, z, doppler, snr, noise = struct.unpack(points_format, point_data)

        point = {
            "X": x * xyz_unit,
            "Y": y * xyz_unit,
            "Z": z * xyz_unit,
            "Doppler": doppler * doppler_unit,
            "SNR": snr * snr_unit,
            "Noise": noise * noise_unit
        }

        detected_points.append(point)

    return detected_points
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_range_azimuth_heat_map_major(payload, num_range_bins, num_azimuth_bins):
    expected_length = 4 * num_range_bins * num_azimuth_bins

    print(f"Actual payload length: {len(payload)}, Expected payload length: {expected_length}")

    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    # Initialize an empty heatmap matrix
    heatmap = []

    # Iterate through the payload to extract each value
    for range_index in range(num_range_bins):
        row = []
        for azimuth_index in range(num_azimuth_bins):
            start_index = (range_index * num_azimuth_bins + azimuth_index) * 4
            value_bytes = payload[start_index:start_index + 4]
            magnitude = struct.unpack('<I', value_bytes)[0]
            row.append(magnitude)
        heatmap.append(row)

    return heatmap
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_range_azimuth_heat_map_minor(payload, num_range_bins, num_azimuth_bins):
    expected_length = 4 * num_range_bins * num_azimuth_bins

    print(f"Actual payload length: {len(payload)}, Expected payload length: {expected_length}")

    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    # Initialize an empty heatmap matrix
    heatmap = []

    # Iterate through the payload to extract each value
    for range_index in range(num_range_bins):
        row = []
        for azimuth_index in range(num_azimuth_bins):
            start_index = (range_index * num_azimuth_bins + azimuth_index) * 4
            value_bytes = payload[start_index:start_index + 4]
            magnitude = struct.unpack('<I', value_bytes)[0]
            row.append(magnitude)
        heatmap.append(row)

    return heatmap
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_statistics_performance(payload):
    expected_length = 24
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    # Unpack the payload using struct.unpack
    inter_frame_processing_time = struct.unpack('<I', payload[0:4])[0]  # uint32_t (4 bytes)
    transmit_output_time = struct.unpack('<I', payload[4:8])[0]  # uint32_t (4 bytes)

    # Extract power measured values (4 x uint16_t = 8 bytes)
    power_measured = []
    for i in range(4):
        index = 8 + i * 2
        power_measured.append(struct.unpack('<H', payload[index:index + 2])[0])

    # Extract temperature readings (4 x uint16_t = 8 bytes)
    temp_reading = []
    for i in range(4):
        index = 16 + i * 2
        temp_reading.append(struct.unpack('<H', payload[index:index + 2])[0])

    statistics = {
        "interFrameProcessingTime_usec": inter_frame_processing_time,
        "transmitOutputTime_usec": transmit_output_time,
        "powerMeasured_uW": power_measured,
        "tempReading_C": temp_reading
    }

    return statistics
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_micro_doppler_raw_data(payload, num_tracked_objects, num_doppler_bins):
    expected_length = num_tracked_objects * num_doppler_bins * 4  # Each value is a float (4 bytes)

    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    micro_doppler_data = []

    # Iterate through the payload to extract micro-Doppler spectra for each tracked object
    index = 0
    for target_index in range(num_tracked_objects):
        spectrum = []
        for doppler_index in range(num_doppler_bins):
            value_bytes = payload[index:index + 4]
            doppler_value = struct.unpack('<f', value_bytes)[0]  # Unpack as float
            spectrum.append(doppler_value)
            index += 4  # Move to the next float value
        micro_doppler_data.append(spectrum)

    return micro_doppler_data
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_micro_doppler_features(payload, num_tracked_objects, num_features):
    expected_length = num_tracked_objects * num_features * 4  # Each value is a float (4 bytes)

    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    micro_doppler_features = []

    # Iterate through the payload to extract micro-Doppler features for each tracked object
    index = 0
    for target_index in range(num_tracked_objects):
        feature_set = []
        for feature_index in range(num_features):
            value_bytes = payload[index:index + 4]
            feature_value = struct.unpack('<f', value_bytes)[0]  # Unpack as float
            feature_set.append(feature_value)
            index += 4  # Move to the next float value
        micro_doppler_features.append(feature_set)

    return micro_doppler_features
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_radar_cube_major(payload, num_range_bins, num_doppler_bins, num_antennas):
    expected_length = num_range_bins * num_doppler_bins * num_antennas * 4  # Each value is a float (4 bytes)

    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    radar_cube = []

    # Iterate through the payload to extract radar cube data
    index = 0
    for antenna_index in range(num_antennas):
        antenna_data = []
        for doppler_index in range(num_doppler_bins):
            doppler_data = []
            for range_index in range(num_range_bins):
                value_bytes = payload[index:index + 4]
                radar_value = struct.unpack('<f', value_bytes)[0]  # Unpack as float
                doppler_data.append(radar_value)
                index += 4  # Move to the next float value
            antenna_data.append(doppler_data)
        radar_cube.append(antenna_data)

    return radar_cube
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_radar_cube_minor(payload, num_range_bins, num_doppler_bins, num_antennas):
    expected_length = num_range_bins * num_doppler_bins * num_antennas * 4  # Each value is a float (4 bytes)

    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    radar_cube = []

    # Iterate through the payload to extract radar cube data
    index = 0
    for antenna_index in range(num_antennas):
        antenna_data = []
        for doppler_index in range(num_doppler_bins):
            doppler_data = []
            for range_index in range(num_range_bins):
                value_bytes = payload[index:index + 4]
                radar_value = struct.unpack('<f', value_bytes)[0]  # Unpack as float
                doppler_data.append(radar_value)
                index += 4  # Move to the next float value
            antenna_data.append(doppler_data)
        radar_cube.append(antenna_data)

    return radar_cube
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_enhanced_presence_indication(payload, num_zones):
    bytes_required = (num_zones + 3) // 4  # Ceiling function of NumberOfZones/4
    if len(payload) != bytes_required:
        logging.error(f"Payload length {len(payload)} does not match expected length {bytes_required}")
        return None  # Return None or an empty list based on your error handling strategy

    presence_indications = []

    for byte in payload:
        for i in range(4):
            zone_index = len(presence_indications)
            if zone_index >= num_zones:
                break
            # Extract 2 bits for the zone
            presence_value = (byte >> (2 * i)) & 0b11
            presence_indications.append(presence_value)

    return presence_indications
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_adc_samples(payload, num_adc_samples, num_rx_channels, num_tx_channels):
    expected_length = num_adc_samples * num_rx_channels * num_tx_channels * 4
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    adc_data = []

    for i in range(num_adc_samples):
        adc_sample = []
        for rx_channel in range(num_rx_channels):
            tx_samples = []
            for tx_channel in range(num_tx_channels):
                start_index = (i * num_rx_channels * num_tx_channels + rx_channel * num_tx_channels + tx_channel) * 4
                # Extract 4 bytes for the ADC sample
                adc_value = int.from_bytes(payload[start_index:start_index + 4], byteorder='little', signed=True)
                tx_samples.append(adc_value)
            adc_sample.append(tx_samples)
        adc_data.append(adc_sample)

    return adc_data
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_classifier_info(payload, num_tracked_objects, num_classes):
    expected_length = num_tracked_objects * num_classes
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    classifier_info = []

    for i in range(num_tracked_objects):
        class_outcomes = []
        for j in range(num_classes):
            index = i * num_classes + j
            class_outcome = payload[index]
            class_outcomes.append(class_outcome)
        classifier_info.append(class_outcomes)

    return classifier_info
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_rx_chan_compensation_info(payload, num_tx_antennas, num_rx_channels):
    expected_length = 4 + (4 * (2 * num_tx_antennas * num_rx_channels))
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    offset = 0

    # First 4 bytes are for some additional info or parameters, assuming it's not coefficients
    additional_info = payload[offset:offset + 4]
    offset += 4

    # Initialize an empty list to hold the compensation coefficients
    rx_chan_compensation_coeffs = []

    # Iterate over each TX antenna and RX channel combination
    for tx_index in range(num_tx_antennas):
        tx_coeffs = []
        for rx_index in range(num_rx_channels):
            # Extract the compensation coefficient in Q20 format
            compensation_coeff = struct.unpack('<i', payload[offset:offset + 4])[0]
            tx_coeffs.append(compensation_coeff)
            offset += 4
        rx_chan_compensation_coeffs.append(tx_coeffs)

    return rx_chan_compensation_coeffs
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_spherical_points(payload, num_points):
    expected_length = num_points * 16
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    points = []

    for i in range(num_points):
        start_index = i * 16

        # Extract each element from the payload
        range_m = struct.unpack('<f', payload[start_index:start_index + 4])[0]
        azimuth_rad = struct.unpack('<f', payload[start_index + 4:start_index + 8])[0]
        elevation_rad = struct.unpack('<f', payload[start_index + 8:start_index + 12])[0]
        doppler_ms = struct.unpack('<f', payload[start_index + 12:start_index + 16])[0]

        point = {
            "Range": range_m,
            "Azimuth": azimuth_rad,
            "Elevation": elevation_rad,
            "Doppler": doppler_ms
        }
        points.append(point)

    return points
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_3d_target_list_xWR6843(payload, num_targets):
    expected_length = num_targets * 112
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    targets = []

    for i in range(num_targets):
        start_index = i * 112

        tid = struct.unpack('<I', payload[start_index:start_index + 4])[0]
        posX = struct.unpack('<f', payload[start_index + 4:start_index + 8])[0]
        posY = struct.unpack('<f', payload[start_index + 8:start_index + 12])[0]
        posZ = struct.unpack('<f', payload[start_index + 12:start_index + 16])[0]
        velX = struct.unpack('<f', payload[start_index + 16:start_index + 20])[0]
        velY = struct.unpack('<f', payload[start_index + 20:start_index + 24])[0]
        velZ = struct.unpack('<f', payload[start_index + 24:start_index + 28])[0]
        accX = struct.unpack('<f', payload[start_index + 28:start_index + 32])[0]
        accY = struct.unpack('<f', payload[start_index + 32:start_index + 36])[0]
        accZ = struct.unpack('<f', payload[start_index + 36:start_index + 40])[0]
        ec = struct.unpack('<16f', payload[start_index + 40:start_index + 104])
        g = struct.unpack('<f', payload[start_index + 104:start_index + 108])[0]
        confidenceLevel = struct.unpack('<f', payload[start_index + 108:start_index + 112])[0]

        target = {
            "TrackID": tid,
            "Position": (posX, posY, posZ),
            "Velocity": (velX, velY, velZ),
            "Acceleration": (accX, accY, accZ),
            "ErrorCovariance": ec,
            "GatingFunctionGain": g,
            "ConfidenceLevel": confidenceLevel
        }
        targets.append(target)

    return targets
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_3d_target_list_xWRLx432(payload, num_targets):
    expected_length = num_targets * 112
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    targets = []

    for i in range(num_targets):
        start_index = i * 112

        tid = struct.unpack('<I', payload[start_index:start_index + 4])[0]
        posX = struct.unpack('<f', payload[start_index + 4:start_index + 8])[0]
        posY = struct.unpack('<f', payload[start_index + 8:start_index + 12])[0]
        posZ = struct.unpack('<f', payload[start_index + 12:start_index + 16])[0]
        velX = struct.unpack('<f', payload[start_index + 16:start_index + 20])[0]
        velY = struct.unpack('<f', payload[start_index + 20:start_index + 24])[0]
        velZ = struct.unpack('<f', payload[start_index + 24:start_index + 28])[0]
        accX = struct.unpack('<f', payload[start_index + 28:start_index + 32])[0]
        accY = struct.unpack('<f', payload[start_index + 32:start_index + 36])[0]
        accZ = struct.unpack('<f', payload[start_index + 36:start_index + 40])[0]
        ec = struct.unpack('<16f', payload[start_index + 40:start_index + 104])
        g = struct.unpack('<f', payload[start_index + 104:start_index + 108])[0]
        confidenceLevel = struct.unpack('<f', payload[start_index + 108:start_index + 112])[0]

        target = {
            "TrackID": tid,
            "Position": (posX, posY, posZ),
            "Velocity": (velX, velY, velZ),
            "Acceleration": (accX, accY, accZ),
            "ErrorCovariance": ec,
            "GatingFunctionGain": g,
            "ConfidenceLevel": confidenceLevel
        }
        targets.append(target)

    return targets
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_target_index_xWR6843(payload, num_points):
    if len(payload) != num_points:
        logging.error(f"Payload length {len(payload)} does not match expected length {num_points}")
        return None  # Return None or an empty list based on your error handling strategy

    target_indices = list(payload)  # Assuming payload is bytes or bytearray
    return target_indices
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_target_index_xWRLx432(payload, num_points):
    if len(payload) != num_points:
        logging.error(f"Payload length {len(payload)} does not match expected length {num_points}")
        return None  # Return None or an empty list based on your error handling strategy

    target_indices = list(payload)  # Assuming payload is bytes or bytearray
    return target_indices
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_target_height(payload, num_points):
    expected_length = num_points * 12
    if len(payload) != expected_length:
        logging.error(f"Payload length {len(payload)} does not match expected length {expected_length}")
        return None  # Return None or an empty list based on your error handling strategy

    targets = []

    for i in range(num_points):
        start_index = i * 12

        targetID = struct.unpack('<I', payload[start_index:start_index + 4])[0]
        maxZ = struct.unpack('<f', payload[start_index + 4:start_index + 8])[0]
        minZ = struct.unpack('<f', payload[start_index + 8:start_index + 12])[0]

        target = {
            "TargetID": targetID,
            "MaxZ": maxZ,
            "MinZ": minZ
        }
        targets.append(target)

    return targets
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_compressed_points(payload):
    if len(payload) < 20:
        logging.error(f"Payload length is less than the minimum expected length (20 bytes)")
        return None  # Return None or an empty list based on your error handling strategy

    # Unpack the first part of the payload which contains unit values
    elevationUnit = struct.unpack('<f', payload[0:4])[0]
    azimuthUnit = struct.unpack('<f', payload[4:8])[0]
    dopplerUnit = struct.unpack('<f', payload[8:12])[0]
    rangeUnit = struct.unpack('<f', payload[12:16])[0]
    snrUnit = struct.unpack('<f', payload[16:20])[0]

    # Calculate number of points based on remaining payload length and point struct size
    num_points = (len(payload) - 20) // 8

    points = []

    # Unpack each point from the payload
    for i in range(num_points):
        start_index = 20 + i * 8

        elevation = struct.unpack('<b', payload[start_index:start_index + 1])[0]  # int8
        azimuth = struct.unpack('<b', payload[start_index + 1:start_index + 2])[0]  # int8
        doppler = struct.unpack('<h', payload[start_index + 2:start_index + 4])[0]  # int16
        range_val = struct.unpack('<H', payload[start_index + 4:start_index + 6])[0]  # uint16
        snr = struct.unpack('<H', payload[start_index + 6:start_index + 8])[0]  # uint16

        point = {
            "Elevation": elevation * elevationUnit,
            "Azimuth": azimuth * azimuthUnit,
            "Doppler": doppler * dopplerUnit,
            "Range": range_val * rangeUnit,
            "SNR": snr * snrUnit
        }
        points.append(point)

    return points
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_presence_indication(payload):
    if len(payload) != 4:
        logging.error(f"Payload length is not 4 bytes as expected")
        return None

    presence_detected = struct.unpack('<I', payload)[0]
    return presence_detected
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_occupancy_state_machine(payload):
    if len(payload) != 4:
        # raise ValueError("Payload length is not 4 bytes as expected.")
        logging.error(f"Payload length is not 4 bytes as expected")
        return None

    occupancy_mask = struct.unpack('<I', payload)[0]
    return occupancy_mask
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_surface_classification_probability(payload):
    if len(payload) != 4:
        # raise ValueError("Payload length is not 4 bytes as expected.")
        logging.error(f"Payload length is not 4 bytes as expected")
        return None

    probability = struct.unpack('<f', payload)[0]
    return probability
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_gesture_features(payload):
    if len(payload) != 40:
        # raise ValueError("Payload length is not 40 bytes as expected.")
        logging.error(f"Payload length is not 4 bytes as expected")
        return None

    # Unpack the payload according to the specified format
    (weighted_doppler,
     weighted_positive_doppler,
     weighted_negative_doppler,
     weighted_range,
     num_points,
     weighted_azimuth_mean,
     weighted_elevation_mean,
     azimuth_doppler_correlation,
     weighted_azimuth_dispersion,
     weighted_elevation_dispersion) = struct.unpack('<10f', payload)

    # Create a dictionary to store the parsed features
    gesture_features = {
        "Weighted Doppler": weighted_doppler,
        "Weighted Positive Doppler": weighted_positive_doppler,
        "Weighted Negative Doppler": weighted_negative_doppler,
        "Weighted Range": weighted_range,
        "Number of Points": num_points,
        "Weighted Azimuth Mean": weighted_azimuth_mean,
        "Weighted Elevation Mean": weighted_elevation_mean,
        "Azimuth-Doppler Correlation": azimuth_doppler_correlation,
        "Weighted Azimuth Dispersion": weighted_azimuth_dispersion,
        "Weighted Elevation Dispersion": weighted_elevation_dispersion
    }

    return gesture_features
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_neural_network_output(payload):
    if len(payload) != 40:
        # raise ValueError("Payload length is not 40 bytes as expected.")
        logging.error(f"Payload length is not 40 bytes as expected.")
        return None

    # Unpack the payload according to the specified format
    (prob_no_gesture,
     prob_gesture_1,
     prob_gesture_2,
     prob_gesture_3,
     prob_gesture_4,
     prob_gesture_5,
     prob_gesture_6,
     prob_gesture_7,
     prob_gesture_8,
     prob_gesture_9) = struct.unpack('<10f', payload)

    # Create a dictionary to store the parsed probabilities
    neural_network_output = {
        "Probability No Gesture": prob_no_gesture,
        "Probability Gesture 1": prob_gesture_1,
        "Probability Gesture 2": prob_gesture_2,
        "Probability Gesture 3": prob_gesture_3,
        "Probability Gesture 4": prob_gesture_4,
        "Probability Gesture 5": prob_gesture_5,
        "Probability Gesture 6": prob_gesture_6,
        "Probability Gesture 7": prob_gesture_7,
        "Probability Gesture 8": prob_gesture_8,
        "Probability Gesture 9": prob_gesture_9
    }

    return neural_network_output
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def parse_dashcam_trigger_output(payload):
    if len(payload) != 16:
        # raise ValueError("Payload length is not 16 bytes as expected.")
        logging.error(f"Payload length is not 16 bytes as expected.")
        return None

    # Unpack the payload according to the specified format
    tracks_active, tracks_triggering_cam, tracks_within_mon_range, tracks_within_trigger_range = struct.unpack('<4I', payload)

    # Create a dictionary to store the parsed values
    dashcam_trigger_output = {
        "Tracks Active": tracks_active,
        "Tracks Triggering Cam": tracks_triggering_cam,
        "Tracks Within Mon Range": tracks_within_mon_range,
        "Tracks Within Trigger Range": tracks_within_trigger_range
    }

    return dashcam_trigger_output
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~