//
// Created by shell on 2025/3/9.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CLIENTBOUNDPACKETS_H_
#define BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CLIENTBOUNDPACKETS_H_
#include <vector>
#include "Packet.h"
#include "base/model/nbt/Nbt.h"
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

class ChunkDataAndUpdateLightPacket : public Packet {
 public:
  ChunkDataAndUpdateLightPacket();
  ~ChunkDataAndUpdateLightPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  [[nodiscard]] DecodeStream chunkData() const;

 private:
  int x = 0;
  int z = 0;
  std::shared_ptr<Tag> heightMaps = nullptr;
  std::unique_ptr<ByteData> chunkData_ = nullptr;
  std::vector<std::unique_ptr<BlockEntityInfo>> blockEntities;
  std::unique_ptr<LightUpdateData> lightUpdateData;
};

//configuration
class CustomPayloadPacket : public Packet {
 public:
  CustomPayloadPacket();
  ~CustomPayloadPacket() override;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  std::string identifier;
  std::unique_ptr<ByteData> datas;
};

class UpdateEnabledFeaturesPacket : public Packet {
 public:
  UpdateEnabledFeaturesPacket();
  ~UpdateEnabledFeaturesPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  std::vector<std::string> featureFlags;
};

class KnownPack;
class SelectKnownPacksPacket : public Packet {
 public:
  SelectKnownPacksPacket();
  ~SelectKnownPacksPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

  [[nodiscard]] std::vector<std::shared_ptr<KnownPack>> getKnownPacks() const {
    return knownPacks;
  }
 private:
  std::vector<std::shared_ptr<KnownPack>> knownPacks;
};

class RegistryEntry;
class ClientboundRegistryDataPacket : public Packet {
 public:
  ClientboundRegistryDataPacket();
  ~ClientboundRegistryDataPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  std::string identifier;
  std::vector<std::shared_ptr<RegistryEntry>> entries;
};

class ClientboundUpdateTagsPacket : public Packet {
 public:
  ClientboundUpdateTagsPacket();
  ~ClientboundUpdateTagsPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
 private:
  std::map<std::string, std::map<std::string, std::vector<int>>> tags;
};

class FinishConfigurationPacket : public Packet {
 public:
  FinishConfigurationPacket();
  ~FinishConfigurationPacket() override = default;
  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
};

//ingame

class ClientboundSpawnEntityPacket : public Packet {
 public:
  ClientboundSpawnEntityPacket();
  ~ClientboundSpawnEntityPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  int entityId{};
  std::string uuid;
  int type{};
  double x{};
  double y{};
  double z{};
  int pitch{};
  int yaw{};
  int headYaw{};
  int data{};
  short velocityX{};
  short velocityY{};
  short velocityZ{};
};

class PlayerSpawnInfo;

class ClientboundLoginPacket : public Packet {
 public:
  ClientboundLoginPacket();
  ~ClientboundLoginPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;
 private:
  int32_t entityId{};
  bool hardcore{};
  std::vector<std::string> dimensions;
  int maxPlayers{};
  int viewDistance{};
  int simulationDistance{};
  bool reducedDebugInfo{};
  bool enableRespawnScreen{};
  bool doLimitedCrafting{};
  std::shared_ptr<PlayerSpawnInfo> playerSpawnInfo = nullptr;
  bool enforceSecureChat{};
};

class ClientboundChangeDifficultyPacket : public Packet {
 public:
  ClientboundChangeDifficultyPacket();
  ~ClientboundChangeDifficultyPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  int difficulty{};
  bool difficultyLock{};
};

class ClientboundSetPlayerPositionPacket : public Packet {
 public:
  ClientboundSetPlayerPositionPacket();
  ~ClientboundSetPlayerPositionPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  double x;
  double feetY;
  double z;
  int flags;
};

class ClientboundSynchronizePlayerPositionPacket : public Packet {
 public:
  ClientboundSynchronizePlayerPositionPacket() : Packet(0x42) {}
  ~ClientboundSynchronizePlayerPositionPacket() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  int teleportId{};
  double x{};
  double y{};
  double z{};
  double velocityX{};
  double velocityY{};
  double velocityZ{};
  float yaw{};
  float pitch{};
  int flags{};

  friend class BitcraftClient;
};
}
#endif //BITCRAFT_LINUX_SRC_BASE_PROTOCOL_CLIENTBOUNDPACKETS_H_
