//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "Packet.h"

namespace bitcraft {
enum class ProtocolStatus { NONE = -1, HANDSHAKE = 0, STATUS = 1, LOGIN = 2, PLAY = 3 };
class PacketFactory {
 public:
  explicit PacketFactory();
  ~PacketFactory();

  std::unique_ptr<Packet> createClientBoundPacket(int id);

  void setProtocolStatus(ProtocolStatus status) {
    status_ = status;
  }

  ProtocolStatus getProtocolStatus() {
    return status_;
  }

 private:
  ProtocolStatus status_ = ProtocolStatus::NONE;
};
}
