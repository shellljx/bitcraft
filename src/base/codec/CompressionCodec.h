//
// Created by 李金祥 on 2022/5/28.
//

#pragma once
#include "base/io/EncodeStream.h"
#include "base/io/DecodeStream.h"

namespace bitcraft{
class CompressionCodec {
 public:
  std::unique_ptr<ByteData> decode(DecodeStream& in);

  void setEnable(bool enable){
    enable_ = enable;
  }

 private:
  std::unique_ptr<ByteData> deCompression(DecodeStream & in, int uLength);
 private:
  bool enable_ = false;
};
}
