from pathlib import Path


def test_bandwidth_limit_validation_and_visual_warning_are_wired_into_ui():
    source = Path('sparc_mmwave/ui/legacy_window.py').read_text(encoding='utf-8')
    assert 'def _maximum_device_bandwidth_mhz(self):' in source
    assert 'def _bandwidth_limit_status(self, show_warning=False):' in source
    assert 'for column in range(table.columnCount())' in source
    assert 'background-color: #c62828' in source and 'table.setCellWidget(row, column, label)' in source
    assert 'Reduce Frequency Slope to at most' in source
    assert 'Reduce Ramp End Time to at most' in source
    assert 'self._bandwidth_limit_status(show_warning=True)' in source
    assert 'self._bandwidth_limit_status(show_warning=False)' in source


def test_rf_bandwidth_limits_are_defined_for_supported_evm_profiles():
    source = Path('sparc_mmwave/ui/legacy_window.py').read_text(encoding='utf-8')
    assert '"Maximum RF Bandwidth [MHz]": 4000' in source
    assert '"Maximum RF Bandwidth [MHz]": 5000' in source
