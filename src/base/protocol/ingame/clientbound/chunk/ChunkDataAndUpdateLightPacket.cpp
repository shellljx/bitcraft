//
// Created by 李金祥 on 2022/6/7.
//

#include <memory>
#include "base/protocol/ClientBoundPackets.h"
#include "base/model/nbt/Nbt.h"
#include "base/model/world/BlockEntityInfo.h"
#include "base/model/world/LightUpdateData.h"
#include "base/protocol/DataTypes.h"

namespace bitcraft {
ChunkDataAndUpdateLightPacket::ChunkDataAndUpdateLightPacket() : Packet(0x28) {
}

ChunkDataAndUpdateLightPacket::~ChunkDataAndUpdateLightPacket() = default;

std::unique_ptr<ByteData> ReadChunkData(DecodeStream *stream, int size) {
  return stream->readByteData(size);
}

std::vector<std::unique_ptr<BlockEntityInfo>> ReadBlockEntity(DecodeStream *stream, int size) {
  auto blockEntities = std::vector<std::unique_ptr<BlockEntityInfo>>(size);
  for (int i = 0; i < size; ++i) {
    blockEntities[i] = std::make_unique<BlockEntityInfo>();
    blockEntities[i]->read(stream);
  }
  return blockEntities;
}

void ChunkDataAndUpdateLightPacket::write(EncodeStream *stream) {

}

void ChunkDataAndUpdateLightPacket::read(DecodeStream *stream) {
  x = stream->readInt32();
  z = stream->readInt32();
  heightMaps = ReadNbt(stream);
  chunkData_ = ReadPrefixedBytes(stream, ReadChunkData);
  blockEntities = ReadPrefixedArray(stream, ReadBlockEntity);
  lightUpdateData = std::make_unique<LightUpdateData>();
  lightUpdateData->read(stream);
}

DecodeStream ChunkDataAndUpdateLightPacket::chunkData() const {
  return {chunkData_->data(), static_cast<uint32_t>(chunkData_->length())};
}
}