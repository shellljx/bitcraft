//
// Created by shell on 2025/3/12.
//
#include "base/protocol/ClientBoundPackets.h"
#include "base/model/configuration/KnownPack.h"

namespace bitcraft {
SelectKnownPacksPacket::SelectKnownPacksPacket() : Packet(0x0E) {

}
void SelectKnownPacksPacket::read(bitcraft::DecodeStream *stream) {
  auto size = stream->readVarInt();
  for (int i = 0; i < size; ++i) {
    auto pack = std::make_shared<KnownPack>();
    pack->read(stream);
    knownPacks.push_back(pack);
  }
}

void SelectKnownPacksPacket::write(bitcraft::EncodeStream *stream) {}
}