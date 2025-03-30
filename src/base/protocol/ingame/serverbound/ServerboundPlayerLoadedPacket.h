//
// Created by shell on 2025/3/23.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_SERVERBOUNDPLAYERLOADEDPACKET_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_SERVERBOUNDPLAYERLOADEDPACKET_H_

#include "base/protocol/Packet.h"

namespace bitcraft {
class ServerboundPlayerLoadedPacket : public Packet {
 public:
  ServerboundPlayerLoadedPacket();
  ~ServerboundPlayerLoadedPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
};
}

#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_SERVERBOUNDPLAYERLOADEDPACKET_H_
