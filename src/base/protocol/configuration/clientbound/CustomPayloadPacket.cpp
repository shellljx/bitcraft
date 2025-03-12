//
// Created by shell on 2025/3/11.
//
#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
CustomPayloadPacket::CustomPayloadPacket() : Packet(0x01) {}

CustomPayloadPacket::~CustomPayloadPacket() {}

void CustomPayloadPacket::read(bitcraft::DecodeStream *stream) {
  identifier = stream->readVarString();
  datas = stream->readByteData(stream->bytesAvailable());
}

void CustomPayloadPacket::write(bitcraft::EncodeStream *stream) {

}
}