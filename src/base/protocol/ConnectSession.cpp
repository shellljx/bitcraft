//
// Created by shell on 2025/2/23.
//

#include "ConnectSession.h"
#include <asio/connect.hpp>
#include <asio/write.hpp>
#include <utility>

namespace bitcraft {
std::shared_ptr<ConnectSession> ConnectSession::Make(const std::string &ip, uint16_t port, Listener *listener) {
  return std::shared_ptr<ConnectSession>(new ConnectSession(ip, port, listener));
}

ConnectSession::ConnectSession(std::string ip, uint16_t port, Listener *listener)
    : socket(ioService), ip(std::move(ip)), port(port), listener(listener) {
  buffer = new uint8_t[512];
}

ConnectSession::~ConnectSession() {
  if (loopThread.joinable()) {
    loopThread.joinable();
  }
  delete[] buffer;
  buffer = nullptr;
}

void ConnectSession::connect() {
  asio::ip::tcp::resolver resolver(ioService);
  asio::ip::tcp::resolver::query query(ip, std::to_string(port));
  asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
  asio::async_connect(socket, iterator, std::bind(&ConnectSession::handleConnect, this, std::placeholders::_1));
  loopThread = std::thread([&] {
    std::printf("loop start\n");
    ioService.run();
    std::printf("loop exit\n");
  });
}

void ConnectSession::post(std::unique_ptr<ByteData> data) {
  asio::async_write(socket,
                    asio::buffer(data->data(), data->length()),
                    std::bind(&ConnectSession::handleWrite, this, std::placeholders::_1));
}

void ConnectSession::handleConnect(const asio::error_code &error) {
  if (!error) {
    listener->handleConnected();
    socket.async_read_some(asio::buffer(buffer, 512),
                           std::bind(&ConnectSession::handleRead,
                                     this,
                                     std::placeholders::_1,
                                     std::placeholders::_2));
  } else {

  }
}

void ConnectSession::handleRead(const asio::error_code &error, std::size_t bytesTransferred) {
  if (!error) {
    listener->handleInputMessage(ByteData::MakeWithoutCopy(buffer, bytesTransferred));
  }
}

void ConnectSession::handleWrite(const asio::error_code &error) {
  if (!error) {
    socket.async_read_some(asio::buffer(buffer, 512),
                           std::bind(&ConnectSession::handleRead,
                                     this,
                                     std::placeholders::_1,
                                     std::placeholders::_2));
  }
}

}