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
class BitcraftClient;
class ConnectSession {
 public:
  ConnectSession(BitcraftClient *protocol);
  ~ConnectSession();

  void connect(const std::string& host, int16_t port);
  void post(std::unique_ptr<ByteData> data);

 private:

  void handleConnect(const asio::error_code &error);
  void handleRead(const asio::error_code &error, std::size_t bytesTransferred);
  void handleWrite(const asio::error_code &error);
 private:
  asio::io_service ioService;
  asio::ip::tcp::socket socket;
  BitcraftClient* protocol;
  std::thread loopThread;
  uint8_t *buffer = nullptr;
};
}

#endif //BITCRAFT_MAC_SRC_BASE_PROTOCOL_CONNECTSESSION_H_
