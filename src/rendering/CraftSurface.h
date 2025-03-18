//
// Created by shell on 2025/3/18.
//

#ifndef BITCRAFT_CRAFTSURFACE_H
#define BITCRAFT_CRAFTSURFACE_H

#include "gpu/Surface.h"

namespace bitcraft {

class Drawable;

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

  tgfx::Context *lockContext();

  void unlockContext();
};
}

#endif //BITCRAFT_CRAFTSURFACE_H
