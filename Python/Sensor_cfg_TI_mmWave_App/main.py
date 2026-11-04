"""Application entry point for SPARC mmWave Radar Studio."""

import logging
import sys
import threading
from pathlib import Path

from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QApplication, QMessageBox

from sparc_mmwave.ui.main_window import MainWindow
from sparc_mmwave.services.radar_application import RadarApplication


APP_DIR = Path(__file__).resolve().parent
LOG_DIR = APP_DIR / "logs"
LOG_DIR.mkdir(exist_ok=True)

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s | %(levelname)s | %(name)s | %(message)s",
    handlers=[
        logging.StreamHandler(),
        logging.FileHandler(LOG_DIR / "sparc_mmwave.log", encoding="utf-8"),
    ],
)


def main():
    app = QApplication(sys.argv)
    app.setApplicationName("SPARC mmWave Radar Studio")
    app.setOrganizationName("SPARC - University of Luxembourg")

    try:
        window = MainWindow()
        radar_app = RadarApplication()
        window.attach_radar_visualizations(radar_app)
        window.set_runtime_statistics_provider(radar_app.runtime_statistics.snapshot)

        # The worker threads only acquire and parse data. UI table updates are
        # relayed through queued Qt signals by MainWindow.
        data_thread = threading.Thread(
            target=radar_app.read_data,
            args=(window,),
            name="RadarDataReader",
            daemon=True,
        )
        process_thread = threading.Thread(
            target=radar_app.process_data,
            args=(window,),
            name="RadarDataProcessor",
            daemon=True,
        )

        data_thread.start()
        process_thread.start()

        def safe_update_plots():
            try:
                radar_app.update_plots_wrapper(window)
            except Exception:
                logging.exception("Could not update radar visualizations")

        plot_timer = QTimer(window)
        plot_timer.timeout.connect(safe_update_plots)
        plot_timer.start(40)  # 25 Hz UI refresh; incoming data is processed independently.

        def close_event(event):
            logging.info("Application shutdown requested")
            plot_timer.stop()

            # The visualization window is a permanent companion: close it only
            # as part of the main application's shutdown sequence.
            try:
                window.close_visualization_for_shutdown()
            except Exception:
                logging.exception("Error closing the visualization companion window")

            # Stop RF/frame generation while the command UART is still open.
            # Only send sensorStop if this application previously issued sensorStart.
            try:
                window.shutdown_device()
            except Exception:
                logging.exception("Error during orderly radar-device shutdown")

            # Then stop background readers and release any remaining resources.
            radar_app.stop_event.set()
            data_thread.join(timeout=2.5)
            process_thread.join(timeout=2.5)
            if data_thread.is_alive() or process_thread.is_alive():
                logging.warning(
                    "A radar worker did not stop within 2.5 seconds; daemon shutdown will finish with the application."
                )
            event.accept()

        window.closeEvent = close_event
        window.show()
        # Start the companion visualization automatically. It remains open
        # throughout the session and cannot be closed independently.
        window.open_visualization_window()
        return app.exec_()

    except Exception as exc:
        logging.exception("Fatal application error")
        QMessageBox.critical(None, "SPARC mmWave Radar Studio", str(exc))
        return 1


if __name__ == "__main__":
    sys.exit(main())
