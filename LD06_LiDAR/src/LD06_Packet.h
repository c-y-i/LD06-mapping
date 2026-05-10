#pragma once

#include <Arduino.h>

constexpr uint8_t kLD06PacketHeader = 0x54;
constexpr uint8_t kLD06PacketLength = 0x2C;
constexpr size_t kLD06PointsPerPacket = 12;
constexpr size_t kLD06PacketSize = 47;
constexpr size_t kLD06MaxPointsPerScan = 1200;
constexpr float kLD06MaxAngleStepDeg = 5.0f;
constexpr uint16_t kLD06MaxDisplayDistanceMm = 12000;

struct LD06ScanPoint
{
  float angle_deg = 0.0f;
  uint16_t distance_mm = 0;
  uint8_t intensity = 0;
  int16_t x_mm = 0;
  int16_t y_mm = 0;
  bool valid = false;
};

struct LD06PacketSummary
{
  uint16_t speed_raw = 0;
  float start_angle_deg = 0.0f;
  float end_angle_deg = 0.0f;
  uint16_t timestamp_ms = 0;
  uint16_t valid_points = 0;
  LD06ScanPoint points[kLD06PointsPerPacket]{};
};

struct LD06ScanFrame
{
  uint16_t speed_raw = 0;
  uint16_t timestamp_ms = 0;
  uint16_t point_count = 0;
  uint16_t valid_point_count = 0;
  uint32_t crc_fail_count = 0;
  LD06ScanPoint points[kLD06MaxPointsPerScan]{};
};
