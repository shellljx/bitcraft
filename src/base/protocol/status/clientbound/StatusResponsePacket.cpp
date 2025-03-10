//
// Created by 李金祥 on 2022/5/28.
//

#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
StatusResponsePacket::StatusResponsePacket() : Packet(0) {
}

StatusResponsePacket::~StatusResponsePacket() = default;

void StatusResponsePacket::write(EncodeStream *stream) {

}

void StatusResponsePacket::read(DecodeStream *stream) {
  info = stream->readVarString();
}
}