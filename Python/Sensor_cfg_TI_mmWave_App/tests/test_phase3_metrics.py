import time
import unittest

from sparc_mmwave.core.timing_diagnostics import (
    calculate_timing_metrics, parse_standard_frame_cfg, calculate_chirps_per_tx_cpi
)
from sparc_mmwave.services.runtime_statistics import RuntimeStatistics


class TimingMetricsTests(unittest.TestCase):
    def test_frame_timing_and_duty_estimate(self):
        metrics = calculate_timing_metrics({
            "Frame Periodicity [ms]": 100.0,
            "Chirp Cycle Time [us]": 100.0,
            "Number of Chirps in Frame": 64,
            "Ramp End Time [us]": 60.0,
        })
        self.assertAlmostEqual(metrics["active_frame_ms"], 6.4)
        self.assertAlmostEqual(metrics["idle_time_ms"], 93.6)
        self.assertAlmostEqual(metrics["frame_utilization_pct"], 6.4)
        self.assertAlmostEqual(metrics["estimated_rf_duty_pct"], 3.84)
        self.assertAlmostEqual(metrics["configured_fps"], 10.0)

    def test_runtime_statistics_and_frame_gap(self):
        stats = RuntimeStatistics(window_seconds=5.0)
        now = time.monotonic()
        stats.record_frame(100, 1000, now)
        stats.record_frame(101, 1000, now + 0.1)
        stats.record_frame(103, 1200, now + 0.2)
        snapshot = stats.snapshot()
        self.assertEqual(snapshot["frames_received"], 3)
        self.assertEqual(snapshot["missing_frames"], 1)
        self.assertAlmostEqual(snapshot["measured_fps"], 10.0, places=5)
        self.assertGreater(snapshot["throughput_kBps"], 0)

    def test_per_chirp_rf_and_adc_duty_metrics(self):
        metrics = calculate_timing_metrics({
            "Frame Periodicity [ms]": 100.0,
            "Chirp Cycle Time [us]": 624.14,
            "Number of Chirps in Frame": 32,
            "Ramp End Time [us]": 57.14,
            "Sample Rate [KHz]": 5209.0,
            "Number of Samples per Chirp": 256,
        })
        self.assertAlmostEqual(metrics["chirp_rf_duty_pct"], 57.14 / 624.14 * 100.0, places=5)
        self.assertAlmostEqual(metrics["adc_acquisition_us"], 256 / 5209.0 * 1000.0, places=5)
        self.assertAlmostEqual(metrics["adc_duty_pct"], (256 / 5209.0 * 1000.0) / 624.14 * 100.0, places=5)
        self.assertAlmostEqual(metrics["ramp_duration_us"], 57.14)

    def test_frame_cfg_rejects_fractional_integer_fields(self):
        with self.assertRaises(ValueError):
            parse_standard_frame_cfg("0 1 16.5 0 100 1 0")

    def test_chirps_in_loop_preserves_per_tx_cpi_semantics(self):
        # Two chirp indices (two TX slots) x 16 loops = 32 frame chirps,
        # but each TX contributes 16 chirps to its Doppler CPI.
        parsed = parse_standard_frame_cfg("0 1 16 0 100 1 0")
        per_tx = calculate_chirps_per_tx_cpi(
            {0: 16, 1: 16, 2: 0}, parsed["chirps_per_frame"],
            parsed["num_loops"], "TDM-MIMO"
        )
        self.assertEqual(parsed["chirps_per_loop"], 2)  # frameCfg index span
        self.assertEqual(parsed["chirps_per_frame"], 32)
        self.assertEqual(per_tx, 16)  # legacy UI/Doppler CPI meaning

    def test_chirps_per_tx_fallback_without_masks(self):
        self.assertEqual(calculate_chirps_per_tx_cpi({}, 32, 16, "TDM-MIMO"), 16)
        self.assertEqual(calculate_chirps_per_tx_cpi({}, 32, 16, "Phased-Array"), 32)

    def test_standard_frame_cfg_field_interpretation(self):
        # chirpStartIdx=0, chirpEndIdx=1, numLoops=16, numFrames=0,
        # framePeriodicity=100 ms, triggerSelect=1, frameTriggerDelay=0
        parsed = parse_standard_frame_cfg("0 1 16 0 100 1 0")
        self.assertEqual(parsed["chirps_per_loop"], 2)
        self.assertEqual(parsed["num_loops"], 16)
        self.assertEqual(parsed["chirps_per_frame"], 32)
        self.assertEqual(parsed["frame_period_ms"], 100.0)

    def test_per_tx_duty_and_frame_overrun(self):
        metrics = calculate_timing_metrics({
            "Frame Periodicity [ms]": 10.0,
            "Chirp Cycle Time [us]": 100.0,
            "Number of Chirps in Frame": 20,
            "Ramp End Time [us]": 60.0,
            "TX Chirps per Frame": {0: 20, 1: 10, 2: 0},
        })
        self.assertAlmostEqual(metrics["active_frame_ms"], 2.0)
        self.assertAlmostEqual(metrics["estimated_rf_duty_pct"], 12.0)
        self.assertAlmostEqual(metrics["tx1_duty_pct"], 12.0)
        self.assertAlmostEqual(metrics["tx2_duty_pct"], 6.0)
        self.assertAlmostEqual(metrics["tx3_duty_pct"], 0.0)
        self.assertFalse(metrics["frame_overrun"])

    def test_empty_configuration_is_safe(self):
        metrics = calculate_timing_metrics({})
        self.assertEqual(metrics["configured_fps"], 0.0)
        self.assertEqual(metrics["frame_utilization_pct"], 0.0)


if __name__ == "__main__":
    unittest.main()
