//
// Created by shell on 2025/2/22.
//

#ifndef BITCRAFT_MAC_MINECRAFTPROTOCOL_H
#define BITCRAFT_MAC_MINECRAFTPROTOCOL_H

#include <string>
#include "ConnectSession.h"
#include "base/codec/PacketCodec.h"
#include "base/protocol/ClientBoundPackets.h"
#include "rendering/CraftSurface.h"
#include "rendering/McRenderer.h"
#include "rendering/AssetManager.h"

namespace bitcraft {
using LoinPackets = std::tuple<
    SetCompressionPacket,
    LoginSuccessPacket,
    CustomPayloadPacket,
    UpdateEnabledFeaturesPacket,
    SelectKnownPacksPacket,
    FinishConfigurationPacket,
    ClientboundLoginPacket,
    ClientboundSynchronizePlayerPositionPacket
>;
class BitcraftClient : public PacketHandler<BitcraftClient, LoinPackets> {
 public:
  static std::shared_ptr<BitcraftClient> Make(int version);
  ~BitcraftClient();

  void connect(const std::string &host, int16_t port);
  void handleConnected();

  bool flush();

  [[nodiscard]] PacketCodec *getPacketCodec() const {
    return packetCodec;
  }

  void setSurface(std::shared_ptr<CraftSurface> newSurface);
 private:
  void handle(SetCompressionPacket &packet);
  void handle(LoginSuccessPacket &packet);
  void handle(CustomPayloadPacket &packet);
  void handle(UpdateEnabledFeaturesPacket &packet);
  void handle(SelectKnownPacksPacket &packet);
  void handle(FinishConfigurationPacket &packet);
  void handle(ClientboundLoginPacket &packet);
  void handle(ClientboundSynchronizePlayerPositionPacket &packet);
 private:
  BitcraftClient(int version);
  bool flushInternal();
 private:
  int protocolVersion;
  std::shared_ptr<std::mutex> rootLocker = nullptr;
  std::shared_ptr<CraftSurface> craftSurface = nullptr;
  ConnectSession *connectSession = nullptr;
  PacketCodec *packetCodec = nullptr;
  std::shared_ptr<McRenderer> mcRenderer = nullptr;
  std::shared_ptr<AssetManager> assetManager;
  std::string serverHost;
  int16_t serverPort = 0;

  friend class PacketHandler;
};
}
#endif //BITCRAFT_MAC_MINECRAFTPROTOCOL_H
