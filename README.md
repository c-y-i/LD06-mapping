# LD06 Mapping

LD06 Mapping is a LiDAR mapping workspace built around the LD06 2D LiDAR. It includes a reusable Arduino/PlatformIO LD06 library, ESP32 firmware for streaming scan data, host-side Python viewers and rover tools, and a pure-Python 2D SLAM simulator.

The rover pieces are still real subsystems in this workspace; `rover_stack/` keeps its existing name and firmware role.

## What's Here

| Folder | Description |
|---|---|
| [LD06_LiDAR/](LD06_LiDAR/) | Reusable Arduino/PlatformIO library for LD06 packet parsing and scan assembly |
| [LD06_lidar/](LD06_lidar/) | ESP32 firmware/demo app that uses `LD06_LiDAR`, streams JSON over serial, and serves an optional web viewer |
| [slam/](slam/) | Pure-Python 2D SLAM package and hardware-free simulator (`slam/sim.py`) |
| [py_scripts/](py_scripts/) | Shared host-side Python workspace for sensor viewers and rover tools |
| [rover_stack/](rover_stack/) | Rover firmware and tools |
| [VL53L5CX_tof/](VL53L5CX_tof/) | Standalone 8x8 ToF depth streaming firmware and viewer |

## Try It Without Hardware

```bash
python -m slam.sim --map office
# open http://localhost:8080
```

Plot-only mode:

```bash
python -m slam.plot_sim
```

Static, non-live plot:

```bash
python -m slam.plot_sim --no-live
```

Plot on bundled static maps:

```bash
python -m slam.plot_sim --map nav2_tb3_sandbox
```

## Run The LD06 Firmware Demo

```bash
cd LD06_lidar
platformio run --target upload
platformio device monitor --baud 460800
```

The firmware reads LD06 UART packets through the reusable `LD06_LiDAR` library, emits newline-delimited JSON scan messages, optionally reads IMU data, and can serve a browser viewer from the ESP32.

## Run With The Rover

```bash
cd py_scripts
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt

python -m rover_tools.controller_teleop --port /dev/ttyACM0 --baud 460800 --web-port 8080 --slam
```

Record and replay:

```bash
python -m rover_tools.record --port /dev/ttyACM0 --output run1.jsonl
python -m rover_tools.replay --file run1.jsonl [--speed 2.0]
```

## Flash Rover Firmware

```bash
cd rover_stack/controller && platformio run --target upload
cd rover_stack/bot        && platformio run --target upload
```

Set `kBotMac` in `rover_stack/controller/src/main.cpp` to your bot's MAC address.

## Agent Guides

- [AGENTS/rover_stack.md](AGENTS/rover_stack.md)
- [AGENTS/slam.md](AGENTS/slam.md)
- [AGENTS/py_scripts.md](AGENTS/py_scripts.md)
