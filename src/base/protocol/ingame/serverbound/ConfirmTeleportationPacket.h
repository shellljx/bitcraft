//
// Created by shell on 2025/3/25.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_CONFIRMTELEPORTATIONPACKET_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_CONFIRMTELEPORTATIONPACKET_H_

#include "base/protocol/Packet.h"

namespace bitcraft {
class ConfirmTeleportationPacket : public Packet {
 public:
  explicit ConfirmTeleportationPacket(int id) : Packet(0x00), teleportId(id) {};
  ~ConfirmTeleportationPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  int teleportId;
};
}

#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_CONFIRMTELEPORTATIONPACKET_H_
