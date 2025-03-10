//
// Created by shell on 2025/2/23.
//

#include "PacketCodec.h"
#include "EncryptionCodec.h"
#include "CompressionCodec.h"
#include "base/protocol/PacketFactory.h"

namespace bitcraft {
#define INPUT_BUFFER_CAPACITY 256

PacketCodec::PacketCodec() {
  inputStream = std::make_shared<EncodeStream>(INPUT_BUFFER_CAPACITY);
  compressionCodec = std::make_shared<CompressionCodec>();
  encryptionCodec = std::make_shared<EncryptionCodec>();
}
void PacketCodec::decode(std::unique_ptr<ByteData> data) {
  auto decrypted = encryptionCodec->decode(std::move(data));
  inputStream->writeByteData(decrypted.get());
  auto encoded = inputStream->release();
  auto decodeStream = DecodeStream(encoded->data(), encoded->length());
  while (decodeStream.bytesAvailable() > 0) {
    auto packetStream = sizerDecode(decodeStream);
    if (packetStream.data() == nullptr) {
      break;
    }
    auto packetByteData = compressionCodec->decode(packetStream);
    decodePacket(std::move(packetByteData));
  }
}

void PacketCodec::decodePacket(const std::unique_ptr<ByteData> data) {
  auto decodeStream = DecodeStream(data->data(), data->length());
  int packetId = decodeStream.readVarInt();
  auto packet = createClientBoundPacket(packetId, status);
  if (packet == nullptr) {
    return;
  }
  packet->read(&decodeStream);
  dispatchPacket(*packet);
}

std::unique_ptr<ByteData> PacketCodec::encode(std::shared_ptr<Packet> packet) {
  auto encodeStream = EncodeStream();
  //write Packet ID
  encodeStream.writeVarInt(packet->getPacketId());
  //write Packet
  packet->write(&encodeStream);
  auto encodeData = compressionCodec->encode(encodeStream.release());

  //write sizer
  encodeStream.writeVarInt(encodeData->length());
  encodeStream.writeByteData(encodeData.get());
  encodeData = encodeStream.release();
  return encodeData;
}

void PacketCodec::setState(ProtocolStatus state) {
  this->status = state;
}

void PacketCodec::setCompressionThreshold(int threshold) {
  compressionCodec->setThreshold(threshold);
}
}