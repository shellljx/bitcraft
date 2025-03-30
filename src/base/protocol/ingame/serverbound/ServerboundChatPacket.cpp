//
// Created by shell on 2025/3/25.
//

#include "ServerboundChatPacket.h"
namespace bitcraft {
void ServerboundChatPacket::read(bitcraft::DecodeStream *stream) {
}

void ServerboundChatPacket::write(bitcraft::EncodeStream *stream) {
  stream->writeVarString("hello world");
  stream->writeInt64(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
  stream->writeInt64(0);
  stream->writeBoolean(false);
  stream->writeVarInt(0);
  auto datas = new uint8_t[3];
  stream->writeBytes(datas,3);
}
}