#include <Arduino.h>
#include <LD06_LiDAR.h>

constexpr int kLd06RxPin = 7;
constexpr int kLd06TxPin = 8;
constexpr uint32_t kLd06Baud = 230400;
constexpr uint32_t kUsbBaud = 460800;

LD06_LiDAR lidar(Serial1);

void setup()
{
  Serial.begin(kUsbBaud);
  lidar.begin(kLd06Baud, kLd06RxPin, kLd06TxPin);
}

void loop()
{
  if (lidar.update())
  {
    const LD06ScanFrame &scan = lidar.latestScan();
    Serial.print("points=");
    Serial.print(scan.point_count);
    Serial.print(" valid=");
    Serial.print(scan.valid_point_count);
    Serial.print(" packets=");
    Serial.print(lidar.packetsSeen());
    Serial.print(" crc_fail=");
    Serial.println(scan.crc_fail_count);
  }
}
