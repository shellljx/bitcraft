//
// Created by 李金祥 on 2022/5/28.
//

#pragma once

#include "../io/EncodeStream.h"
#include "../io/DecodeStream.h"

namespace bitcraft {

class PacketCodec {
 public:
  DecodeStream decode(const DecodeStream *in);
};
}