//
// Created by 李金祥 on 2022/5/31.
//

#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
ServerKeepAlivePacket::ServerKeepAlivePacket() : Packet(0x21), keepAliveId_(0) {
}

ServerKeepAlivePacket::~ServerKeepAlivePacket() = default;

void ServerKeepAlivePacket::write(EncodeStream *stream) {

}

void ServerKeepAlivePacket::read(DecodeStream *stream) {
  keepAliveId_ = stream->readInt64();
}
}