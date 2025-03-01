//
// Created by 李金祥 on 2022/5/31.
//

#pragma once
#include "base/protocol/Packet.h"
namespace bitcraft {
class ServerKeepAlivePacket : public Packet {
 public:
  ServerKeepAlivePacket();
  ~ServerKeepAlivePacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  long getKeepAliveId() const {
    return keepAliveId_;
  }
 private:
  long long keepAliveId_;
};
}