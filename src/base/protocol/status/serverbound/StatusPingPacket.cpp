//
// Created by 李金祥 on 2022/5/29.
//

#include "StatusPingPacket.h"

namespace bitcraft {
StatusPingPacket::StatusPingPacket() : Packet(0x01), pingTime(0) {
}

StatusPingPacket::~StatusPingPacket() = default;

void StatusPingPacket::write(EncodeStream *stream) {
  stream->writeInt64(pingTime);
}

void StatusPingPacket::read(DecodeStream *stream) {
  pingTime = stream->readInt64();
}
}