//
// Created by shell on 2025/3/23.
//
#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
ClientboundChangeDifficultyPacket::ClientboundChangeDifficultyPacket() : Packet(0x0B) {}

void ClientboundChangeDifficultyPacket::read(bitcraft::DecodeStream *stream) {
  difficulty = stream->readUint8();
  difficultyLock = stream->readBoolean();
}

void ClientboundChangeDifficultyPacket::write(bitcraft::EncodeStream *stream) {

}
}