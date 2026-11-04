# SPARC mmWave Radar Studio — architecture

This clean package revision has one canonical copy of each Python module. All application implementation code lives under `sparc_mmwave/`; the project root contains only the launcher, build configuration, dependencies and documentation.

## Module responsibilities

- `main.py`: application startup, logging, worker lifecycle and GUI refresh timer.
- `sparc_mmwave/ui/main_window.py`: SPARC application shell, navigation, theme, dashboard and queued Qt signal bridge.
- `sparc_mmwave/ui/legacy_window.py`: retained configuration/serial UI implementation and callbacks from the supplied application. This is intentionally a compatibility layer pending a deeper widget-by-widget extraction.
- `sparc_mmwave/core/radar_calculator.py`: existing radar parameter calculation routines.
- `sparc_mmwave/processing/payload.py`: radar frame/TLV payload parsing.
- `sparc_mmwave/services/radar_application.py`: data acquisition, parsing orchestration and plot-update preparation.
- `sparc_mmwave/visualization/plots.py`: PyQtGraph visualization helpers.
- `sparc_mmwave/hardware/`: reserved for the next extraction of serial-port and device-specific communication code.

## Import policy

Internal imports must use package-relative imports or fully qualified `sparc_mmwave...` imports. Do not create root-level copies or compatibility shims named `ui.py`, `payload.py`, `plots.py`, `radar_calculator.py` or `radar_application.py`; these would shadow the package and reintroduce ambiguity.

## Migration boundary

The radar CFG command handling, parser formats and existing calculation algorithms have been preserved in this phase. The legacy UI is still a single module and the serial implementation remains within it. Further extraction should be done only after testing the current clean package against the actual TI boards and firmware.
