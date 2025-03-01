//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "Tag.h"

namespace bitcraft {
class TagFloat : public Tag {
 public:
  explicit TagFloat(const std::string &name);
  ~TagFloat() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
  TagType getType() override;

 private:
  float value_;
};
}
