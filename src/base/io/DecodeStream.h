//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "ByteData.h"
#include "ByteOrder.h"

namespace bitcraft {

class DecodeStream final {
 public:
  DecodeStream(const uint8_t *data, uint32_t length) : bytes_(data), length_(length) {
  }

  ByteOrder order() const;

  void setOrder(ByteOrder order);

  uint32_t bytesAvailable() const {
    return length_ - position_;
  }

  const uint8_t *data() const {
    return bytes_;
  }

  uint32_t length() const {
    return length_;
  }

  uint32_t position() const {
    return position_;
  }

  void setPosition(uint32_t value);

  void skip(uint32_t bytes);

  bool readBoolean() {
    return readBit8().boolValue;
  }

  uint8_t readUint8() {
    return readBit8().uintValue;
  }

  int8_t readInt8() {
    return readBit8().intValue;
  }

  int16_t readInt16() {
    return readBit16().intValue;
  }

  uint16_t readUint16() {
    return readBit16().uintValue;
  }

  int32_t readInt32() {
    return readBit32().intValue;
  }

  int64_t readInt64() {
    return readBit64().intValue;
  }

  uint64_t readUint64() {
    return readBit64().uintValue;
  }

  float readFloat() {
    return readBit32().floatValue;
  }

  double readDouble() {
    return readBit64().doubleValue;
  }

  int readVarInt();

  std::string readVarString();

  /**
   * Reads a UTF-8 string from the byte stream. The string is assumed to be a sequential list of
   * bytes terminated by the null character byte.
   */
  std::string readUTF8String();

  /**
   * First, two bytes are read and used to construct an unsigned 16-bit interger.
   * This interger value is called the UTF length and specifies the number of additional bytes
   * to be read.
   * @return
   */
  std::string readUtfString();

  /**
   * reads the number of data bytes, specified by the length parameter, from the byte stream.
   * @param length the number of bytes to read
   * @return
   */
  DecodeStream readBytes(uint32_t length);

  /**
   * Reads a ByteData object from the byte stream.
   * @param length the number of bytes to read.
   * @return
   */
  std::unique_ptr<ByteData> readByteData(uint32_t length);

 private:
  Bit8 readBit8();
  Bit16 readBit16();
  Bit32 readBit32();
  Bit64 readBit64();

 private:
  const uint8_t *bytes_ = nullptr;
  ByteOrder order_ = EndianTest();
  uint32_t length_ = 0;
  uint32_t position_ = 0;
};
}
