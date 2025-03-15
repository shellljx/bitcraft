//
// Created by shell on 2025/3/15.
//

#include "AcknowledgeFinishConfigurationPacket.h"
namespace bitcraft {
AcknowledgeFinishConfigurationPacket::AcknowledgeFinishConfigurationPacket() : Packet(0x03) {}

void AcknowledgeFinishConfigurationPacket::read(bitcraft::DecodeStream *stream) {}

void AcknowledgeFinishConfigurationPacket::write(bitcraft::EncodeStream *stream) {}
}