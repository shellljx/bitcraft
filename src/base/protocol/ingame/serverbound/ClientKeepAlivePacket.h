//
// Created by 李金祥 on 2022/5/31.
//

#pragma once
#include "base/protocol/Packet.h"
namespace bitcraft {
class ClientKeepAlivePacket : public Packet {
 public:
  ClientKeepAlivePacket();
  ~ClientKeepAlivePacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  long getKeepAliveId() const {
    return keepAliveId_;
  }

  void setKeepAliveId(long id) {
    keepAliveId_ = id;
  }
 private:
  long long keepAliveId_;
};
}