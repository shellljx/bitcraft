//
// Created by 李金祥 on 2022/5/29.
//

#include "base/codec/PacketCodec.h"
#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {

std::shared_ptr<Packet> createClientBoundPacket(int id, ProtocolStatus status) {
  if (status == ProtocolStatus::STATUS) {
    switch (id) {
      case 0x00: return std::shared_ptr<Packet>(new StatusResponsePacket());
      case 0x01:return std::shared_ptr<Packet>(new StatusPongPacket());
      default:return nullptr;
    }
  } else if (status == ProtocolStatus::LOGIN) {
    switch (id) {
      case 0x00:return std::shared_ptr<Packet>(new LoginDisconnectPacket());
      case 0x02:return std::shared_ptr<Packet>(new LoginSuccessPacket());
      case 0x03:return std::shared_ptr<Packet>(new SetCompressionPacket());
      default:return nullptr;
    }
  } else if (status == ProtocolStatus::PLAY) {
    switch (id) {
      case 0x1C:return std::shared_ptr<Packet>(new ClientboundSetPlayerPositionPacket());
      case 0x21:return std::shared_ptr<Packet>(new ServerKeepAlivePacket());
      case 0x28:return std::shared_ptr<Packet>(new ChunkDataAndUpdateLightPacket());
      case 0x2C: return std::shared_ptr<Packet>(new ClientboundLoginPacket());
      case 0x42:return std::shared_ptr<Packet>(new ClientboundSynchronizePlayerPositionPacket);
      default:return nullptr;
    }
  } else if (status == ProtocolStatus::Configuration) {
    switch (id) {
      case 0x00:return nullptr;
      case 0x01:return std::shared_ptr<Packet>(new CustomPayloadPacket());
      case 0x03:return std::shared_ptr<Packet>(new FinishConfigurationPacket());
      case 0x07:return std::shared_ptr<Packet>(new ClientboundRegistryDataPacket());
      case 0x0C:return std::shared_ptr<Packet>(new UpdateEnabledFeaturesPacket());
      case 0x0D:return std::shared_ptr<Packet>(new ClientboundUpdateTagsPacket());
      case 0x0E:return std::shared_ptr<Packet>(new SelectKnownPacksPacket());
      default:return nullptr;
    }
  } else {
    return nullptr;
  }
}
}