//
// Created by shell on 2025/3/9.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CLIENTBOUNDPACKETS_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CLIENTBOUNDPACKETS_H_
#include "Packet.h"
namespace bitcraft {
//status
class StatusPongPacket : public Packet {
 public:
  StatusPongPacket();
  ~StatusPongPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  long getPayload() {
    return pingTime;
  }

 private:
  long pingTime = 0;
};

class StatusResponsePacket : public Packet {
 public:
  StatusResponsePacket();
  ~StatusResponsePacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  std::string getInfo() const {
    return info;
  }

 private:
  std::string info;
};
//login
class LoginDisconnectPacket : public Packet {
 public:
  LoginDisconnectPacket();
  ~LoginDisconnectPacket();

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
 private:
  std::string reason;
};

class LoginSuccessPacket : public Packet {
 public:
  LoginSuccessPacket();
  ~LoginSuccessPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  std::string getUUID() const {
    return uuid;
  }

  std::string getUserName() const {
    return userName;
  }
 private:
  std::string uuid = "";
  std::string userName = "";
};

class SetCompressionPacket : public Packet {
 public:
  SetCompressionPacket();
  ~SetCompressionPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  int getCompressionThreshold() const {
    return threshold;
  }
 private:
  int threshold;
};

class LoginAcknowledgedPacket : public Packet {
 public:
  LoginAcknowledgedPacket();
  ~LoginAcknowledgedPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
};
//in game
class ServerKeepAlivePacket : public Packet {
 public:
  ServerKeepAlivePacket();
  ~ServerKeepAlivePacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  long getKeepAliveId() const {
    return keepAliveId_;
  }
 private:
  long long keepAliveId_;
};

class TagCompound;
class BlockEntityInfo;
class LightUpdateData;

class ServerChunkDataPacket : public Packet {
 public:
  ServerChunkDataPacket();
  ~ServerChunkDataPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  DecodeStream getChunkData() const {
    return DecodeStream(chunkData_->data(), chunkData_->length());
  }

  int getX() const {
    return x_;
  }

  int getZ() const {
    return z_;
  }

 private:
  int x_;
  int z_;
  std::shared_ptr<TagCompound> heightMaps_ = nullptr;
  std::unique_ptr<ByteData> chunkData_ = nullptr;
  std::vector<std::unique_ptr<BlockEntityInfo>> blockEntities_;
  std::unique_ptr<LightUpdateData> lightUpdateData_;
};
}
#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CLIENTBOUNDPACKETS_H_
