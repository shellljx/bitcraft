//
// Created by 李金祥 on 2022/6/11.
//

#include "BlockEntityInfo.h"

namespace bitcraft {
void BlockEntityInfo::write(EncodeStream *stream) {
}

void BlockEntityInfo::read(DecodeStream *stream) {
  uint8_t xz = stream->readUint8();
  x = xz >> 4;
  z = xz & 15;
  y = stream->readInt16();
  type = stream->readVarInt();
  nbt = ReadNbt(stream);
}
}