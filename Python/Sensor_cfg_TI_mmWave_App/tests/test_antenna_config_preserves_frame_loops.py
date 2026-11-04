from pathlib import Path


def test_antenna_change_does_not_derive_frame_loops_from_tx_count():
    source_path = (
        Path(__file__).resolve().parents[1]
        / "sparc_mmwave" / "ui" / "legacy_window.py"
    )
    source = source_path.read_text(encoding="utf-8")
    start = source.index("    def on_antenna_confg(")
    end = source.index("    def add_combo_box(", start)
    handler = source[start:end]

    assert 'self.radar_params["Number of Loops"] = num_tx - 1' not in handler
    assert "Do not derive frameCfg.numLoops from the number of TX antennas." in handler
