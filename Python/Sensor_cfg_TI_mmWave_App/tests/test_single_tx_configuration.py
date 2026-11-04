from pathlib import Path


SOURCE = Path(__file__).parents[1] / "sparc_mmwave" / "ui" / "legacy_window.py"


def test_single_tx_uses_one_active_chirp_for_both_multiplexing_modes():
    source = SOURCE.read_text(encoding="utf-8")
    assert "(1, 'Phased-Array'): [['chirpCfg', '00000001']]" in source
    assert "(1, 'TDM-MIMO'): [['chirpCfg', '00000001']]" in source
    assert "(1, 'TDM-MIMO'): [['chirpCfg', '00000001'], ['chirpCfg', '11000000']]" not in source


def test_single_tx_updates_frame_span_and_preserves_loop_count():
    source = SOURCE.read_text(encoding="utf-8")
    assert "frame_args[0] = '0'" in source
    assert "frame_args[1] = str(len(chirp_params) - 1)" in source
    assert "radar_params['Chirp Configurations per Loop'] = len(chirp_params)" in source
    assert "Preserve numLoops and all other frame timing fields." in source


def test_single_tx_removes_unsupported_bpm_command():
    source = SOURCE.read_text(encoding="utf-8")
    assert "for bpm_row in reversed(self.get_command_rows('bpmCfg'))" in source
