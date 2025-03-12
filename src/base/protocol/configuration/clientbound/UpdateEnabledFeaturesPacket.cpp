//
// Created by shell on 2025/3/11.
//
#include "base/protocol/ClientBoundPackets.h"
namespace bitcraft {
UpdateEnabledFeaturesPacket::UpdateEnabledFeaturesPacket() : Packet(0x0C) {}

void UpdateEnabledFeaturesPacket::read(bitcraft::DecodeStream *stream) {
  auto length = stream->readVarInt();
  for (int i = 0; i < length; i++) {
    auto flag = stream->readVarString();
    featureFlags.push_back(flag);
  }
}

void UpdateEnabledFeaturesPacket::write(bitcraft::EncodeStream *stream) {

}
}