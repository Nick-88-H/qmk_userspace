import os
import sys
import subprocess

VENV_DIR = ".venv"
REQUIREMENTS = ["pywinusb"]

venv_py = os.path.join(VENV_DIR, "Scripts", "python.exe")
venv_pw = os.path.join(VENV_DIR, "Scripts", "pythonw.exe")

# --- Only do bootstrap if NOT spawned ---
if "--spawned" not in sys.argv:
    # 1️⃣ Make sure venv exists + deps
    if not os.path.isdir(VENV_DIR):
        subprocess.check_call([sys.executable, "-m", "venv", VENV_DIR])

    subprocess.check_call([venv_py, "-m", "pip", "install", "--upgrade", "pip"])
    subprocess.check_call([venv_py, "-m", "pip", "install"] + REQUIREMENTS)

    # 2️⃣ Now spawn the child ONCE, with --spawned to mark it
    subprocess.Popen(
        [venv_pw, __file__, "--spawned"],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
        stdin=subprocess.DEVNULL,
        creationflags=0x00000008  # DETACHED_PROCESS
    )
    sys.exit(0)

# --- If we are spawned, skip bootstrap, run sticky only ---

import time
import re
import winsound
import pywinusb.hid as hid

def play_on():
    winsound.Beep(1200, 100)

def play_off():
    winsound.Beep(600, 100)

def dump_report(data):
    raw = bytes(data)
    if raw[0] == 0:
        raw = raw[1:]
    msg = raw.rstrip(b'\x00').decode(errors="ignore").strip()
    if not msg:
        return

    m = msg.upper()
    if re.search(r'ACTIVATED', m):
        play_on()
    elif re.search(r'(RELEASED|TIMEOUT)', m):
        play_off()

devices = hid.HidDeviceFilter(vendor_id=0x3434).get_devices()

idx = 2  # your known debug console index
dev = devices[idx]

dev.open()
dev.set_raw_data_handler(dump_report)

try:
    while True:
        time.sleep(0.1)
except KeyboardInterrupt:
    dev.close()
