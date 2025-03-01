//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "base/protocol/Packet.h"

namespace bitcraft {
class HandshakePacket : public Packet {
 public:
  static std::shared_ptr<HandshakePacket> Make(int version, const std::string &host, uint16_t port, int state);
  ~HandshakePacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  HandshakePacket(int version, std::string host, uint16_t port, int nextState);
 private:
  int protocolVersion_ = 0;
  std::string serverAddr_;
  uint16_t serverPort = 0;
  int nextState = 2;
};
}