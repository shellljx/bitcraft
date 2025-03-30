//
// Created by shell on 2025/3/23.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATATYPES_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATATYPES_H_
#include "base/io/DecodeStream.h"

namespace bitcraft {

std::string ReadUUID(DecodeStream *stream);

std::unique_ptr<ByteData> ReadPrefixedBytes(DecodeStream *stream,
                                            std::unique_ptr<ByteData>(*reader)(DecodeStream *, int));

template<typename T>
std::vector<T> ReadPrefixedArray(DecodeStream *stream, std::vector<T>(*reader)(DecodeStream *, int)) {
  auto size = stream->readVarInt();
  if (size <= 0) {
    return std::vector<T>(0);
  }
  return reader(stream, size);
}
}
#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATATYPES_H_