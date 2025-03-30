//
// Created by shell on 2025/3/22.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_MODEL_INGAME_GLOBALPOS_H_
#define BITCRAFT_LINUX_SRC_BASE_MODEL_INGAME_GLOBALPOS_H_

#include "base/io/ReadWriteable.h"

namespace bitcraft {
class GlobalPos : public ReadWriteable{
 public:
  ~GlobalPos() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  std::string dimensionName;
  int x;
  int y;
  int z;
};
}

#endif //BITCRAFT_LINUX_SRC_BASE_MODEL_INGAME_GLOBALPOS_H_
