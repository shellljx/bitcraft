//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "base/protocol/Packet.h"
namespace bitcraft {
class StatusPongPacket : public Packet {
 public:
  StatusPongPacket();
  ~StatusPongPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  long getPayload(){
    return pingTime;
  }

 private:
  long pingTime = 0;
};
}