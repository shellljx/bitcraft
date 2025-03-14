//
// Created by 李金祥 on 2022/6/7.
//

#include <memory>
#include "base/protocol/ClientBoundPackets.h"
#include "base/model/nbt/Nbt.h"
#include "base/model/world/BlockEntityInfo.h"
#include "base/model/world/LightUpdateData.h"

namespace bitcraft {
ServerChunkDataPacket::ServerChunkDataPacket() : Packet(0x22), x_(0), z_(0) {
}

ServerChunkDataPacket::~ServerChunkDataPacket() = default;

void ServerChunkDataPacket::write(EncodeStream *stream) {

}

void ServerChunkDataPacket::read(DecodeStream *stream) {
  x_ = stream->readInt32();
  z_ = stream->readInt32();
  //nbt
  heightMaps_ = ReadNbt(stream);
  //chunk data size
  const int datSize = stream->readVarInt();
  //chunk data
  chunkData_ = stream->readByteData(datSize);

  //block entity
  const int num_entities = stream->readVarInt();
  blockEntities_ = std::vector<std::unique_ptr<BlockEntityInfo>>(num_entities);
  for (int i = 0; i < num_entities; ++i) {
    blockEntities_[i] = std::make_unique<BlockEntityInfo>();
    blockEntities_[i]->read(stream);
  }
  lightUpdateData_ = std::make_unique<LightUpdateData>();
  lightUpdateData_->read(stream);
}
}