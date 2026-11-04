"""Pre-flight validation for standard TI mmWave CLI configurations.

This validator intentionally distinguishes blocking errors from warnings. It
supports standard profileCfg/chirpCfg/frameCfg operation; advanced-frame
commands are detected and reported as requiring a dedicated timing model.
"""
from dataclasses import dataclass, field

@dataclass
class ValidationReport:
    errors: list[str] = field(default_factory=list)
    warnings: list[str] = field(default_factory=list)
    @property
    def is_valid(self):
        return not self.errors


def validate_commands(commands):
    """Validate iterable of (command, argument-string) pairs."""
    report = ValidationReport()
    parsed = {}
    for name, raw in commands:
        args = str(raw).split()
        parsed.setdefault(str(name).strip(), []).append(args)

    if any(k in parsed for k in ("advFrameCfg", "subFrameCfg", "burstCfg")):
        report.warnings.append(
            "Advanced-frame commands detected. Standard frame timing/duty-cycle checks do not apply; verify this configuration with the device-specific advanced-frame model."
        )

    profiles = {}
    for args in parsed.get("profileCfg", []):
        if len(args) < 14:
            report.errors.append("profileCfg requires at least 14 arguments.")
            continue
        try:
            pid = int(args[0]); idle = float(args[2]); ramp = float(args[4])
            adc_start = float(args[3])
            slope = float(args[7]); samples = int(args[9]); rate = float(args[10])
            if idle < 0 or ramp <= 0 or adc_start < 0 or slope <= 0 or samples <= 0 or rate <= 0:
                report.errors.append(f"profileCfg profile {pid}: timing, slope, sample count and sample rate must be positive (idle may be zero).")
            adc_time = samples / rate * 1000.0  # Ksamples/s => microseconds
            if adc_start + adc_time > ramp + 1e-9:
                report.errors.append(
                    f"profileCfg profile {pid}: ADC window ends at {adc_start + adc_time:.3f} us, beyond rampEndTime {ramp:.3f} us."
                )
            profiles[pid] = args
        except (ValueError, IndexError):
            report.errors.append("profileCfg contains a non-numeric or missing required field.")

    chirps = {}
    for args in parsed.get("chirpCfg", []):
        if len(args) < 8:
            report.errors.append("chirpCfg requires 8 arguments.")
            continue
        try:
            first, last, pid = int(args[0]), int(args[1]), int(args[2])
            tx_mask = int(args[7], 10)
            if first < 0 or last < first or tx_mask < 0:
                report.errors.append(f"chirpCfg {first}-{last}: invalid chirp indices or TX mask.")
                continue
            if pid not in profiles:
                report.errors.append(f"chirpCfg {first}-{last}: references profileId {pid}, which has no profileCfg.")
            for idx in range(first, last + 1):
                if idx in chirps:
                    report.warnings.append(f"Chirp index {idx} is defined more than once; later definition will be used.")
                chirps[idx] = (pid, tx_mask)
        except ValueError:
            report.errors.append("chirpCfg contains a non-numeric field.")

    frame_rows = parsed.get("frameCfg", [])
    if frame_rows:
        if len(frame_rows) > 1:
            report.warnings.append("Multiple frameCfg commands found; only the final one is used by the standard-frame timing model.")
        args = frame_rows[-1]
        if len(args) < 5:
            report.errors.append("frameCfg requires at least 5 arguments.")
        else:
            try:
                start, end, loops = int(args[0]), int(args[1]), int(args[2])
                period_ms = float(args[4])
                if start < 0 or end < start or loops <= 0 or period_ms <= 0:
                    report.errors.append("frameCfg: chirp indices, loop count or frame periodicity are invalid.")
                missing = [i for i in range(start, end + 1) if i not in chirps]
                if missing:
                    report.errors.append("frameCfg references undefined chirpCfg indices: " + ", ".join(map(str, missing)))
                elif profiles:
                    used_profiles = {chirps[i][0] for i in range(start, end + 1)}
                    if len(used_profiles) > 1:
                        report.warnings.append("Frame uses multiple profileCfg IDs. The simple single-profile timing estimate is not valid for this frame.")
                    else:
                        pid = next(iter(used_profiles))
                        p = profiles[pid]
                        chirp_interval = float(p[2]) + float(p[4])
                        chirps_per_frame = (end - start + 1) * loops
                        active_ms = chirps_per_frame * chirp_interval / 1000.0
                        if active_ms > period_ms:
                            report.errors.append(f"frameCfg overrun: estimated active chirp time {active_ms:.3f} ms exceeds frame period {period_ms:.3f} ms.")
            except (ValueError, IndexError):
                report.errors.append("frameCfg contains a non-numeric or missing required field.")

    gui_rows = parsed.get("guiMonitor", [])
    if gui_rows:
        args = gui_rows[-1]
        if len(args) < 7:
            report.errors.append("guiMonitor requires subFrameIdx and six output-enable flags.")
        else:
            for label, index in (("Range-Azimuth heatmap", 4), ("Range-Doppler heatmap", 5)):
                if args[index] not in ("0", "1"):
                    report.errors.append(f"guiMonitor {label} enable flag must be 0 or 1.")
    else:
        report.warnings.append("No guiMonitor command found; expected output TLVs may not be transmitted.")

    if not parsed.get("frameCfg") and not any(k in parsed for k in ("advFrameCfg", "subFrameCfg")):
        report.errors.append("No standard frameCfg or advanced-frame configuration found.")
    return report
