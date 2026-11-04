from pathlib import Path


def test_bandwidth_warning_is_reapplied_after_recalculation_highlight():
    source = Path('sparc_mmwave/ui/legacy_window.py').read_text(encoding='utf-8')
    generic = source.index('self.highlight_recalculated_parameters(')
    reapply = source.index('self._bandwidth_limit_status(show_warning=False)', generic)
    refresh = source.index('if hasattr(self, "_refresh_dashboard"):', generic)
    assert generic < reapply < refresh


def test_bandwidth_limit_highlights_entire_scene_parameter_row():
    source = Path('sparc_mmwave/ui/legacy_window.py').read_text(encoding='utf-8')
    method_start = source.index('def _bandwidth_limit_status(')
    method_end = source.index('\n    def handle_cfg_update', method_start)
    method = source[method_start:method_end]
    assert 'for column in range(table.columnCount())' in method
    assert 'background-color: #c62828' in method
    assert 'table.viewport().update()' in method
