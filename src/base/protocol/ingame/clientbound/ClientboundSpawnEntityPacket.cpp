//
// Created by shell on 2025/3/24.
//

#include "base/protocol/ClientBoundPackets.h"
#include "base/protocol/DataTypes.h"

namespace bitcraft {
ClientboundSpawnEntityPacket::ClientboundSpawnEntityPacket() : Packet(0x01) {}

void ClientboundSpawnEntityPacket::read(bitcraft::DecodeStream *stream) {
  entityId = stream->readVarInt();
  uuid = readUUID(stream);
  type = stream->readVarInt();
  x = stream->readDouble();
  y = stream->readDouble();
  z = stream->readDouble();
  pitch = stream->readUint8();
  yaw = stream->readUint8();
  headYaw = stream->readUint8();
  data = stream->readVarInt();
  velocityX = stream->readInt16();
  velocityY = stream->readInt16();
  velocityZ = stream->readInt16();
}

void ClientboundSpawnEntityPacket::write(bitcraft::EncodeStream *stream) {

}
}