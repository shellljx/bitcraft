//
// Created by 李金祥 on 2022/5/29.
//

#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
SetCompressionPacket::SetCompressionPacket() : Packet(0x03), threshold(0) {
}

SetCompressionPacket::~SetCompressionPacket() = default;

void SetCompressionPacket::write(EncodeStream *stream) {

}

void SetCompressionPacket::read(DecodeStream *stream) {
  threshold = stream->readVarInt();
}
}