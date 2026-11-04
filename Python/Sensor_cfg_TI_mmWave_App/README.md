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

## Phase 3A/3B – Timing and runtime diagnostics

The Overview dashboard now separates configuration-derived timing from live
UART acquisition measurements.

- Configuration-derived: configured frame rate/period, chirp cycle, chirps per
  frame, active frame time, idle time, frame utilization, and estimated
  aggregate RF-active duty.
- Live: measured frame rate, average/minimum/maximum frame interval, interval
  jitter (standard deviation), frame-number discontinuities, and rolling UART
  data throughput.

The RF-active duty value is an estimate based on the configured chirp ramp and
frame timing. It is not a per-transmitter duty-cycle measurement and does not
model TX-enable masks or all device-specific burst scheduling. Live timing is
measured when complete UART packets are assembled, so USB/UART buffering can
influence the observed intervals. Throughput is based on complete received
packet sizes and uses decimal kB/s.

### Live command execution feedback
The Live Radar workspace includes the command execution panel. When a configuration is sent, each command is displayed with a timestamp before transmission, followed by a SENT confirmation after the UART write/flush completes. Any response bytes received from the device and any transmission errors are displayed in the same panel. The progress bar reports the number of commands transmitted. A SENT confirmation indicates successful delivery to the local serial driver, not an acknowledgement that the radar firmware accepted the command; inspect any device response shown in the RX log.

### UX update
Signal plots are now available on the dedicated **Signal Analysis** page, separate from the **Live Radar** operator dashboard. Use **Open full-screen plot viewer** to display all signal plots in a maximized standalone window; closing it returns the plots to Signal Analysis. The default configuration preset is loaded during startup, so **Send configuration & start** is enabled whenever a valid preset or CFG file has populated the command table.

### Point Cloud workspace
The 3D point-cloud view and detected-points tables are available from the dedicated **Point Cloud** page. Use **Open 3D viewer** to move the live 3D view into a maximized standalone window. Closing that window returns the same live view to the Point Cloud page.

## Configuration-first workflow
The first workspace page is **Radar Control**. Its **CFG Editor** tab exposes the existing TI configuration editor, with direct access to load a `.cfg` file and to apply/save edits. Use the **Device Operation** tab for connecting the command/data UART ports, sending the configuration, starting/stopping the sensor, and monitoring command execution. Serial-port selection remains under **Device Setup**. Signal plots and point-cloud views remain separate workspaces.

### Unified configuration and operation workflow
The Radar Control page combines the CFG editor with Connect device, Send configuration & start, and Stop radar controls. Select the command and data UART ports under Device Setup. The detailed command progress and UART transcript are available separately under Diagnostics → Command Log; they are intentionally not shown in the main Radar Control workspace.


### Radar Control workspace
The Radar Control page contains the original editable CFG tables, device connection/start/stop controls, and live command execution progress/log. The CFG editor retains its existing parameter dependency callbacks (for example, sampling-rate changes trigger recalculation of dependent radar parameters). Use the vertical splitter to resize the editor and command log areas.

### UI layout behaviour
The Radar Control workspace keeps the original CFG editor and command execution log in separate resizable regions. The CFG editor is hosted in a scroll area so its tabs, tables and Apply/Save controls remain accessible on shorter displays rather than being compressed into overlapping regions. The command log retains a minimum usable height and expands with the available space.

### Radar Control command tabs
The lower section of Radar Control contains two tabs: **CFG Commands & Save** (generated command table and Save Config action) and **Command Execution Log** (live transmission progress and device transcript). This keeps the command list accessible without taking vertical space from the editable radar-parameter tabs.


### Visualization workspace
Signal plots and point-cloud views are grouped under a single **Visualization** page to reduce main navigation items. The bottom tab strip provides separate views for Range Profile, Range-Doppler, Range-Azimuth, 3D Point Cloud and Detected Points. Individual signal plots retain their pop-out controls, and the 3D viewer remains available as a separate window.

### Global header
The radar platform and configuration preset selectors are integrated into the main application header alongside the SPARC identity and application title. Their existing widgets and selection callbacks are retained.

### Separate visualization window
The **Visualization** item in the bottom navigation opens the complete radar visualization workspace in a separate window. The main Radar Control window remains available for configuration and device operation. Close the visualization window to return to the main application; select Visualization again to reopen it. The signal-analysis tabs, 3D point cloud, detected-points table, and existing individual pop-out controls remain part of that workspace.

### Companion visualization window
The radar visualization workspace opens automatically alongside the main application. It is intentionally kept open for the duration of the session; use the main application's close button to exit, which closes both windows and performs the normal radar shutdown sequence. The Visualization entry is no longer part of the bottom navigation.


### Editable CFG parameter dependencies

The Radar Control Chirp table is editable. Changes to supported profile/frame parameters are propagated to the generated TI command table and the full CFG is reparsed to refresh dependent Scene Parameters. In particular, changing ADC sample rate, samples per chirp, or frequency slope recalculates bandwidth, range resolution, beat frequency, maximum range, and unambiguous range. Invalid or non-finite values are rejected and the previous configuration is restored.

### Frame timing and duty-cycle interpretation
For standard `frameCfg`, chirps per frame are calculated as `(chirpEndIdx - chirpStartIdx + 1) * numLoops`. The standard `profileCfg` chirp interval is `idleTime + rampEndTime`. The frame duration estimate is chirps per frame multiplied by this interval; the number of enabled TX antennas is not used as a multiplier. Per-TX duty estimates use the `chirpCfg` TX-enable masks. These RF duty values are timing-based estimates, not direct PA-enable measurements. Advanced-frame configurations (`advFrameCfg`/`subFrameCfg`/`burstCfg`) are not covered by this standard-frame calculation and should not be interpreted using it.

### Configuration pre-flight validation
Before sending a standard-frame configuration, SPARC checks profile timing, ADC window versus ramp duration, chirp profile references, frame chirp references, frame overrun, and GUI-monitor output flags. Validation errors block transmission and are shown in the Command Execution Log. Advanced-frame commands are detected but require a separate device-specific timing validator.

### Range-Doppler and Range-Azimuth output
Enable the corresponding Range-Doppler Heat Map and Range Azimuth Heat Map options in Radar Control → Display, then send the configuration again. The `guiMonitor` flags control whether the firmware transmits these TLVs. Enabling the options does not retroactively change a configuration already running. The application now validates TLV dimensions against the configured FFT and antenna dimensions and logs payload-size mismatches. Enabling heatmaps no longer silently changes the frame periodicity to 1000 ms.
