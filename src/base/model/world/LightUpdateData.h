//
// Created by 李金祥 on 2022/6/11.
//
#pragma once
#include <vector>
#include "../../io/ReadWriteable.h"

namespace bitcraft {
class LightUpdateData : public ReadWriteable {
 public:
  LightUpdateData() = default;
  ~LightUpdateData() override = default;

  void read(DecodeStream *stream) override;
  void write(EncodeStream *stream) override;

 private:
  std::vector<unsigned long long int> skyYMask;
  std::vector<unsigned long long int> blockYMask;
  std::vector<unsigned long long int> emptySkyYMask;
  std::vector<unsigned long long int> emptyBlockYMask;

  std::vector<std::unique_ptr<ByteData>> skyUpdates;
  std::vector<std::unique_ptr<ByteData>> blockUpdates;
};
}