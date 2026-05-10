# LD06_LiDAR

`LD06_LiDAR` is an Arduino/PlatformIO library for the LD06 2D LiDAR. It reads LD06 UART packets, validates CRCs, decodes scan points, assembles full scan frames across packets, and exposes the latest scan to firmware code.

The library deliberately does not include board pin constants, Wi-Fi, IMU handling, JSON formatting, or application heartbeat/status output. Those belong in the firmware app that consumes the library.

## Install In PlatformIO

From a sibling firmware project, add the local library as a dependency:

```ini
lib_deps =
  symlink://../LD06_LiDAR
```

You can also copy `LD06_LiDAR/` into a project's `lib/` directory.

## Wiring Notes

Connect the LD06 UART TX line to the ESP32 RX pin passed to `begin()`. The LD06 default serial baud rate is `230400`.

Power requirements depend on the LiDAR module and carrier board. Verify voltage and current requirements for your hardware before connecting it to the ESP32.

## Minimal Usage

```cpp
#include <Arduino.h>
#include <LD06_LiDAR.h>

LD06_LiDAR lidar(Serial1);

void setup()
{
  Serial.begin(460800);
  lidar.begin(230400, 7, 8);
}

void loop()
{
  if (lidar.update())
  {
    const LD06ScanFrame &scan = lidar.latestScan();
    Serial.print("points=");
    Serial.println(scan.valid_point_count);
  }
}
```

## Data Model

- `LD06ScanPoint`: one decoded point with angle, distance, intensity, Cartesian `x_mm`/`y_mm`, and validity.
- `LD06PacketSummary`: one validated LD06 packet with 12 decoded points and packet metadata.
- `LD06ScanFrame`: one assembled scan frame with point counters, latest timestamp, speed, CRC fail count, and point storage.

## Examples

- `examples/BasicScan`: prints a summary whenever a full scan is ready.
- `examples/SerialJsonStreamer`: streams compact JSON arrays compatible with simple host-side viewers.
