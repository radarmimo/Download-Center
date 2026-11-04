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

## Phase 3A/3B – Timing and runtime diagnostics
- Added configuration-derived frame timing, utilization, idle-time and estimated RF-active duty calculations.
- Added thread-safe rolling statistics for measured FPS, frame intervals, interval jitter, frame-number gaps and UART packet throughput.
- Extended the Overview dashboard with separate configuration and live-acquisition metric cards.
- Added packet-length sanity checks before accepting complete frames.
- Documented assumptions and limitations of estimated RF duty and UART-derived timing.

## UX refinement – command execution visibility
- Moved the existing command console from the Configuration/Ports page to the Live Radar operator workspace.
- Added a command execution panel with a live transmission status, progress bar, timestamped TX/RX log, and visible error reporting.
- Configuration commands are now logged before transmission and marked as sent after the serial write/flush succeeds; device responses are shown as they are received.
- Added clear feedback for missing configuration, disconnected/closed command ports, aborted sequences, and transmission failures.
- Kept the existing CFG editor, serial-port controls, radar plots, and application shutdown workflow.

## UX refinement – Signal Analysis and preset workflow
- Moved Range Profile, Range-Doppler and Range-Azimuth out of the Live Radar operator dashboard into a dedicated Signal Analysis navigation page.
- Added a full-screen plot viewer containing the complete signal-analysis workspace; closing it restores the plots to the Signal Analysis page.
- Kept Live Radar focused on device connection, configuration transmission, command execution feedback, 3D point cloud and detected-point views.
- Fixed Send & Start being disabled on startup despite the default preset already populating the command table. The action now reflects whether a configuration is actually loaded.
- Explicitly cleared any inherited button icon from Send & Start and retained a text-only primary action.
- Refined spacing, typography, panel contrast, navigation and button styling.

## UX refinement – visual system and operation readiness
- Reworked the application-wide Qt stylesheet with a more contemporary engineering-dashboard visual system: refined neutral surfaces, navy navigation, clearer typography, consistent rounded panels, improved tabs, controls, tables and scrollbars.
- Send configuration & start now starts disabled and becomes available only when both command and data UART ports are connected and a configuration is loaded.
- Added contextual tooltips explaining why the operation action is unavailable or what it will do when enabled.
- Kept the primary action text-only and disabled Qt's default-button behaviour to avoid platform-dependent default-button decoration.
- Stop radar availability now follows the tracked sensor-running state and port connection state.

## UX refinement – Point Cloud workspace
- Moved the 3D point-cloud view and detected-points tables from the Live Radar operator page into a dedicated Point Cloud navigation page.
- Added a standalone maximized 3D point-cloud viewer; closing it restores the live GL widget to its original tab.
- Kept the existing point-cloud rendering object and data-update path intact.

## Radar configuration as the primary workflow
- Promoted the full CFG editor to the first application workspace page, named Radar Control.
- Added a dedicated CFG toolbar with direct Load .cfg access and guidance to load, edit, apply and save configurations.
- Added a Device Operation sub-tab for connecting, sending/starting, stopping and viewing command execution feedback.
- Kept serial-port connection and advanced serial settings in a separate Device Setup page.
- Updated navigation and getting-started guidance to reflect the configuration-first workflow.

## UX update – unified Radar Control workspace
- Merged CFG editing and device operation controls into a single Radar Control page.
- Connect, Send Configuration & Start, and Stop Radar are now presented above the CFG editor, so users can edit and apply configurations without switching tabs.
- Removed the detailed command execution panel from the primary operation workspace.
- Moved the command progress indicator and UART transcript to Diagnostics → Command Log for occasional troubleshooting.
- Updated the getting-started guidance to reflect the simplified workflow.


## Radar Control workspace restoration
- Restored the original full CFG editor to the Radar Control page and explicitly show it after reparenting from the legacy tab widget.
- Preserved the original editable chirp/configuration tables and dependent-parameter recalculation callbacks.
- Restored the live command progress bar and command/response transcript directly below the editor and device controls.
- Added a vertically resizable splitter so users can allocate space between CFG editing and command feedback.

## UI layout robustness update
- Wrapped the full CFG editor in a dedicated scroll area so short displays scroll instead of compressing and overlapping editor controls.
- Rebalanced the vertical splitter and protected the command execution panel with a minimum usable height; the command log expands with available space.
- Refined tab sizing, table typography and header padding to prevent clipped labels and improve readability.
- Applied an antialiased Segoe UI application font where available.
- Replaced the ampersand in the Send Configuration action with a literal plus sign, avoiding Qt mnemonic interpretation that previously hid the separator character.

## Radar Control lower-panel organization
- Grouped the generated CFG command table and Save CFG action in a dedicated `CFG Commands & Save` tab.
- Added a neighbouring `Command Execution Log` tab containing the live progress bar, command transcript, device responses, and errors.
- Kept the parameter editor focused on the Chirp, Field of View, Display, and EVM settings, preserving its existing edit callbacks and dependent-parameter calculations.

## Duty-cycle dashboard clarification
- Renamed the frame-utilization metric to **Frame duty cycle** so the frame-level duty cycle is explicitly reported.
- Renamed estimated RF-active duty to **Aggregate RF duty cycle (est.)** and added tooltips/formula definitions to distinguish it from frame duty cycle and per-transmitter duty cycle.
- Clarified the dashboard note: frame duty cycle is active-frame time divided by frame period; aggregate RF duty estimate is chirps per frame multiplied by ramp duration, divided by frame period.


## Visualization workspace consolidation
- Merged Signal Analysis and Point Cloud into one main-navigation workspace named Visualization.
- Added Range Profile, Range-Doppler and Range-Azimuth as individual tabs alongside 3D Point Cloud and Detected Points.
- Moved the visualization tab strip to the bottom of the workspace.
- Preserved individual plot pop-out controls and the dedicated 3D viewer action.

## Unified header refinement
- Integrated the radar-platform and configuration-preset selectors into the same global header as the SPARC branding and application title.
- Replaced the separated horizontal label/control blocks with compact stacked selector groups and a subtle divider.
- Kept the existing selector widgets and their callbacks; this is a layout-only change.

## Visualization in a separate window
- Moved the complete Radar Visualization workspace out of the main page stack.
- Selecting Visualization in the bottom navigation now opens a dedicated maximized second window.
- The visualization window retains the five tabs (Range Profile, Range-Doppler, Range-Azimuth, 3D Point Cloud, and Detected Points), including their existing live data connections and pop-out controls.
- Closing the visualization window hides it; selecting Visualization again reopens the same workspace. The Radar Control window remains available independently.

## Companion visualization window
- Removed Visualization from the bottom navigation.
- The complete visualization workspace now opens automatically when the application starts.
- The visualization window is a persistent companion: its native close button is omitted and independent close requests (including Alt+F4) are ignored.
- Closing the main application explicitly closes the visualization window before radar shutdown and worker cleanup.


## CFG dependency restoration and completion

- Restored and hardened the editable Chirp Configuration change handler.
- Editing supported `profileCfg` and `frameCfg` values now updates the corresponding command-table fields, reparses the full configuration, and refreshes the Scene Parameters and Overview metrics immediately.
- Centralized profile-derived range calculations in `RadarCalculator.calculate_profile_metrics()` so sample rate, samples per chirp, and frequency slope consistently recalculate bandwidth, range resolution, beat frequency, maximum range, and unambiguous range.
- Added numeric validation and rollback for invalid edits, preventing partially applied CFG/model states.
- Preserved the unified configuration tabs, command execution log, automatic visualization companion window, and existing live radar workflow.
- Added unit tests for sample-rate and slope dependency chains and invalid profile inputs.

## Recalculated-parameter highlighting
- Scene Parameters rows whose values change after a Chirp Configuration edit are now highlighted with a consistent soft-green background and readable dark-green text.
- The highlight is applied to the complete affected row and includes a tooltip explaining that the value was recalculated automatically.
- Highlighting is based on comparing the radar-parameter model before and after recalculation; unchanged rows and the directly edited input parameter are not highlighted.
- Replaced random-colour behaviour for this feedback with a predictable visual convention.

## Overview duty-cycle metrics update
- Added per-chirp RF ramp duration and estimated RF ramp duty cycle.
- Added ADC acquisition duration and ADC acquisition duty cycle per chirp.
- Kept frame utilization and aggregate RF duty-cycle estimates, with explanatory tooltips distinguishing receiver sampling from transmitter activity.

## Frame timing and duty-cycle correction
- Corrected standard `frameCfg` parsing: chirp count is `(chirpEndIdx - chirpStartIdx + 1) * numLoops`; `numFrames` and `framePeriodicity` are read from their proper fields.
- Corrected `profileCfg` interpretation: `txStartTime` is no longer mistaken for a burst count.
- Standard-frame chirp interval is now `idleTime + rampEndTime`; TX antenna count is not multiplied into the frame duration.
- Added TX1/TX2/TX3 duty-cycle estimates based on `chirpCfg` TX-enable masks and scheduled chirp counts.
- Added explicit frame-overrun indication when calculated active duration exceeds frame periodicity.
- Added regression tests for standard `frameCfg` parsing, TX duty estimates, and frame timing.

## Configuration logic audit and corrections

- Corrected `profileCfg` field mapping: `txStartTime` is no longer treated as a burst count.
- Corrected `frameCfg` field mapping: chirp start/end indices, loop count, frame count and periodicity now map to their actual command positions. Editing chirps-per-loop updates `chirpEndIdx` relative to `chirpStartIdx`.
- Removed the erroneous `+1` when displaying the configured number of loops.
- Corrected profile bandwidth calculation to use configured `rampEndTime`; ADC sampling duration is calculated separately from samples/sample rate.
- Added validation that the ADC acquisition window fits inside the configured ramp.
- Clarified the sample-rate-derived maximum/usable range as an estimate using a configurable beat-frequency margin.
- Corrected waveform multiplexing classification from chirp TX-enable masks and used per-TX chirp count for TDM Doppler-resolution calculations.
- Added strict integer validation for standard `frameCfg` integer fields.
- Expanded regression tests for the corrected profile/frame mappings and invalid timing combinations.

## Configuration validation and heatmap reliability
- Added a pre-flight validator for standard profileCfg/chirpCfg/frameCfg/guiMonitor configurations; blocking errors are shown in the Command Execution Log before any UART command is sent.
- Advanced-frame commands are detected and explicitly flagged as requiring a dedicated advanced-frame timing model.
- Corrected Range-Doppler TLV dimensions to use per-TX chirp counts for TDM-MIMO and the padded Doppler FFT length.
- Corrected Range-Azimuth TLV dimensions to use configured range FFT bins and virtual-array length, with strict payload-size validation.
- Replaced fragile cubic-only range-azimuth interpolation with linear/nearest fallback.
- Removed the unintended 1-second frame-period override when enabling Range-Doppler or Range-Azimuth display outputs.
- Added regression tests for configuration pre-flight checks and heatmap TLV parsing.


## Chirps-in-loop regression correction
- Restored the original application meaning of `Number of Chirps in Loop` as the Doppler CPI chirp count per TX for TDM-MIMO (derived from actual `chirpCfg` TX masks and loop count), rather than the `frameCfg` chirp-index span.
- Kept the standard TI `frameCfg` chirp-index span as a separate `Chirp Configurations per Loop` metric.
- Prevented the legacy CPI metric from rewriting `frameCfg.chirpEndIdx`; the configured start/end indices remain authoritative.
- Doppler FFT sizing now uses the per-TX CPI count.
- Added regression tests for a 2-chirp-index, 16-loop TDM configuration (32 chirps/frame, 16 chirps/TX/CPI).

## Range metrics and editable chirp span correction
- Corrected the complex-I/Q ADC range estimate to use the configured complex sample rate as the theoretical positive beat-frequency limit, avoiding the unintended Fs/2 reduction from a real-sampling Nyquist assumption.
- Kept the engineering-margin usable/unambiguous range separate (default 80% of complex sample rate) and exposed the theoretical maximum beat frequency in profile metrics.
- Made `Chirp Configurations per Loop` editable in the Chirp Configuration table.
- Editing the chirp span updates `frameCfg.chirpEndIdx` while preserving `chirpStartIdx`; edits are rejected if any selected index lacks a corresponding `chirpCfg` definition.
- Kept `Number of Chirps in Loop` as the separate per-TX Doppler CPI quantity.
- Added regression tests for range scaling and separation of maximum/usable range.


## Matplotlib compatibility fix
- Replaced the removed `matplotlib.cm.get_cmap()` call with the modern `matplotlib.colormaps.get_cmap()` registry API.
- Added a fallback for older Matplotlib releases. This fixes heatmap refresh failures on newer Matplotlib versions.

## Ramp End Time editability fix
- Added `Ramp End Time [us]` to the editable Chirp Configuration parameter-to-command mapping.
- Editing this value now updates `profileCfg` field 4 and triggers the existing full configuration re-parse and dependent-parameter recalculation path.
- Added regression tests to ensure the GUI edit mapping and `profileCfg` field mapping remain connected.
