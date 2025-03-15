//
// Created by shell on 2025/3/14.
//
#include "Nbt.h"

namespace bitcraft {
#define NBT_MAX_DEPTH 512

std::shared_ptr<Tag> ReadTags(DecodeStream *stream, TagType type, int depth = 0);

void ReadTagCompound(DecodeStream *stream, TagCompound *compound, int depth = 0) {// NOLINT
  if (depth > NBT_MAX_DEPTH) {
    throw std::runtime_error("NBT structure too deeply nested");
  }
  while (true) {
    const auto type = (TagType) stream->readUint8();
    if (type == TagType::End) {
      break;
    }
    std::string name = stream->readUtfString();
    auto tag = ReadTags(stream, type, depth + 1);
    compound->value[name] = tag;
  }
}

void ReadTagList(DecodeStream *stream, TagList *tag, int depth = 0) {// NOLINT
  if (depth > NBT_MAX_DEPTH) {
    throw std::runtime_error("NBT structure too deeply nested");
  }
  auto listType = (TagType) stream->readUint8();
  int count = stream->readInt32();
  tag->value = std::vector<std::shared_ptr<Tag>>(count);
  for (int i = 0; i < count; ++i) {
    tag->value[i] = ReadTags(stream, listType, depth + 1);
  }
}

std::shared_ptr<Tag> ReadTags(DecodeStream *stream, TagType type, int depth) {// NOLINT
  if (depth > NBT_MAX_DEPTH) {
    throw std::runtime_error("NBT tag nesting exceeds maximum depth");
  }
  switch (type) {
    case TagType::Byte: {
      auto tag = std::make_shared<TagByte>();
      tag->value = stream->readInt8();
      return tag;
    }
    case TagType::Short: {
      auto tag = std::make_shared<TagShort>();
      tag->value = stream->readInt16();
      return tag;
    }
    case TagType::Int: {
      auto tag = std::make_shared<TagInt>();
      tag->value = stream->readInt32();
      return tag;
    }
    case TagType::Long: {
      auto tag = std::make_shared<TagLong>();
      tag->value = stream->readInt64();
      return tag;
    }
    case TagType::Float: {
      auto tag = std::make_shared<TagFloat>();
      tag->value = stream->readFloat();
      return tag;
    }
    case TagType::Double: {
      auto tag = std::make_shared<TagDouble>();
      tag->value = stream->readDouble();
      return tag;
    }
    case TagType::ByteArray: {
      auto tag = std::make_shared<TagByteArray>();
      auto length = stream->readInt32();
      tag->value = stream->readByteData(length);
      return tag;
    }
    case TagType::String: {
      auto tag = std::make_shared<TagString>();
      tag->value = stream->readUtfString();
      return tag;
    }
    case TagType::List: {
      auto tag = std::make_shared<TagList>();
      ReadTagList(stream, tag.get(), depth);
      return tag;
    }
    case TagType::Compound: {
      auto tag = std::make_shared<TagCompound>();
      ReadTagCompound(stream, tag.get(), depth);
      return tag;
    }
    case TagType::IntArray: {
      auto tag = std::make_shared<TagIntArray>();
      const auto count = stream->readInt32();
      for (int i = 0; i < count; ++i) {
        tag->value.push_back(stream->readInt32());
      }
      return tag;
    }
    case TagType::LongArray: {
      auto tag = std::make_shared<TagLongArray>();
      auto count = stream->readInt32();
      tag->value = std::vector<long long>(count);
      for (int i = 0; i < count; ++i) {
        tag->value[i] = stream->readInt64();
      }
      return tag;
    }
    default:return nullptr;
  }
}

std::shared_ptr<Tag> ReadNbt(DecodeStream *stream) {
  const auto type = (TagType) stream->readUint8();
  if (type == TagType::Compound) {
    //Since 1.20.2 (Protocol 764) NBT sent over the network has been updated to exclude the name from the root TAG_COMPOUND
    return ReadTags(stream, type);
  }
  return nullptr;
}
}