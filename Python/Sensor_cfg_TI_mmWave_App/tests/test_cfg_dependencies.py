import unittest

from sparc_mmwave.core.radar_calculator import RadarCalculator


class CfgDependencyTests(unittest.TestCase):
    def setUp(self):
        self.calculator = RadarCalculator()

    def test_sample_rate_recalculates_range_metrics(self):
        baseline = self.calculator.calculate_profile_metrics(
            freq_slope_MHz_us=70.0, sample_rate_KHz=5209, samples_per_chirp=256,
            ramp_end_time_us=80.0, adc_start_time_us=7.0
        )
        changed = self.calculator.calculate_profile_metrics(
            freq_slope_MHz_us=70.0, sample_rate_KHz=4000, samples_per_chirp=256,
            ramp_end_time_us=80.0, adc_start_time_us=7.0
        )
        # Sample rate changes the usable beat-frequency/range limit, but not
        # the transmitted sweep bandwidth when rampEndTime is unchanged.
        self.assertEqual(baseline["Bandwidth [MHz]"], changed["Bandwidth [MHz]"])
        self.assertEqual(baseline["Range Resolution [m]"], changed["Range Resolution [m]"])
        self.assertNotEqual(baseline["Maximum Range [m]"], changed["Maximum Range [m]"])
        self.assertNotEqual(baseline["Unambiguous Range [m]"], changed["Unambiguous Range [m]"])

    def test_slope_recalculates_bandwidth_and_range(self):
        baseline = self.calculator.calculate_profile_metrics(70.0, 5209, 256, 80.0, 7.0)
        changed = self.calculator.calculate_profile_metrics(60.0, 5209, 256, 80.0, 7.0)
        self.assertNotEqual(baseline["Bandwidth [MHz]"], changed["Bandwidth [MHz]"])
        self.assertNotEqual(baseline["Range Resolution [m]"], changed["Range Resolution [m]"])
        self.assertNotEqual(baseline["Unambiguous Range [m]"], changed["Unambiguous Range [m]"])

    def test_adc_window_must_fit_inside_ramp(self):
        with self.assertRaises(ValueError):
            self.calculator.calculate_profile_metrics(
                70.0, 5209.0, 256, ramp_end_time_us=40.0, adc_start_time_us=7.0
            )

    def test_invalid_profile_values_are_rejected(self):
        for values in ((0, 5209, 256), (70, 0, 256), (70, 5209, 0)):
            with self.subTest(values=values):
                with self.assertRaises(ValueError):
                    self.calculator.calculate_profile_metrics(*values, ramp_end_time_us=80.0, adc_start_time_us=7.0)


if __name__ == "__main__":
    unittest.main()
