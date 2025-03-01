//
// Created by shell on 2025/2/23.
//

#ifndef BITCRAFT_MAC_SRC_BASE_CODEC_CODEC_H_
#define BITCRAFT_MAC_SRC_BASE_CODEC_CODEC_H_
#include "EncryptionCodec.h"
#include "CompressionCodec.h"
#include "SizerCodec.h"
#include "PacketCodec.h"
#include "base/protocol/PacketFactory.h"
#include "base/protocol/Packet.h"

namespace bitcraft {
class Codec {
 public:
  Codec();
  void decode(std::unique_ptr<ByteData> data,
                                 const std::function<void(std::unique_ptr<Packet> packet)> &packetFunc);
  std::unique_ptr<ByteData> encode(std::shared_ptr<Packet> packet);
  void setState(ProtocolStatus state);
 private:
  void decodePacket(std::unique_ptr<ByteData> data,
                    const std::function<void(std::unique_ptr<Packet> packet)> &packetFunc);
 private:
  std::shared_ptr<EncryptionCodec> encryptionCodec;
  std::shared_ptr<CompressionCodec> compressionCodec;
  std::shared_ptr<SizerCodec> sizerCodec;
  std::shared_ptr<PacketCodec> packetCodec;
  std::shared_ptr<EncodeStream> inputStream;
  std::shared_ptr<PacketFactory> packetFactory;
};
}

#endif //BITCRAFT_MAC_SRC_BASE_CODEC_CODEC_H_
