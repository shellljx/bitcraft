//
// Created by 李金祥 on 2022/6/4.
//

#pragma once
#include <glm/glm.hpp>
#include "glm/vec4.hpp"
#include "base/protocol/ClientBoundPackets.h"
#include "Face.h"
#include "Graphic.h"

namespace bitcraft {

class McRenderer : public Graphic {
 public:
  explicit McRenderer();
  ~McRenderer() override;

  void setData(const ServerChunkDataPacket *packet, int x, int z);

  void draw(tgfx::Canvas *canvas) const override;
 private:

 private:
  std::vector<Face> faces_;
};
}
