from pathlib import Path

SOURCE = Path(__file__).parents[1] / "sparc_mmwave" / "ui" / "legacy_window.py"


def test_phased_array_uses_one_simultaneous_chirp_for_all_enabled_tx():
    source = SOURCE.read_text(encoding="utf-8")
    assert "(3, 'Phased-Array'): [['chirpCfg', '00000007']]" in source
    assert "(2, 'Phased-Array'): [['chirpCfg', '00000005']]" in source
    assert "['chirpCfg', '11000007']" not in source
    assert "['chirpCfg', '22000007']" not in source


def test_frame_span_tracks_number_of_generated_chirps_and_preserves_loops():
    source = SOURCE.read_text(encoding="utf-8")
    assert "frame_args[1] = str(len(chirp_params) - 1)" in source
    assert "radar_params['Chirp Configurations per Loop'] = len(chirp_params)" in source
    assert "Preserve numLoops and all other frame timing fields." in source


def test_tdm_mimo_still_uses_sequential_one_hot_tx_masks():
    source = SOURCE.read_text(encoding="utf-8")
    assert "(3, 'TDM-MIMO'): [['chirpCfg', '00000001'], ['chirpCfg', '11000004']," in source
    assert "['chirpCfg', '22000002']]" in source
