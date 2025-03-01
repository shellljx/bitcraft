//
// Created by shell on 2025/2/22.
//

#ifndef BITCRAFT_MAC_MINECRAFTPROTOCOL_H
#define BITCRAFT_MAC_MINECRAFTPROTOCOL_H

#include <string>
#include "ConnectSession.h"
#include "base/codec/Codec.h"

namespace bitcraft {
class MinecraftProtocol : ConnectSession::Listener {
 public:
  static std::shared_ptr<MinecraftProtocol> Make(const std::string &ip, int port, const std::string &version);
  ~MinecraftProtocol();

  void connect();
 protected:
  void handleConnected() override;
  void handleInputMessage(std::unique_ptr<ByteData> data) override;
 private:
  MinecraftProtocol(const std::string &ip, int port, std::string version);
 private:
  std::string protocolVersion;
  std::shared_ptr<ConnectSession> session;
  std::shared_ptr<Codec> codec;
};
}
#endif //BITCRAFT_MAC_MINECRAFTPROTOCOL_H
