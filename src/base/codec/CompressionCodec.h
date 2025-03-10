//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "base/io/EncodeStream.h"
#include "base/io/DecodeStream.h"

namespace bitcraft {
class CompressionCodec {
 public:
  CompressionCodec();
  std::unique_ptr<ByteData> decode(DecodeStream &in) const;
  std::unique_ptr<ByteData> encode(std::unique_ptr<ByteData> data) const;

  void setThreshold(int threshold) {
    compressionThreshold = threshold;
  }

 private:
  static std::unique_ptr<ByteData> compression(std::unique_ptr<ByteData> data);
  static std::unique_ptr<ByteData> deCompression(DecodeStream &in, int uLength);
 private:
  int compressionThreshold;
};
}
