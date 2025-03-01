//
// Created by shell on 2025/2/23.
//

#ifndef BITCRAFT_MAC_SRC_BASE_PROTOCOL_CONNECTSESSION_H_
#define BITCRAFT_MAC_SRC_BASE_PROTOCOL_CONNECTSESSION_H_
#include <string>
#include <thread>
#include <asio/ip/tcp.hpp>
#include <asio/io_service.hpp>
#include "base/io/ByteData.h"

namespace bitcraft {
class ConnectSession {
 public:
  class Listener {
   public:
    virtual void handleConnected() {

    }
    virtual void handleInputMessage(std::unique_ptr<ByteData> data) {
    }
  };
  static std::shared_ptr<ConnectSession> Make(const std::string &ip, uint16_t port, Listener *listener);
  ~ConnectSession();
  void connect();
  void post(std::unique_ptr<ByteData> data);

  [[nodiscard]] std::string getHost() const {
    return ip;
  }

  [[nodiscard]] uint16_t getPort() const {
    return port;
  }
 private:
  ConnectSession(std::string ip, uint16_t port, Listener *listener);
  void handleConnect(const asio::error_code &error);
  void handleRead(const asio::error_code &error, std::size_t bytesTransferred);
  void handleWrite(const asio::error_code &error);
 private:
  asio::io_service ioService;
  std::thread loopThread;
  asio::ip::tcp::socket socket;
  uint8_t *buffer;
  Listener *listener;
  std::string ip;
  uint16_t port;
};
}

#endif //BITCRAFT_MAC_SRC_BASE_PROTOCOL_CONNECTSESSION_H_
