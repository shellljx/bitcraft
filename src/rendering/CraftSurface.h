//
// Created by shell on 2025/3/18.
//

#ifndef BITCRAFT_CRAFTSURFACE_H
#define BITCRAFT_CRAFTSURFACE_H

#include "gpu/Surface.h"
#include "rendering/Graphic.h"

namespace bitcraft {

class Drawable;

class BitcraftClient;

class CraftSurface {
 public:
  static std::shared_ptr<CraftSurface> MakeFrom(std::shared_ptr<Drawable> drawable);

  int width();

  int height();

  void updateSize();

  bool clearAll();

  void freeCache();

 private:
  std::shared_ptr<std::mutex> rootLocker = nullptr;
  std::shared_ptr<Drawable> drawable = nullptr;
  std::shared_ptr<tgfx::Surface> surface = nullptr;

  explicit CraftSurface(std::shared_ptr<Drawable> drawable);

  bool draw(std::shared_ptr<Graphic> graphic);

  tgfx::Context *lockContext();

  void unlockContext();

  friend class BitcraftClient;
};
}

#endif //BITCRAFT_CRAFTSURFACE_H
