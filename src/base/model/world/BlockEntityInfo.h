//
// Created by 李金祥 on 2022/6/11.
//

#pragma once
#include "../../io/ReadWriteable.h"
#include "base/model/nbt/Nbt.h"

namespace bitcraft {
class BlockEntityInfo : public ReadWriteable {
 public:
  BlockEntityInfo() = default;
  ~BlockEntityInfo() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  int x = 0;
  int z = 0;
  short y = 0;
  int type = 0;
  std::shared_ptr<Tag> nbt = nullptr;
};
}