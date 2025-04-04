//
// Created by 李金祥 on 2022/5/29.
//
#pragma once
#include "../../Packet.h"
namespace bitcraft {
class StatusPingPacket : public Packet {
 public:
  StatusPingPacket();
  ~StatusPingPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  void setPayload(long payload) {
    pingTime = payload;
  }

  long getPayload() {
    return pingTime;
  }

 private:
  long pingTime;
};
}