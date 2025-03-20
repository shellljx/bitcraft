//
// Created by shell on 2025/3/19.
//

#ifndef BITCRAFT_SRC_RENDERING_GRAPHIC_H_
#define BITCRAFT_SRC_RENDERING_GRAPHIC_H_

#include "gpu/Canvas.h"

namespace bitcraft {
class Graphic {
 public:
  virtual ~Graphic() = default;

  virtual void draw(tgfx::Canvas *canvas) const = 0;
};
}
#endif //BITCRAFT_SRC_RENDERING_GRAPHIC_H_
