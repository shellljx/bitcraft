//
// Created by 李金祥 on 2022/6/11.
//
#pragma once
#include "base/io/DecodeStream.h"
#include "base/io/EncodeStream.h"

namespace bitcraft {
class ReadWriteable {
 public:
  virtual ~ReadWriteable() = default;

  virtual void read(DecodeStream *stream) = 0;
  virtual void write(EncodeStream *stream) = 0;
};
}