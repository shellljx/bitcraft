//
// Created by 李金祥 on 2022/6/1.
//

#pragma once
#include "base/protocol/Packet.h"
namespace bitcraft {
class ClientChatPacket : public Packet {
 public:
  explicit ClientChatPacket(const char *message);
  ~ClientChatPacket() override;

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

 private:
  std::string message_;
};
}