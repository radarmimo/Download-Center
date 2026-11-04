import unittest

from sparc_mmwave.core.radar_calculator import RadarCalculator


class RangeMetricsAndChirpSpanTests(unittest.TestCase):
    def test_complex_adc_maximum_range_uses_full_sample_rate(self):
        calc = RadarCalculator()
        metrics = calc.calculate_profile_metrics(
            freq_slope_MHz_us=70,
            sample_rate_KHz=5209,
            samples_per_chirp=256,
            ramp_end_time_us=57.14,
            adc_start_time_us=2.5,
            beat_frequency_fraction=0.8,
        )
        expected_max = calc.calculate_unambiguous_range(5.209, 70)
        expected_usable = calc.calculate_unambiguous_range(5.209 * 0.8, 70)
        self.assertEqual(metrics["Maximum Range [m]"], expected_max)
        self.assertEqual(metrics["Unambiguous Range [m]"], expected_usable)
        self.assertGreater(metrics["Maximum Range [m]"], metrics["Unambiguous Range [m]"])

    def test_range_values_are_not_halved_by_real_sample_nyquist_assumption(self):
        calc = RadarCalculator()
        metrics = calc.calculate_profile_metrics(70, 5209, 256, 57.14, 2.5)
        full_fs_range = calc.calculate_unambiguous_range(5.209, 70)
        half_fs_range = calc.calculate_unambiguous_range(5.209 / 2, 70)
        self.assertEqual(metrics["Maximum Range [m]"], full_fs_range)
        self.assertNotEqual(metrics["Maximum Range [m]"], half_fs_range)


if __name__ == "__main__":
    unittest.main()
