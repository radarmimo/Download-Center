"""Regression test: every displayed profileCfg input must be wired to profileCfg."""
import ast
from pathlib import Path


def _source_path():
    return Path(__file__).resolve().parents[1] / "sparc_mmwave" / "ui" / "legacy_window.py"


def test_ramp_end_time_is_mapped_to_profile_cfg():
    tree = ast.parse(_source_path().read_text(encoding="utf-8"))
    for node in ast.walk(tree):
        if isinstance(node, ast.FunctionDef) and node.name == "on_chirp_cfg_table_cell_changed":
            for child in ast.walk(node):
                if isinstance(child, ast.Assign) and any(
                    isinstance(target, ast.Name) and target.id == "command_by_parameter"
                    for target in child.targets
                ) and isinstance(child.value, ast.Dict):
                    mapping = {
                        key.value: value.value
                        for key, value in zip(child.value.keys, child.value.values)
                        if isinstance(key, ast.Constant) and isinstance(value, ast.Constant)
                    }
                    assert mapping.get("Ramp End Time [us]") == "profileCfg"
                    return
    raise AssertionError("Could not find command_by_parameter mapping")


def test_ramp_end_time_is_written_to_profile_cfg_field_four():
    source = _source_path().read_text(encoding="utf-8")
    assert 'self.update_cfg_param(params, radar_params, 4, \'Ramp End Time [us]\'' in source
