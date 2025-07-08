import sys
import logging
from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QApplication, QMessageBox
from ui import MainWindow
from radar_application import RadarApplication  # Import RadarApplication
import threading

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# main.py
def main():
    app = QApplication(sys.argv)

    # Ensure window is initialized first
    window = MainWindow()

    try:
        window.setGeometry(100, 100, 900, 700)
        window.show()

        radar_app = RadarApplication()
        # Threads for reading and processing data
        data_thread = threading.Thread(target=radar_app.read_data, args=(window,))
        data_thread.start()

        process_thread = threading.Thread(target=radar_app.process_data, args=(window,))
        process_thread.start()

        def safe_update():
            try:
                radar_app.update_plots_wrapper(window)
            except Exception as e:
                window.command_textbox.appendPlainText("Restart => 1): Press on 'Stop Device' or 'Sensor's NRST' Button, 2): Select on desired plot, 3): Click on 'Send Configuration'.")

        timers = {
            "plot_update_timer": QTimer()
        }

        timers["plot_update_timer"].timeout.connect(lambda: safe_update())
        timers["plot_update_timer"].start(25)

        def close_event(event):
            logging.info("Closing application.")
            radar_app.stop_event.set()  # Stop threads
            data_thread.join()
            process_thread.join()
            event.accept()

        window.closeEvent = close_event
        sys.exit(app.exec_())

    except Exception as e:
        logging.critical(f"Critical error: {e}")
        QMessageBox.critical(None, "Error", f"An error occurred: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
