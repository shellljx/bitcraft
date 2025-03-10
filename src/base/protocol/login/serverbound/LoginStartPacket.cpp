//
// Created by 李金祥 on 2022/5/29.
//

#include "LoginStartPacket.h"

#include <utility>
namespace bitcraft {

std::shared_ptr<LoginStartPacket> LoginStartPacket::Make(const std::string &name) {
  if (name.empty())return nullptr;
  auto packet = std::shared_ptr<LoginStartPacket>(new LoginStartPacket(name));
  return packet;
}

LoginStartPacket::LoginStartPacket(std::string name) : Packet(0x00), userName(std::move(name)) {
}

LoginStartPacket::~LoginStartPacket() noexcept {
}

void LoginStartPacket::write(EncodeStream *stream) {
  stream->writeVarString(userName);
  stream->writeInt64(123);
  stream->writeInt64(123);
}

void LoginStartPacket::read(DecodeStream *stream) {
  userName = stream->readVarString();
}
}