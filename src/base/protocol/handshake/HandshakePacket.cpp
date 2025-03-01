//
// Created by 李金祥 on 2022/5/28.
//

#include "HandshakePacket.h"

#include <utility>

namespace bitcraft {

std::shared_ptr<HandshakePacket> HandshakePacket::Make(int version, const std::string &host, uint16_t port, int state) {
  if (host.empty())return nullptr;
  auto packet = new HandshakePacket(version, host, port, state);
  return std::shared_ptr<HandshakePacket>(packet);
}
HandshakePacket::HandshakePacket(int version, std::string host, uint16_t port, int nextState)
    : Packet(0), protocolVersion_(version), serverAddr_(std::move(host)), serverPort(port), nextState(nextState) {

}

HandshakePacket::~HandshakePacket() = default;

void HandshakePacket::write(EncodeStream *stream) {
  stream->writeVarInt(protocolVersion_);
  stream->writeVarString(serverAddr_);
  stream->writeUInt16(serverPort);
  stream->writeVarInt(nextState);
}

void HandshakePacket::read(DecodeStream *stream) {
  // no read
}
}