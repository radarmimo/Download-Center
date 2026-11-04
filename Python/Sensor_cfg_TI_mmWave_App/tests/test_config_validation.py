import unittest
from sparc_mmwave.core.config_validation import validate_commands

BASE = [
    ("profileCfg", "0 60 567 7 57.14 0 0 70 1 256 5209 0 0 158"),
    ("chirpCfg", "0 0 0 0 0 0 0 1"),
    ("chirpCfg", "1 1 0 0 0 0 0 4"),
    ("frameCfg", "0 1 16 0 100 1 0"),
    ("guiMonitor", "-1 1 1 0 1 1 1"),
]

class ConfigurationValidationTests(unittest.TestCase):
    def test_valid_standard_configuration(self):
        self.assertTrue(validate_commands(BASE).is_valid)

    def test_detects_adc_window_beyond_ramp(self):
        commands = list(BASE)
        commands[0] = ("profileCfg", "0 60 567 20 57.14 0 0 70 1 256 5209 0 0 158")
        self.assertFalse(validate_commands(commands).is_valid)

    def test_detects_undefined_chirp_index(self):
        commands = list(BASE)
        commands[3] = ("frameCfg", "0 2 16 0 100 1 0")
        self.assertFalse(validate_commands(commands).is_valid)

    def test_detects_frame_overrun(self):
        commands = list(BASE)
        commands[3] = ("frameCfg", "0 1 100 0 1 1 0")
        self.assertFalse(validate_commands(commands).is_valid)

    def test_advanced_frame_is_flagged(self):
        report = validate_commands(BASE + [("advFrameCfg", "0 1 0 0 0 0 0")])
        self.assertTrue(any("Advanced-frame" in w for w in report.warnings))

    def test_heatmap_flags_are_validated(self):
        commands = list(BASE)
        commands[-1] = ("guiMonitor", "-1 1 1 0 2 0 1")
        self.assertFalse(validate_commands(commands).is_valid)

if __name__ == "__main__":
    unittest.main()
