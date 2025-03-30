//
// Created by shell on 2025/3/21.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_MODEL_INGAME_PLAYERSPAWNINFO_H_
#define BITCRAFT_LINUX_SRC_BASE_MODEL_INGAME_PLAYERSPAWNINFO_H_
#include "base/io/ReadWriteable.h"

namespace bitcraft {
class GlobalPos;

class PlayerSpawnInfo : public ReadWriteable {
 public:
  ~PlayerSpawnInfo() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  int dimensionType;
  std::string dimensionName;
  long hashedSeed;
  int gameMode;
  int previousGameMode;
  bool isDebug;
  bool isFlat;
  bool hasDeathLocation;
  std::shared_ptr<GlobalPos> deathLocation;
  int portalCooldown;
};
}

#endif //BITCRAFT_LINUX_SRC_BASE_MODEL_INGAME_PLAYERSPAWNINFO_H_
