//
// Created by shell on 2025/2/22.
//

#ifndef BITCRAFT_MAC_MINECRAFTPROTOCOL_H
#define BITCRAFT_MAC_MINECRAFTPROTOCOL_H

#include <string>
#include "ConnectSession.h"
#include "base/codec/PacketCodec.h"
#include "base/protocol/ClientBoundPackets.h"

namespace bitcraft {
using LoinPackets = std::tuple<
    SetCompressionPacket,
    LoginSuccessPacket,
    CustomPayloadPacket,
    UpdateEnabledFeaturesPacket,
    SelectKnownPacksPacket
>;
class MinecraftProtocol : public PacketHandler<MinecraftProtocol, LoinPackets> {
 public:
  static std::shared_ptr<MinecraftProtocol> Make(const std::string &ip, int port, const std::string &version);
  ~MinecraftProtocol();

  void connect();
  void handleConnected();

  [[nodiscard]] PacketCodec *getPacketCodec() const {
    return packetCodec;
  }
 public:
  void handle(SetCompressionPacket &packet);
  void handle(LoginSuccessPacket &packet);
  void handle(CustomPayloadPacket &packet);
  void handle(UpdateEnabledFeaturesPacket &packet);
  void handle(SelectKnownPacksPacket &packet);
  void handle(FinishConfigurationPacket &packet);
 private:
  MinecraftProtocol(const std::string &ip, int port, std::string version);
 private:
  std::string protocolVersion;
  ConnectSession *connectSession;
  PacketCodec *packetCodec;
};
}
#endif //BITCRAFT_MAC_MINECRAFTPROTOCOL_H
