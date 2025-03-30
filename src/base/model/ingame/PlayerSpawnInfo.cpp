//
// Created by shell on 2025/3/21.
//

#include "PlayerSpawnInfo.h"
#include "GlobalPos.h"

namespace bitcraft {
void PlayerSpawnInfo::read(bitcraft::DecodeStream *stream) {
  dimensionType = stream->readVarInt();
  dimensionName = stream->readVarString();
  hashedSeed = stream->readInt64();
  gameMode = stream->readUint8();
  previousGameMode = stream->readInt8();
  isDebug = stream->readBoolean();
  isFlat = stream->readBoolean();
  hasDeathLocation = stream->readBoolean();
  if (hasDeathLocation) {
    deathLocation = std::make_shared<GlobalPos>();
    deathLocation->read(stream);
  }
  portalCooldown = stream->readVarInt();
}

void PlayerSpawnInfo::write(bitcraft::EncodeStream *stream) {

}
}