//
// Created by 李金祥 on 2022/5/29.
//

#include "base/protocol/ClientBoundPackets.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>

namespace bitcraft {
LoginSuccessPacket::LoginSuccessPacket() : Packet(0x02) {
}

LoginSuccessPacket::~LoginSuccessPacket() = default;

void LoginSuccessPacket::write(EncodeStream *stream) {

}

std::string generateUUID(int64_t u1, int64_t u2) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0')
     << std::setw(8) << ((u1 >> 32) & 0xFFFFFFFF) << "-"
     << std::setw(4) << ((u1 >> 16) & 0xFFFF) << "-"
     << std::setw(4) << (u1 & 0xFFFF) << "-"
     << std::setw(4) << ((u2 >> 48) & 0xFFFF) << "-"
     << std::setw(12) << (u2 & 0xFFFFFFFFFFFF);

  return ss.str();
}

void LoginSuccessPacket::read(DecodeStream *stream) {
  int64_t u1 = stream->readInt64();
  int64_t u2 = stream->readInt64();
  uuid = generateUUID(u1,u2);
  userName = stream->readVarString();
}
}