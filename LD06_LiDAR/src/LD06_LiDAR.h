#pragma once

#include <Arduino.h>

#include "LD06_Packet.h"

class LD06_LiDAR
{
public:
  explicit LD06_LiDAR(HardwareSerial &serial_port);

  void begin(uint32_t baud_rate, int rx_pin, int tx_pin);
  bool update();
  void printPacketSummary(Stream &stream) const;

  const LD06PacketSummary &lastPacket() const;
  const LD06ScanFrame &latestScan() const;
  uint32_t packetsSeen() const;
  uint32_t crcFailCount() const;

private:
  static uint16_t readLeU16(const uint8_t *data);
  static float normalizeAngle(float angle_deg);
  static bool decodePacket(const uint8_t *packet, LD06PacketSummary &summary);

  void clearScanFrame(LD06ScanFrame &frame);
  void appendPointToCurrentScan(const LD06PacketSummary &summary,
                                const LD06ScanPoint &point);
  void publishCurrentScan();
  bool processPacket(const LD06PacketSummary &summary);

  HardwareSerial &serial_;
  uint8_t packet_buffer_[kLD06PacketSize]{};
  size_t packet_index_ = 0;
  uint8_t computed_crc_ = 0;
  LD06PacketSummary last_packet_{};
  LD06ScanFrame scan_buffers_[2]{};
  LD06ScanFrame *current_scan_ = &scan_buffers_[0];
  LD06ScanFrame *latest_scan_ = &scan_buffers_[1];
  bool scan_initialized_ = false;
  bool have_last_physical_angle_ = false;
  float last_physical_angle_deg_ = 0.0f;
  float start_physical_angle_deg_ = 0.0f;
  uint32_t packets_seen_ = 0;
  uint32_t crc_fail_count_ = 0;
};
