#include <Arduino.h>
#include <LD06_LiDAR.h>

constexpr int kLd06RxPin = 7;
constexpr int kLd06TxPin = 8;
constexpr uint32_t kLd06Baud = 230400;
constexpr uint32_t kUsbBaud = 460800;

LD06_LiDAR lidar(Serial1);

void printJsonScan(const LD06ScanFrame &scan)
{
  Serial.print(F("{\"t\":\"scan\",\"x\":["));
  bool first = true;
  for (uint16_t i = 0; i < scan.point_count; ++i)
  {
    if (!scan.points[i].valid)
    {
      continue;
    }
    if (!first)
    {
      Serial.print(',');
    }
    Serial.print(scan.points[i].x_mm);
    first = false;
  }

  Serial.print(F("],\"y\":["));
  first = true;
  for (uint16_t i = 0; i < scan.point_count; ++i)
  {
    if (!scan.points[i].valid)
    {
      continue;
    }
    if (!first)
    {
      Serial.print(',');
    }
    Serial.print(scan.points[i].y_mm);
    first = false;
  }

  Serial.print(F("],\"i\":["));
  first = true;
  for (uint16_t i = 0; i < scan.point_count; ++i)
  {
    if (!scan.points[i].valid)
    {
      continue;
    }
    if (!first)
    {
      Serial.print(',');
    }
    Serial.print(scan.points[i].intensity);
    first = false;
  }
  Serial.println(F("]}"));
}

void setup()
{
  Serial.begin(kUsbBaud);
  lidar.begin(kLd06Baud, kLd06RxPin, kLd06TxPin);
}

void loop()
{
  if (lidar.update())
  {
    printJsonScan(lidar.latestScan());
  }
}
