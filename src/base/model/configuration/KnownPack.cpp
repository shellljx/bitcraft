//
// Created by shell on 2025/3/12.
//

#include "KnownPack.h"

namespace bitcraft {
void KnownPack::read(bitcraft::DecodeStream *stream) {
  packNameSpace = stream->readVarString();
  packId = stream->readVarString();
  packVersion = stream->readVarString();
}

void KnownPack::write(bitcraft::EncodeStream *stream) {
  stream->writeVarString(packNameSpace);
  stream->writeVarString(packId);
  stream->writeVarString(packVersion);
}
}