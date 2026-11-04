# SPARC mmWave Radar Studio — Clean package build (Phase 1 + Phase 2)

This release consolidates application source code under the `sparc_mmwave` Python package. There are no duplicate root-level copies of the radar modules.

## Project structure

```text
SPARC_mmWave_Studio/
├── main.py
├── main.spec
├── requirements.txt
├── README.md
├── ARCHITECTURE.md
├── CHANGELOG.md
├── icon.png
└── sparc_mmwave/
    ├── __init__.py
    ├── core/
    │   └── radar_calculator.py
    ├── hardware/
    ├── processing/
    │   └── payload.py
    ├── services/
    │   └── radar_application.py
    ├── ui/
    │   ├── main_window.py
    │   └── legacy_window.py
    ├── visualization/
    │   └── plots.py
    └── resources_icon.png
```

## Installation (Windows)

Use Python 3.10 or a version compatible with the listed packages. From this project root:

```powershell
py -3.10 -m venv .venv
.venv\Scripts\Activate.ps1
python -m pip install --upgrade pip
pip install -r requirements.txt
```

If PowerShell blocks activation, run `.venv\Scripts\activate.bat` from Command Prompt instead.

## Run

Always launch from the project root:

```powershell
python main.py
```

## Package imports

All internal imports use package paths or relative imports. For example:

- `main.py` imports `sparc_mmwave.ui.main_window` and `sparc_mmwave.services.radar_application`.
- `services/radar_application.py` imports the parser and visualizer from sibling package modules.
- `ui/legacy_window.py` imports `RadarCalculator` from `sparc_mmwave.core`.

Do not copy the Python modules back into the project root; that would reintroduce duplicate sources and import ambiguity.

## Features retained from the supplied application

- Existing radar platform selection and configuration presets.
- TI CFG loading/editing and serial command/data port handling.
- Existing radar parameter calculation routines.
- Existing packet/TLV parsing and radar visualizations.
- SPARC-branded dashboard and navigation pages: Overview, Configuration, Live Radar and Diagnostics.

## Validation status

The source has been checked for Python syntax and for remaining imports that refer to removed root-level modules. Actual GUI operation and hardware-in-the-loop testing still need to be performed on the target Windows PC with the required Python dependencies and the relevant TI radar board connected.

The existing radar parser, serial protocol and configuration calculations have not been redesigned in this release. Duty-cycle/advanced timing diagnostics remain a subsequent phase.

## Build with PyInstaller

```powershell
pip install pyinstaller
pyinstaller --noconfirm --clean main.spec
```

Review the generated executable on the target PC; USB serial driver availability and board firmware compatibility remain system-level requirements.


## Live signal plot workspace

The Live Radar page includes a Signal Analysis tab with embedded Range Profile, Range-Doppler, and Range-Azimuth plots. Use each plot's **Pop out** control to move it into a maximized, independently resizable window. Closing that window returns the plot to its original dashboard panel; live updates continue while the plot is detached.

### Automatic sensor stop on application exit

When the application sends `sensorStart`, it records the sensor as running. On normal application close, it sends `sensorStop` through the command UART before disconnecting the serial ports, then stops its background data threads. This is a best-effort graceful shutdown and requires the command UART to remain connected and responsive. If the USB cable is unplugged, the board loses power, or the process is forcibly terminated, software cannot guarantee delivery of the stop command.
