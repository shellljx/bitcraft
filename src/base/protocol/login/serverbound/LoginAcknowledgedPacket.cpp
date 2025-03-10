//
// Created by shell on 2025/3/9.
//
#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
LoginAcknowledgedPacket::LoginAcknowledgedPacket() : Packet(0x03) {
}
LoginAcknowledgedPacket::~LoginAcknowledgedPacket() {}

void LoginAcknowledgedPacket::read(bitcraft::DecodeStream *stream) {}

void LoginAcknowledgedPacket::write(bitcraft::EncodeStream *stream) {}

}