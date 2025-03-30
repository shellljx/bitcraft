//
// Created by shell on 2025/3/23.
//

#include "ServerboundPlayerLoadedPacket.h"

namespace bitcraft {
ServerboundPlayerLoadedPacket::ServerboundPlayerLoadedPacket() : Packet(0x2A) {}

void ServerboundPlayerLoadedPacket::read(bitcraft::DecodeStream *stream) {}

void ServerboundPlayerLoadedPacket::write(bitcraft::EncodeStream *stream) {}
}