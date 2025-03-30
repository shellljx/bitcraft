//
// Created by shell on 2025/3/23.
//

#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
ClientboundSetPlayerPositionPacket::ClientboundSetPlayerPositionPacket() : Packet(0x1C) {}

void ClientboundSetPlayerPositionPacket::read(bitcraft::DecodeStream *stream) {
  x = stream->readDouble();
  feetY = stream->readDouble();
  z = stream->readDouble();
  flags = stream->readInt8();
}

void ClientboundSetPlayerPositionPacket::write(bitcraft::EncodeStream *stream) {}
}