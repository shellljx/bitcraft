//
// Created by shell on 2025/3/25.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_SERVERBOUNDCHATPACKET_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_SERVERBOUNDCHATPACKET_H_
#include "base/protocol/Packet.h"

namespace bitcraft {
class ServerboundChatPacket: public Packet{
 public:
  ServerboundChatPacket(): Packet(0x07){}
  ~ServerboundChatPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  std::string  message;
  long long int timeStamp;
  long long int salt;

};
}

#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_INGAME_SERVERBOUND_SERVERBOUNDCHATPACKET_H_
