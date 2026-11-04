# Hardware layer

Reserved for the next extraction step. In this first migration, the existing serial-port behaviour remains in `ui/legacy_window.py` so command sequencing and sensor interaction are unchanged. The next hardware refactor should move port discovery, open/close, baud-rate handling, writes, timeouts and reconnect logic into a UI-independent serial manager.
