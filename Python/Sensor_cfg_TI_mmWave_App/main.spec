# -*- mode: python ; coding: utf-8 -*-
from pathlib import Path

project_root = Path(SPECPATH)

a = Analysis(
    [str(project_root / "main.py")],
    pathex=[str(project_root)],
    binaries=[],
    datas=[(str(project_root / "sparc_mmwave" / "resources_icon.png"), "sparc_mmwave")],
    hiddenimports=[
        "sparc_mmwave.core.radar_calculator",
        "sparc_mmwave.processing.payload",
        "sparc_mmwave.visualization.plots",
        "sparc_mmwave.services.radar_application",
        "sparc_mmwave.ui.legacy_window",
        "sparc_mmwave.ui.main_window",
    ],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    noarchive=False,
    optimize=0,
)

pyz = PYZ(a.pure)
exe = EXE(
    pyz, a.scripts, a.binaries, a.datas, [],
    name="SPARC_mmWave_Studio",
    debug=False, bootloader_ignore_signals=False, strip=False, upx=True,
    upx_exclude=[], runtime_tmpdir=None, console=False,
    disable_windowed_traceback=False, argv_emulation=False,
    target_arch=None, codesign_identity=None, entitlements_file=None,
)
