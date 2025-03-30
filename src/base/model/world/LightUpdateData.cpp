//
// Created by 李金祥 on 2022/6/11.
//

#include "LightUpdateData.h"
#include "base/protocol/DataTypes.h"

namespace bitcraft {
void LightUpdateData::write(EncodeStream *stream) {
}

std::vector<unsigned long long int> ReadLongArray(DecodeStream *stream, int size) {
  auto array = std::vector<unsigned long long int>(size);
  for (int i = 0; i < size; i++) {
    array[i] = stream->readUint64();
  }
  return array;
}

std::unique_ptr<ByteData> ReadLightData(DecodeStream *stream, int size) {
  return stream->readByteData(size);
}

std::vector<std::unique_ptr<ByteData>> ReadByteDataArray(DecodeStream *stream, int size) {
  auto array = std::vector<std::unique_ptr<ByteData>>(size);
  for (int i = 0; i < size; i++) {
    array[i] = ReadPrefixedBytes(stream, ReadLightData);
  }
  return array;
}

void LightUpdateData::read(DecodeStream *stream) {
  skyYMask = ReadPrefixedArray(stream, ReadLongArray);
  blockYMask = ReadPrefixedArray(stream, ReadLongArray);
  emptySkyYMask = ReadPrefixedArray(stream, ReadLongArray);
  emptyBlockYMask = ReadPrefixedArray(stream, ReadLongArray);
  skyUpdates = ReadPrefixedArray(stream, ReadByteDataArray);
  blockUpdates = ReadPrefixedArray(stream, ReadByteDataArray);
}
}