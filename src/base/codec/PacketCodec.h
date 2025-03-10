//
// Created by shell on 2025/2/23.
//

#ifndef BITCRAFT_MAC_SRC_BASE_CODEC_CODEC_H_
#define BITCRAFT_MAC_SRC_BASE_CODEC_CODEC_H_
#include "SizerCodec.h"
#include "base/protocol/Packet.h"
#include <typeindex>

namespace bitcraft {
class AbsPacketHandler {
 public:
  virtual ~AbsPacketHandler() = default;
  virtual void handlePacket(Packet &) = 0;
};

template<typename Derived>
class PacketHandler : public AbsPacketHandler {
 public:
  void handlePacket(Packet &packet) override {
    auto it = handlers.find(std::type_index(typeid(packet)));
    if (it != handlers.end()) {
      it->second(packet);
    }
  }

 protected:
  template<typename PacketType>
  void registerPacket() {
    handlers[std::type_index(typeid(PacketType))] = [this](Packet &packet) {
      handle(static_cast<PacketType &>(packet));
    };
  }

 private:
  template<typename PacketType>
  void handle(PacketType &packet) {
    static_assert(std::is_base_of_v<Packet, PacketType>, "PacketType must derive from Packet");
    static_cast<Derived *>(this)->handle(packet);
  }

 private:
  std::unordered_map<std::type_index, std::function<void(Packet &)>> handlers;
};

enum class ProtocolStatus { NONE = -1, HANDSHAKE = 0, STATUS = 1, LOGIN = 2, PLAY = 3 };

class EncryptionCodec;
class CompressionCodec;

class PacketDispatcher {
 public:
  void registerHandler(AbsPacketHandler *handler) {
    handlers.push_back(handler);
  }

  void dispatchPacket(Packet &packet) {
    for (auto &handler : handlers) {
      handler->handlePacket(packet);
    }
  }

 private:
  std::vector<AbsPacketHandler *> handlers;
};

class PacketCodec : public PacketDispatcher {
 public:
  PacketCodec();
  void decode(std::unique_ptr<ByteData> data);
  std::unique_ptr<ByteData> encode(std::shared_ptr<Packet> packet);
  void setState(ProtocolStatus state);
  void setCompressionThreshold(int threshold);
 private:
  void decodePacket(const std::unique_ptr<ByteData> data);
 private:
  std::shared_ptr<EncryptionCodec> encryptionCodec;
  std::shared_ptr<CompressionCodec> compressionCodec;
  std::shared_ptr<EncodeStream> inputStream;
  ProtocolStatus status = ProtocolStatus::NONE;
};
}

#endif //BITCRAFT_MAC_SRC_BASE_CODEC_CODEC_H_
