//
// Created by 李金祥 on 2022/5/29.
//

#include "base/protocol/ClientBoundPackets.h"
#include "base/protocol/DataTypes.h"

namespace bitcraft {
LoginSuccessPacket::LoginSuccessPacket() : Packet(0x02) {
}

LoginSuccessPacket::~LoginSuccessPacket() = default;

void LoginSuccessPacket::write(EncodeStream *stream) {

}

void LoginSuccessPacket::read(DecodeStream *stream) {
  uuid = ReadUUID(stream);
  userName = stream->readVarString();
}
}