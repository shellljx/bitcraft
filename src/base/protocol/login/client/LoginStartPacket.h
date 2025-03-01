//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "base/protocol/Packet.h"
namespace bitcraft {
class LoginStartPacket : public Packet {
 public:
  static std::shared_ptr<LoginStartPacket> Make(const std::string& name);

  ~LoginStartPacket() override;

  void read(DecodeStream *stream);
  void write(EncodeStream *stream);

 private:
  LoginStartPacket(std::string name);
 private:
  std::string userName = "";
};
}