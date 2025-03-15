//
// Created by shell on 2025/3/14.
//
#include "base/protocol/ClientBoundPackets.h"
namespace bitcraft {
ClientboundUpdateTagsPacket::ClientboundUpdateTagsPacket() : Packet(0x0D) {}

void readTag(DecodeStream *stream, std::map<std::string, std::vector<int>> &tag) {
  int size = stream->readVarInt();
  for (int i = 0; i < size; i++) {
    std::string key = stream->readVarString();
    int entrySize = stream->readVarInt();
    auto entries = std::vector<int>(entrySize);
    for (int index = 0; index < entrySize; index++) {
      entries[index] = stream->readVarInt();
    }
    tag[key] = entries;
  }
}

void ClientboundUpdateTagsPacket::read(bitcraft::DecodeStream *stream) {
  int size = stream->readVarInt();
  for (int i = 0; i < size; i++) {
    auto tag = std::map<std::string, std::vector<int>>();
    auto key = stream->readVarString();
    readTag(stream, tag);
    tags[key] = tag;
  }
  tags.size();
}

void ClientboundUpdateTagsPacket::write(bitcraft::EncodeStream *stream) {

}
}