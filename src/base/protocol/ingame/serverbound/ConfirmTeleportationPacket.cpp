//
// Created by shell on 2025/3/25.
//

#include "ConfirmTeleportationPacket.h"

namespace bitcraft {
void ConfirmTeleportationPacket::read(bitcraft::DecodeStream *stream) {

}

void ConfirmTeleportationPacket::write(bitcraft::EncodeStream *stream) {
  stream->writeVarInt(teleportId);
}
}