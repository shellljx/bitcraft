//
// Created by shell on 2025/3/23.
//
#include "DataTypes.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

namespace bitcraft {

std::string ReadUUID(DecodeStream *stream) {
  int64_t u1 = stream->readInt64();
  int64_t u2 = stream->readInt64();

  std::stringstream ss;
  ss << std::hex << std::setfill('0')
     << std::setw(8) << ((u1 >> 32) & 0xFFFFFFFF) << "-"
     << std::setw(4) << ((u1 >> 16) & 0xFFFF) << "-"
     << std::setw(4) << (u1 & 0xFFFF) << "-"
     << std::setw(4) << ((u2 >> 48) & 0xFFFF) << "-"
     << std::setw(12) << (u2 & 0xFFFFFFFFFFFF);
  return ss.str();
}

std::unique_ptr<ByteData> ReadPrefixedBytes(DecodeStream *stream,
                                            std::unique_ptr<ByteData>(*reader)(DecodeStream *, int)) {
  auto size = stream->readVarInt();
  if (size <= 0) {
    return nullptr;
  }
  return reader(stream, size);
}
}