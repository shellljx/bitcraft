//
// Created by shell on 2025/3/22.
//

#include "GlobalPos.h"

namespace bitcraft {
void GlobalPos::read(bitcraft::DecodeStream *stream) {
  dimensionName = stream->readVarString();
  uint64_t value = stream->readUint64();
  int rawX = value >> 38;
  int rawY = value << 52 >> 52;
  int rawZ = value << 26 >> 38;
  x = (rawX & (1 << 25)) ? (rawX - (1 << 26)) : rawX;
  y = (rawY & (1 << 11)) ? (rawY - (1 << 12)) : rawY;
  z = (rawZ & (1 << 25)) ? (rawZ - (1 << 26)) : rawZ;
}

void GlobalPos::write(bitcraft::EncodeStream *stream) {

}
}