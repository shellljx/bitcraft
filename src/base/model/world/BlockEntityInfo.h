//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "../../io/ReadWriteable.h"
#include "base/model/nbt/Nbt.h"

namespace bitcraft {
class BlockEntityInfo : public ReadWriteable {
 public:
  BlockEntityInfo();
  ~BlockEntityInfo() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  short x_;
  short z_;
  short y_;
  int type_;
  std::shared_ptr<Tag> nbt_ = nullptr;
};
}