//
// Created by shell on 2025/3/13.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATA_REGISTRYENTRY_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATA_REGISTRYENTRY_H_
#include "base/io/ReadWriteable.h"
#include "base/model/nbt/Tag.h"
namespace bitcraft {
class TagCompound;
class RegistryEntry : public ReadWriteable {
 public:
  ~RegistryEntry() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  std::string identifier;
  std::shared_ptr<Tag> nbt;
};

}

#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATA_REGISTRYENTRY_H_
