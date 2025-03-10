//
// Created by shell on 2025/3/9.
//
#include "base/protocol/ClientBoundPackets.h"
namespace bitcraft {
LoginDisconnectPacket::LoginDisconnectPacket() : Packet(0x00) {

}
LoginDisconnectPacket::~LoginDisconnectPacket() {

}

void LoginDisconnectPacket::write(bitcraft::EncodeStream *stream) {

}

void LoginDisconnectPacket::read(bitcraft::DecodeStream *stream) {
  reason = stream->readUTF8String();
}
}