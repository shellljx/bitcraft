//
// Created by 李金祥 on 2022/5/28.
//
#pragma once
#include "base/io/ReadWriteable.h"

namespace bitcraft {
class Packet : public ReadWriteable {
 public:
  explicit Packet(int packetId) : packetId_(packetId) {

  }
  ~Packet() override = default;

  void read(DecodeStream *stream) override = 0;
  void write(EncodeStream *stream) override = 0;

  int getPacketId() const {
    return packetId_;
  }

 private:
  int packetId_;
};
}