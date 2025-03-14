//
// Created by shell on 2025/3/14.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_MODEL_NBT_NBT_H_
#define BITCRAFT_LINUX_SRC_BASE_MODEL_NBT_NBT_H_
#include "Tag.h"
namespace bitcraft {
std::shared_ptr<Tag> ReadNbt(DecodeStream *stream);
}

#endif //BITCRAFT_LINUX_SRC_BASE_MODEL_NBT_NBT_H_
