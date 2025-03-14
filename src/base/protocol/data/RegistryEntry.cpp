//
// Created by shell on 2025/3/13.
//

#include "RegistryEntry.h"
#include "base/model/nbt/TagCompound.h"
namespace bitcraft {
void RegistryEntry::read(bitcraft::DecodeStream *stream) {
  identifier = stream->readVarString();
  auto present = stream->readBoolean();
  if (present) {
    nbt = TagCompound::Create(stream);
  }
}
void RegistryEntry::write(bitcraft::EncodeStream *stream) {}
}