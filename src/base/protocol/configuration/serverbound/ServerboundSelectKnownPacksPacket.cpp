//
// Created by shell on 2025/3/13.
//

#include "ServerboundSelectKnownPacksPacket.h"
#include "base/model/configuration/KnownPack.h"

namespace bitcraft {
ServerboundSelectKnownPacksPacket::ServerboundSelectKnownPacksPacket() : Packet(0x07) {}
void ServerboundSelectKnownPacksPacket::read(bitcraft::DecodeStream *stream) {

}

void ServerboundSelectKnownPacksPacket::write(bitcraft::EncodeStream *stream) {
  stream->writeVarInt(static_cast<int>(knownPacks.size()));
  for (auto &pack : knownPacks) {
    pack->write(stream);
  }
}

void ServerboundSelectKnownPacksPacket::setKnownPacks(const std::vector<std::shared_ptr<KnownPack>> &packs) {
  for (auto &pack : packs) {
    knownPacks.push_back(pack);
  }
}
}