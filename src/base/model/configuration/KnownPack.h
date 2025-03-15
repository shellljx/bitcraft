//
// Created by shell on 2025/3/12.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATA_KNOWNPACK_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATA_KNOWNPACK_H_
#include "base/io/ReadWriteable.h"

namespace bitcraft {
class KnownPack : public ReadWriteable {
 public:
  KnownPack() = default;
  ~KnownPack() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  [[nodiscard]] std::string getNameSpace() const {
    return packNameSpace;
  }

  [[nodiscard]] std::string getId() const {
    return packId;
  }

  [[nodiscard]] std::string getVersion() const {
    return packVersion;
  }
 private:
  std::string packNameSpace;
  std::string packId;
  std::string packVersion;
};
}

#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_DATA_KNOWNPACK_H_
