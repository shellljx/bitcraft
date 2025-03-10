//
// Created by shell on 2025/2/22.
//

#include "MinecraftProtocol.h"
#include <functional>
#include <memory>
#include <utility>
#include "base/protocol/handshake/HandshakePacket.h"
#include "base/protocol/login/serverbound/LoginStartPacket.h"

namespace bitcraft {

std::shared_ptr<MinecraftProtocol> MinecraftProtocol::Make(const std::string &ip,
                                                           int port,
                                                           const std::string &version) {
  if (ip.empty() || version.empty()) {
    return nullptr;
  }
  auto protocol = std::shared_ptr<MinecraftProtocol>(new MinecraftProtocol(ip, port, version));
  return protocol;
}

MinecraftProtocol::MinecraftProtocol(const std::string &ip, int port, std::string version)
    : protocolVersion(std::move(version)), connectSession(nullptr), packetCodec(nullptr) {
  packetCodec = new PacketCodec();
  registerPacket<SetCompressionPacket>();
  registerPacket<LoginSuccessPacket>();
  packetCodec->registerHandler(this);
  connectSession = new ConnectSession(ip, port, this);
}

MinecraftProtocol::~MinecraftProtocol() {
  delete connectSession;
  delete packetCodec;
}

void MinecraftProtocol::handleConnected() {
  packetCodec->setState(ProtocolStatus::LOGIN);
  auto handshakePacket = HandshakePacket::Make(
      769, connectSession->getHost(), connectSession->getPort(), static_cast<int>(ProtocolStatus::LOGIN)
  );
  connectSession->post(packetCodec->encode(handshakePacket));
  auto loginStartPacket = LoginStartPacket::Make("shell");
  connectSession->post(packetCodec->encode(loginStartPacket));
}

void MinecraftProtocol::handle(SetCompressionPacket& packet) {
  packetCodec->setCompressionThreshold(packet.getCompressionThreshold());
}

void MinecraftProtocol::handle(LoginSuccessPacket& packet) {
  auto loginAcknow = std::make_shared<LoginAcknowledgedPacket>();
  connectSession->post(packetCodec->encode(loginAcknow));
}

void MinecraftProtocol::connect() {
  connectSession->connect();
}
}