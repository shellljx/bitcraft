//
// Created by shell on 2025/3/15.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CONFIGURATION_SERVERBOUND_ACKNOWLEDGEFINISHCONFIGURATIONPACKET_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CONFIGURATION_SERVERBOUND_ACKNOWLEDGEFINISHCONFIGURATIONPACKET_H_
#include "base/protocol/Packet.h"
namespace bitcraft {
class AcknowledgeFinishConfigurationPacket : public Packet {
 public:
  AcknowledgeFinishConfigurationPacket();
  void read(bitcraft::DecodeStream *stream) override;
  void write(bitcraft::EncodeStream *stream) override;
};
}

#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CONFIGURATION_SERVERBOUND_ACKNOWLEDGEFINISHCONFIGURATIONPACKET_H_
