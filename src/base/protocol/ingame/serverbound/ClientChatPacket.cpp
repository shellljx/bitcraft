//
// Created by 李金祥 on 2022/6/1.
//

#include "ClientChatPacket.h"
namespace bitcraft {
ClientChatPacket::ClientChatPacket(const char *message) : Packet(0x03), message_(message) {
}

ClientChatPacket::~ClientChatPacket() noexcept {
}

void ClientChatPacket::write(EncodeStream *stream) {
  stream->writeVarString(message_);
}

void ClientChatPacket::read(DecodeStream *stream) {
}
}