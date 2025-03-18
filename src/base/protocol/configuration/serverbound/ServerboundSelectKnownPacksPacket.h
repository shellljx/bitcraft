//
// Created by shell on 2025/3/13.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CONFIGURATION_SERVERBOUND_SERVERBOUNDSELECTKNOWNPACKSPACKET_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CONFIGURATION_SERVERBOUND_SERVERBOUNDSELECTKNOWNPACKSPACKET_H_
#include "base/protocol/Packet.h"
#include <vector>

namespace bitcraft {
class KnownPack;
class ServerboundSelectKnownPacksPacket : public Packet {
 public:
  ServerboundSelectKnownPacksPacket();
  ~ServerboundSelectKnownPacksPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  void setKnownPacks(const std::vector<std::shared_ptr<KnownPack>>& packs);

 private:
  std::vector<std::shared_ptr<KnownPack>> knownPacks;
};
}

#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CONFIGURATION_SERVERBOUND_SERVERBOUNDSELECTKNOWNPACKSPACKET_H_
