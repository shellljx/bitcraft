//
// Created by shell on 2025/3/15.
//
#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
FinishConfigurationPacket::FinishConfigurationPacket() : Packet(0x03) {}

void FinishConfigurationPacket::read(bitcraft::DecodeStream *stream) {}

void FinishConfigurationPacket::write(bitcraft::EncodeStream *stream) {}
}