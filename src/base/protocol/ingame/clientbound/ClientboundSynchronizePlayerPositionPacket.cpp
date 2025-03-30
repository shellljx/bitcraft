//
// Created by shell on 2025/3/24.
//
#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
void ClientboundSynchronizePlayerPositionPacket::read(bitcraft::DecodeStream *stream) {
  teleportId = stream->readVarInt();
  x = stream->readDouble();
  y = stream->readDouble();
  z = stream->readDouble();
  velocityX = stream->readDouble();
  velocityY = stream->readDouble();
  velocityZ = stream->readDouble();
  yaw = stream->readFloat();
  pitch = stream->readFloat();
  flags = stream->readInt32();
}

void ClientboundSynchronizePlayerPositionPacket::write(bitcraft::EncodeStream *stream) {

}
}