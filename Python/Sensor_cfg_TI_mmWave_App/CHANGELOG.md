# Changelog

## 2.0.0 — Phase 1 and Phase 2

- Reorganized the application into the `sparc_mmwave` package while retaining root-level import shims.
- Preserved original radar configuration and parsing code in a compatibility layer.
- Added a SPARC-branded navigation shell with Overview, Configuration, Live Radar and Diagnostics pages.
- Added live calculated-parameter cards to the overview.
- Moved serial baud-rate controls to the advanced settings area.
- Added queued Qt signal delivery for table updates initiated by the radar processing worker.
- Added bounded shutdown handling and persistent application logging.


## Clean package revision
- Removed root-level compatibility shim modules to eliminate duplicate module names.
- Updated the application entry point and internal imports to use `sparc_mmwave` exclusively.
- Updated the PyInstaller spec for the package-only layout.
- Replaced the hard-coded developer icon path with a package-relative resource path.


## Live plot integration update
- Embedded Range Profile, Range-Doppler, and Range-Azimuth plots in the Live Radar workspace.
- Added independent pop-out/maximize windows for each plot. Closing a floating plot restores it to its dashboard panel.
- Changed plot creation from standalone pyqtgraph windows to embeddable PlotWidget instances.

## Orderly device shutdown
- Track whether the application has issued `sensorStart` / `sensorStop`.
- On application close, send `sensorStop` over the command UART before closing either serial port.
- Then stop the background reader/processor threads and disconnect the ports.
- Handle missing/closed command ports and serial exceptions without blocking application closure indefinitely.
