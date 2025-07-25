import os
import sys
import subprocess
import json

debug = False
proc_name = "python.exe" if debug else "pythonw.exe"

VENV_DIR = ".venv"
REQUIREMENTS = ["pip", "pywinusb", "psutil"]

venv_py = os.path.join(VENV_DIR, "Scripts", "python.exe")
venv_pip = os.path.join(VENV_DIR, "Scripts", "pip.exe")
venv_pw = os.path.join(VENV_DIR, "Scripts", "pythonw.exe")

# --- Only do bootstrap if NOT spawned ---
if "--spawned" not in sys.argv:
    # Bootstrap and re-launch in venv
    if not os.path.isdir(VENV_DIR):
        subprocess.check_call([sys.executable, "-m", "venv", VENV_DIR])

    result = subprocess.run([venv_pip, "list", "--format=json"], capture_output=True, text=True, check=True)
    installed = {pkg["name"].lower() for pkg in json.loads(result.stdout)}
    missing = [pkg for pkg in REQUIREMENTS if pkg.lower() not in installed]

    if missing:
        subprocess.check_call([venv_py, "-m", "pip", "install", "--upgrade", "pip"])
        subprocess.check_call([venv_py, "-m", "pip", "install"] + REQUIREMENTS)

    # Forward args (like --kill) into the venv-run subprocess
    runner = venv_py if debug else venv_pw
    subprocess.Popen(
        [runner, __file__, "--spawned", *sys.argv[1:]],
        stdout=None if debug else subprocess.DEVNULL,
        stderr=None if debug else subprocess.DEVNULL,
        stdin=None if debug else subprocess.DEVNULL,
        creationflags=0x00000008  # DETACHED_PROCESS
    )
    sys.exit(0)

# --- If we are spawned, skip bootstrap, run sticky only ---

import winsound
from pywinusb import hid
from time import sleep
import psutil

def find_sticky_processes():
    """Returns a list of all sticky sound processes (python/pythonw + --spawned)."""
    matches = []
    for proc in psutil.process_iter(['pid', 'name', 'cmdline', 'create_time']):
        try:
            if proc.info['name'] in ('python.exe', 'pythonw.exe') and '--spawned' in proc.info['cmdline']:
                matches.append(proc)
        except (psutil.NoSuchProcess, psutil.AccessDenied, KeyError):
            continue
    return matches

def kill_sticky_processes():
    """Kills all running sticky sound processes. Returns True if any were killed."""
    procs = find_sticky_processes()
    if not procs:
        print("Nothing to kill cobber.\n")
        return False

    for proc in procs:
        print(f"Killing PID {proc.pid}: {' '.join(proc.info['cmdline'])}\n")
        proc.kill()

    return True

def trim_sticky_processes(max_count=2):
    """Keeps only the most recent `max_count` sticky sound processes alive."""
    sticky_procs = find_sticky_processes()
    sticky_procs.sort(key=lambda p: p.info['create_time'])

    if len(sticky_procs) <= max_count:
        print(f"{len(sticky_procs)} sticky processes — no trimming needed.\n")
        return

    print(f"{len(sticky_procs)} sticky processes — trimming to {max_count}.\n")
    for proc in sticky_procs[:-max_count]:
        print(f"Killing PID {proc.pid}: {' '.join(proc.info['cmdline'])}")
        proc.kill()

def play_beep(frequency, duration):
    winsound.Beep(frequency, duration)

def handle_message(index, msg):
    print(f"[{index}] {msg!r}")
    m = msg.upper()

    if "SHIFT STICKY" in m:
        play_beep(1500, 120)
    elif any(mod in m for mod in ["INSERT STICKY", "CTRL STICKY", "ALT STICKY"]):
        play_beep(1100, 100)
    elif "TIMEOUT" in m:
        play_beep(600, 80)
    elif "RELEASED" in m:
        play_beep(700, 80)

def make_handler(index):
    def handler(data):
        raw = bytes(data)
        if raw[0] == 0:
            raw = raw[1:]
        msg = raw.rstrip(b'\x00').decode(errors="ignore").strip()
        if msg:
            handle_message(index, msg)
    return handler

def main():
    trim_sticky_processes()
    devices = hid.HidDeviceFilter(vendor_id=0x3434).get_devices()
    if not devices:
        print("No Keychron devices found.")
        return

    print(f"Listening to {len(devices)} Keychron device(s)...\n")

    handlers = []
    for i, dev in enumerate(devices):
        print(f"Opening device {i}: {dev.product_name}")
        dev.open()
        handler = make_handler(i)
        dev.set_raw_data_handler(handler)
        handlers.append((dev, handler))

    while True:
        sleep(0.1)

if __name__ == "__main__":
    if "--kill" in sys.argv:
        kill_sticky_processes()
        sys.exit(0)
    else:
        main()
