//
// Created by shell on 2025/3/20.
//
#include "base/protocol/ClientBoundPackets.h"
#include "base/model/ingame/PlayerSpawnInfo.h"

namespace bitcraft {
ClientboundLoginPacket::ClientboundLoginPacket() : Packet(0x2C) {}

void ClientboundLoginPacket::read(bitcraft::DecodeStream *stream) {
  entityId = stream->readInt32();
  hardcore = stream->readBoolean();
  auto dimensionCount = stream->readVarInt();
  dimensions = std::vector<std::string>(dimensionCount);
  for (int index = 0; index < dimensionCount; index++) {
    dimensions[index] = stream->readVarString();
  }
  maxPlayers = stream->readVarInt();
  viewDistance = stream->readVarInt();
  simulationDistance = stream->readVarInt();
  reducedDebugInfo = stream->readBoolean();
  enableRespawnScreen = stream->readBoolean();
  doLimitedCrafting = stream->readBoolean();
  playerSpawnInfo = std::make_shared<PlayerSpawnInfo>();
  playerSpawnInfo->read(stream);
  enforceSecureChat = stream->readBoolean();
}

void ClientboundLoginPacket::write(bitcraft::EncodeStream *stream) {

}
}