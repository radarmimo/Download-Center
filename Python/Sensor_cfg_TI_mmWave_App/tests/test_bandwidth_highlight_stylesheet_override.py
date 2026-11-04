from pathlib import Path


def test_bandwidth_warning_uses_explicit_cell_widgets_to_override_qt_stylesheet():
    source = Path('sparc_mmwave/ui/legacy_window.py').read_text(encoding='utf-8')
    start = source.index('def _bandwidth_limit_status(')
    end = source.index('\n    def handle_cfg_update', start)
    method = source[start:end]
    assert 'label = QLabel(item.text())' in method
    assert 'background-color: #c62828' in method
    assert 'table.setCellWidget(row, column, label)' in method
    assert 'table.removeCellWidget(row, column)' in method
    assert 'old_widget.deleteLater()' in method
