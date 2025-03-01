//
// Created by shell on 2025/2/23.
//

#include "Codec.h"

namespace bitcraft {
#define INPUT_BUFFER_CAPACITY 256

Codec::Codec() {
  inputStream = std::make_shared<EncodeStream>(INPUT_BUFFER_CAPACITY);
  compressionCodec = std::make_shared<CompressionCodec>();
  encryptionCodec = std::make_shared<EncryptionCodec>();
  sizerCodec = std::make_shared<SizerCodec>();
  packetCodec = std::make_shared<PacketCodec>();
  packetFactory = std::make_shared<PacketFactory>();
}
void Codec::decode(std::unique_ptr<ByteData> data,
                                      const std::function<void(std::unique_ptr<Packet> packet)> &packetFunc) {
  auto decrypted = encryptionCodec->decode(std::move(data));
  inputStream->writeByteData(decrypted.get());
  auto encoded = inputStream->release();
  auto decodeStream = DecodeStream(encoded->data(), encoded->length());
  while (decodeStream.bytesAvailable() > 0) {
    auto packetStream = sizerCodec->decode(decodeStream);
    if (packetStream.data() == nullptr) {
      break;
    }
    auto packetByteData = compressionCodec->decode(packetStream);
    decodePacket(std::move(packetByteData), packetFunc);
  }
}

void Codec::decodePacket(std::unique_ptr<ByteData> data,
                         const std::function<void(std::unique_ptr<Packet> packet)> &packetFunc) {
  auto decodeStream = DecodeStream(data->data(), data->length());
  int packetId = decodeStream.readVarInt();
  auto packet = packetFactory->createClientBoundPacket(packetId);
  if (packet == nullptr) {
    return;
  }
  packet->read(&decodeStream);
  packetFunc(std::move(packet));
}

std::unique_ptr<ByteData> Codec::encode(std::shared_ptr<Packet> packet) {
  auto encodeStream = EncodeStream();
  encodeStream.writeVarInt(packet->getPacketId());
  packet->write(&encodeStream);
  auto encodeData = encodeStream.release();

  encodeStream.writeVarInt(encodeData->length());
  encodeStream.writeByteData(encodeData.get());
  encodeData = encodeStream.release();
  return encodeData;
}

void Codec::setState(ProtocolStatus state) {
  packetFactory->setProtocolStatus(state);
}
}