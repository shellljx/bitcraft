//
// Created by shell on 2025/2/22.
//

#include "BitcraftClient.h"
#include "base/utils/ScopedLock.h"
#include "base/utils/LockGuard.h"
#include <functional>
#include <utility>
#include "base/protocol/handshake/HandshakePacket.h"
#include "base/protocol/login/serverbound/LoginStartPacket.h"
#include "base/protocol/configuration/serverbound/ServerboundSelectKnownPacksPacket.h"
#include "base/protocol/configuration/serverbound/AcknowledgeFinishConfigurationPacket.h"
#include "base/model/configuration/KnownPack.h"
#include "base/utils/Log.h"

namespace bitcraft {

std::shared_ptr<BitcraftClient> BitcraftClient::Make(int version) {
  if (version <= 0) {
    return nullptr;
  }
  auto protocol = std::shared_ptr<BitcraftClient>(new BitcraftClient(version));
  return protocol;
}

BitcraftClient::BitcraftClient(int version) : protocolVersion(version) {
  registerPackets();
  rootLocker = std::make_shared<std::mutex>();
  mcRenderer = std::make_shared<McRenderer>();
  packetCodec = new PacketCodec();
  packetCodec->registerHandler(this);
  connectSession = new ConnectSession(this);
}

BitcraftClient::~BitcraftClient() {
  delete connectSession;
  delete packetCodec;
}

void BitcraftClient::handleConnected() {
  packetCodec->setState(ProtocolStatus::LOGIN);
  auto handshakePacket = HandshakePacket::Make(
      769,
      serverHost,
      serverPort,
      static_cast<int>(ProtocolStatus::LOGIN)
  );
  connectSession->post(packetCodec->encode(*handshakePacket));
  auto loginStartPacket = LoginStartPacket::Make("shell");
  connectSession->post(packetCodec->encode(*loginStartPacket));
}

bool BitcraftClient::flush() {
  LockGuard autoLock(rootLocker);
  return flushInternal();
}

bool BitcraftClient::flushInternal() {
  if (craftSurface == nullptr) {
    return false;
  }
  if (!craftSurface->draw(mcRenderer)) {
    return false;
  }
  return true;
}

void BitcraftClient::setSurface(std::shared_ptr<CraftSurface> newSurface) {
  auto locker = newSurface ? newSurface->rootLocker : nullptr;
  ScopedLock autoLock(rootLocker, locker);
  if (craftSurface == newSurface) {
    return;
  }
  if (craftSurface) {
    craftSurface->rootLocker = std::make_shared<std::mutex>();
  }
  craftSurface = newSurface;
  if (craftSurface) {
    craftSurface->rootLocker = rootLocker;
  }
}

void BitcraftClient::handle(SetCompressionPacket &packet) {
  LOGI("handle packet %s", "SetCompressionPacket");
  packetCodec->setCompressionThreshold(packet.getCompressionThreshold());
}

void BitcraftClient::handle(LoginSuccessPacket &packet) {
  LOGI("handle packet %s", "LoginSuccessPacket");
  packetCodec->setState(ProtocolStatus::Configuration);
  auto loginAcknow = LoginAcknowledgedPacket();
  connectSession->post(packetCodec->encode(loginAcknow));
}

void BitcraftClient::handle(bitcraft::CustomPayloadPacket &packet) {
  LOGI("handle packet %s", "CustomPayloadPacket");
}

void BitcraftClient::handle(bitcraft::UpdateEnabledFeaturesPacket &packet) {
  LOGI("handle packet %s", "UpdateEnabledFeaturesPacket");
}

void BitcraftClient::handle(bitcraft::SelectKnownPacksPacket &packet) {
  auto sendP = std::make_shared<ServerboundSelectKnownPacksPacket>();
  sendP->setKnownPacks({});
  connectSession->post(packetCodec->encode(*sendP));
}

void BitcraftClient::handle(bitcraft::FinishConfigurationPacket &packet) {
  auto finishConfiguration = AcknowledgeFinishConfigurationPacket();
  connectSession->post(packetCodec->encode(finishConfiguration));
  packetCodec->setState(ProtocolStatus::PLAY);
}

void BitcraftClient::connect(const std::string &host, int16_t port) {
  serverHost = host;
  serverPort = port;
  connectSession->connect(host, port);
}
}