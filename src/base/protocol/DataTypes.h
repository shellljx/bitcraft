//
// Created by shell on 2025/3/23.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATATYPES_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATATYPES_H_
#include "base/io/DecodeStream.h"

namespace bitcraft {

std::string readUUID(DecodeStream* stream);

}
#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATATYPES_H_