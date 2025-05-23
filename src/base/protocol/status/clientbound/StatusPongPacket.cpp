//
// Created by 李金祥 on 2022/5/29.
//

#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
StatusPongPacket::StatusPongPacket() : Packet(0x01) {
}

StatusPongPacket::~StatusPongPacket() = default;

void StatusPongPacket::write(EncodeStream *stream) {
  stream->writeInt64(pingTime);
}

void StatusPongPacket::read(DecodeStream *stream) {
  pingTime = stream->readInt64();
}
}