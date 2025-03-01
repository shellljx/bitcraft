//
// Created by 李金祥 on 2022/6/4.
//

#pragma once
#include <glm/glm.hpp>
#include "glm/vec4.hpp"
#include "base/protocol/ingame/clientbound/chunk/ServerChunkDataPacket.h"
#include "Face.h"

namespace bitcraft{
class McRenderer {
 public:
  explicit McRenderer();
  ~McRenderer();

  void setData(const ServerChunkDataPacket* packet, int x, int z);

 private:

 private:
  std::vector<Face> faces_;
};
}
