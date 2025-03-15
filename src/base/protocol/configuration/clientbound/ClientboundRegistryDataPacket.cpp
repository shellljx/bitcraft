//
// Created by shell on 2025/3/13.
//
#include "base/protocol/ClientBoundPackets.h"
#include "base/model/configuration/RegistryEntry.h"

namespace bitcraft {

ClientboundRegistryDataPacket::ClientboundRegistryDataPacket() : Packet(0x07) {

}

void ClientboundRegistryDataPacket::read(bitcraft::DecodeStream *stream) {
  identifier = stream->readVarString();
  auto size = stream->readVarInt();
  for (int i = 0; i < size; i++) {
    auto entry = std::make_shared<RegistryEntry>();
    entry->read(stream);
    entries.push_back(entry);
  }
  entries.size();
}

void ClientboundRegistryDataPacket::write(bitcraft::EncodeStream *stream) {

}
}