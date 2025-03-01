//
// Created by shell on 2025/2/22.
//

#include "MinecraftProtocol.h"
#include <functional>
#include <memory>
#include <utility>
#include "base/io/DecodeStream.h"
#include "base/protocol/handshake/HandshakePacket.h"
#include "base/protocol/status/client/StatusRequestPacket.h"
#include "base/protocol/status/server/StatusResponsePacket.h"
#include "base/protocol/login/client/LoginStartPacket.h"

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
    : protocolVersion(std::move(version)) {
  session = ConnectSession::Make(ip, port, this);
  codec = std::make_shared<Codec>();
}

MinecraftProtocol::~MinecraftProtocol() {

}

void MinecraftProtocol::handleConnected() {
  codec->setState(ProtocolStatus::LOGIN);
  auto handshakePacket = HandshakePacket::Make(
      769, session->getHost(), session->getPort(), static_cast<int>(ProtocolStatus::LOGIN)
  );
  session->post(codec->encode(handshakePacket));
  auto loginStartPacket = LoginStartPacket::Make("shell");
  session->post(codec->encode(loginStartPacket));
}

void MinecraftProtocol::handleInputMessage(std::unique_ptr<ByteData> data) {
  codec->decode(std::move(data), [=](std::unique_ptr<Packet> packet) -> void {
    auto id = packet->getPacketId();
    std::printf("input %d\n", id);
  });
}

void MinecraftProtocol::connect() {
  session->connect();
}
}