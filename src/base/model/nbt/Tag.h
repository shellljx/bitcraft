//
// Created by 李金祥 on 2022/6/10.
//

#pragma once
#include <map>
#include <vector>
#include "base/io/ReadWriteable.h"

namespace bitcraft {

enum class TagType {
  End = 0,
  Byte,
  Short,
  Int,
  Long,
  Float,
  Double,
  ByteArray,
  String,
  List,
  Compound,
  IntArray,
  LongArray
};

class Tag {
 public:
  virtual TagType getType() = 0;
};

class TagByte : public Tag {
 public:
  TagType getType() override {
    return TagType::Byte;
  }
 public:
  char value{};
};

class TagByteArray : public Tag {
 public:
  TagType getType() override {
    return TagType::ByteArray;
  }
 public:
  std::unique_ptr<ByteData> value;
};

class TagCompound : public Tag {
 public:
  TagType getType() override {
    return TagType::Compound;
  }
 public:
  std::map<std::string, std::shared_ptr<Tag>> value;
};

class TagDouble : public Tag {
 public:
  TagType getType() override {
    return TagType::Double;
  }
 public:
  double value{};
};

class TagFloat : public Tag {
 public:
  TagType getType() override {
    return TagType::Float;
  }
 public:
  float value{};
};

class TagInt : public Tag {
 public:
  TagType getType() override {
    return TagType::Int;
  }
 public:
  int value{};
};

class TagIntArray : public Tag {
 public:
  TagType getType() override {
    return TagType::IntArray;
  }
 public:
  std::vector<int> value;
};

class TagList : public Tag {
 public:
  TagType getType() override {
    return TagType::List;
  }
 public:
  std::vector<std::shared_ptr<Tag>> value;
};

class TagLong : public Tag {
 public:
  TagType getType() override {
    return TagType::Long;
  }
 public:
  long long value{};
};

class TagLongArray : public Tag {
 public:
  TagType getType() override {
    return TagType::LongArray;
  }
 public:
  std::vector<long long> value;
};

class TagShort : public Tag {
 public:
  TagType getType() override {
    return TagType::Short;
  }
 public:
  short value{};
};

class TagString : public Tag {
 public:
  TagType getType() override {
    return TagType::String;
  }
 public:
  std::string value;
};
}