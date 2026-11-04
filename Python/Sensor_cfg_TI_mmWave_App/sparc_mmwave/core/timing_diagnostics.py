"""Configuration-derived timing metrics for standard TI mmWave frameCfg.

All durations are derived from parsed profileCfg/frameCfg/chirpCfg values.
RF-on values are timing estimates, not measurements of PA enable timing.
"""


def _positive_number(params, key):
    try:
        value = float((params or {}).get(key, 0) or 0)
        return value if value > 0 else 0.0
    except (TypeError, ValueError):
        return 0.0



def parse_standard_frame_cfg(arguments):
    """Parse the seven standard frameCfg arguments (excluding command name)."""
    if isinstance(arguments, str):
        fields = arguments.split()
    else:
        fields = list(arguments)
    if len(fields) < 5:
        raise ValueError("frameCfg requires at least five arguments")
    integer_fields = []
    for index, label in enumerate(("chirpStartIdx", "chirpEndIdx", "numLoops", "numFrames")):
        value = float(fields[index])
        if not value.is_integer():
            raise ValueError(f"frameCfg {label} must be an integer")
        integer_fields.append(int(value))
    start_idx, end_idx, loops, frames = integer_fields
    period_ms = float(fields[4])
    if start_idx < 0 or end_idx < start_idx or loops < 1 or period_ms <= 0:
        raise ValueError("Invalid standard frameCfg values")
    return {
        "chirp_start_idx": start_idx,
        "chirp_end_idx": end_idx,
        "chirps_per_loop": end_idx - start_idx + 1,
        "num_loops": loops,
        "chirps_per_frame": (end_idx - start_idx + 1) * loops,
        "num_frames": frames,
        "frame_period_ms": period_ms,
    }


def calculate_timing_metrics(params):
    """Calculate standard-frame timing and duty metrics.

    ``Chirp Cycle Time [us]`` must be idleTime + rampEndTime for the selected
    profile. ``Number of Chirps in Frame`` must be
    (chirpEndIdx - chirpStartIdx + 1) * numLoops from standard frameCfg.
    """
    p = params or {}
    frame_ms = _positive_number(p, "Frame Periodicity [ms]")
    chirp_us = _positive_number(p, "Chirp Cycle Time [us]")
    chirps_value = _positive_number(p, "Number of Chirps in Frame")
    ramp_us = _positive_number(p, "Ramp End Time [us]")
    adc_time_us = _positive_number(p, "ADC Sampling Time [us]")
    if not adc_time_us:
        sample_rate_ksps = _positive_number(p, "Sample Rate [KHz]")
        samples = _positive_number(p, "Number of Samples per Chirp")
        if sample_rate_ksps and samples:
            adc_time_us = samples / sample_rate_ksps * 1000.0

    chirps = int(chirps_value)
    active_ms = chirps * chirp_us / 1000.0 if chirps and chirp_us else 0.0
    idle_ms = frame_ms - active_ms if frame_ms and active_ms else 0.0
    utilization = active_ms / frame_ms * 100.0 if frame_ms and active_ms else 0.0
    chirp_rf_duty = ramp_us / chirp_us * 100.0 if ramp_us and chirp_us else 0.0
    adc_duty = adc_time_us / chirp_us * 100.0 if adc_time_us and chirp_us else 0.0

    # Aggregate ramp-time occupancy across all scheduled chirps. This is the
    # union-time estimate for sequential chirps, not the sum of simultaneous
    # PA activity and not a measured transmitter-enable duty cycle.
    estimated_rf_duty = chirps * ramp_us / (frame_ms * 1000.0) * 100.0 if frame_ms and chirps and ramp_us else 0.0

    tx_counts = p.get("TX Chirps per Frame", {}) or {}
    tx_duty = {}
    if frame_ms and ramp_us and isinstance(tx_counts, dict):
        for tx_index in (0, 1, 2):
            try:
                count = max(int(tx_counts.get(tx_index, tx_counts.get(str(tx_index), 0)) or 0), 0)
            except (TypeError, ValueError):
                count = 0
            tx_duty[f"tx{tx_index + 1}_duty_pct"] = count * ramp_us / (frame_ms * 1000.0) * 100.0
    else:
        tx_duty = {f"tx{i}_duty_pct": 0.0 for i in (1, 2, 3)}

    return {
        "frame_period_ms": frame_ms,
        "configured_fps": 1000.0 / frame_ms if frame_ms else 0.0,
        "chirp_cycle_us": chirp_us,
        "ramp_duration_us": ramp_us,
        "chirp_rf_duty_pct": chirp_rf_duty,
        "adc_acquisition_us": adc_time_us,
        "adc_duty_pct": adc_duty,
        "chirps_per_frame": chirps,
        "active_frame_ms": active_ms,
        "idle_time_ms": idle_ms,
        "frame_utilization_pct": utilization,
        "estimated_rf_duty_pct": estimated_rf_duty,
        "frame_overrun": bool(frame_ms and active_ms > frame_ms),
        **tx_duty,
    }


def calculate_chirps_per_tx_cpi(tx_chirp_counts, chirps_per_frame, num_loops, waveform_multiplexing):
    """Return chirps in one Doppler CPI for the selected waveform.

    For TDM-MIMO, use the largest number of scheduled chirps assigned to any
    TX. For phased-array operation, all frame chirps contribute to the CPI.
    If chirpCfg masks are unavailable, use the conventional one-chirp-per-TX
    per-loop fallback for TDM, or all frame chirps for phased-array operation.
    """
    counts = tx_chirp_counts or {}
    positive = []
    for value in counts.values():
        try:
            count = int(value)
        except (TypeError, ValueError):
            continue
        if count > 0:
            positive.append(count)
    if positive:
        return max(positive)
    if waveform_multiplexing == "Phased-Array":
        return max(int(chirps_per_frame or 0), 0)
    return max(int(num_loops or 0), 0)
