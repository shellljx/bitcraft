//
// Created by 李金祥 on 2022/6/7.
//

#include <memory>
#include "base/protocol/ClientBoundPackets.h"
#include "base/model/nbt/Nbt.h"
#include "base/model/world/BlockEntityInfo.h"
#include "base/model/world/LightUpdateData.h"

namespace bitcraft {
ServerChunkDataPacket::ServerChunkDataPacket() : Packet(0x28) {
}

ServerChunkDataPacket::~ServerChunkDataPacket() = default;

void ServerChunkDataPacket::write(EncodeStream *stream) {

}

void ServerChunkDataPacket::read(DecodeStream *stream) {
  x = stream->readInt32();
  z = stream->readInt32();
  //nbt
  heightMaps = ReadNbt(stream);
  //chunk data size
  const int datSize = stream->readVarInt();
  //chunk data
  chunkData = stream->readByteData(datSize);

  //block entity
  const int num_entities = stream->readVarInt();
  blockEntities = std::vector<std::unique_ptr<BlockEntityInfo>>(num_entities);
  for (int i = 0; i < num_entities; ++i) {
    blockEntities[i] = std::make_unique<BlockEntityInfo>();
    blockEntities[i]->read(stream);
  }
  lightUpdateData = std::make_unique<LightUpdateData>();
  lightUpdateData->read(stream);
}
}