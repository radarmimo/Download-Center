import unittest
import numpy as np
from types import SimpleNamespace
from sparc_mmwave.processing.payload import RadarDataParser

class HeatmapParserTests(unittest.TestCase):
    def test_range_doppler_uses_per_tx_chirp_count(self):
        params = {
            "Number of Range FFT Bins": 4,
            "Number of Chirps in Loop": 2,
            "Number of Loops": 16,
            "Number of Chirps in Frame": 32,
            "Waveform Multiplexing": "TDM-MIMO",
            "TX Chirps per Frame": {0: 16, 1: 16, 2: 0},
        }
        parser = RadarDataParser()
        parsed = parser.parse_range_doppler_heatmap(bytes(4 * 16 * 2), SimpleNamespace(radar_params=params))
        self.assertEqual(np.asarray(parsed).shape, (4, 16))

    def test_range_doppler_rejects_wrong_payload_length(self):
        params = {"Number of Range FFT Bins": 4, "Waveform Multiplexing": "Phased-Array", "Number of Chirps in Frame": 8}
        self.assertIsNone(RadarDataParser().parse_range_doppler_heatmap(bytes(4), SimpleNamespace(radar_params=params)))

    def test_azimuth_parser_uses_range_fft_bins(self):
        params = {"Number of Range FFT Bins": 4, "Number of Samples per Chirp": 3, "Length of Virtual Array": 2}
        parsed = RadarDataParser().parse_azimuth_static_heatmap(bytes(4 * 2 * 4), SimpleNamespace(radar_params=params))
        self.assertEqual(np.asarray(parsed).shape, (4, 2))

if __name__ == "__main__":
    unittest.main()
