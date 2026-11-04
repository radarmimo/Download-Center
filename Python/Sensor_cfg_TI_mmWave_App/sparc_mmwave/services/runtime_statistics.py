"""Thread-safe rolling statistics for incoming TI mmWave UART frames."""
from collections import deque
from threading import Lock
import time


class RuntimeStatistics:
    def __init__(self, window_seconds=5.0, max_intervals=200):
        self.window_seconds = float(window_seconds)
        self._lock = Lock()
        self._intervals = deque(maxlen=max_intervals)
        self._byte_events = deque()
        self._last_frame_number = None
        self._last_timestamp = None
        self._frames = 0
        self._missing_frames = 0
        self._out_of_order_frames = 0
        self._received_bytes = 0
        self._last_packet_time = None

    def reset(self):
        with self._lock:
            self._intervals.clear()
            self._byte_events.clear()
            self._last_frame_number = None
            self._last_timestamp = None
            self._frames = 0
            self._missing_frames = 0
            self._out_of_order_frames = 0
            self._received_bytes = 0
            self._last_packet_time = None

    def record_frame(self, frame_number, packet_bytes, timestamp=None):
        now = time.monotonic() if timestamp is None else float(timestamp)
        with self._lock:
            if self._last_timestamp is not None:
                interval = now - self._last_timestamp
                if interval > 0:
                    self._intervals.append(interval)
            if frame_number is not None:
                frame_number = int(frame_number) & 0xFFFFFFFF
                if self._last_frame_number is not None:
                    delta = (frame_number - self._last_frame_number) & 0xFFFFFFFF
                    if 1 < delta < 0x80000000:
                        self._missing_frames += delta - 1
                    elif delta == 0 or delta >= 0x80000000:
                        self._out_of_order_frames += 1
                self._last_frame_number = frame_number
            self._last_timestamp = now
            self._last_packet_time = now
            self._frames += 1
            size = max(0, int(packet_bytes))
            self._received_bytes += size
            self._byte_events.append((now, size))
            self._prune(now)

    def _prune(self, now):
        cutoff = now - self.window_seconds
        while self._byte_events and self._byte_events[0][0] < cutoff:
            self._byte_events.popleft()

    def snapshot(self):
        now = time.monotonic()
        with self._lock:
            self._prune(now)
            intervals = list(self._intervals)
            recent_bytes = sum(size for _, size in self._byte_events)
            if intervals:
                avg = sum(intervals) / len(intervals)
                fps = 1.0 / avg if avg > 0 else 0.0
                jitter = (sum((x - avg) ** 2 for x in intervals) / len(intervals)) ** 0.5
                min_interval, max_interval = min(intervals), max(intervals)
            else:
                avg = fps = jitter = min_interval = max_interval = 0.0
            age = max(0.0, now - self._last_packet_time) if self._last_packet_time is not None else None
            return {
                "frames_received": self._frames,
                "measured_fps": fps,
                "average_interval_ms": avg * 1000.0,
                "minimum_interval_ms": min_interval * 1000.0,
                "maximum_interval_ms": max_interval * 1000.0,
                "interval_jitter_ms": jitter * 1000.0,
                "missing_frames": self._missing_frames,
                "out_of_order_frames": self._out_of_order_frames,
                "throughput_kBps": recent_bytes / self.window_seconds / 1000.0,
                "throughput_Mbps": recent_bytes * 8.0 / self.window_seconds / 1_000_000.0,
                "last_frame_age_s": age,
                "is_receiving": age is not None and age < 2.0,
            }
