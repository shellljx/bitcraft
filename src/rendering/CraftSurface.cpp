//
// Created by shell on 2025/3/18.
//

#include "CraftSurface.h"
#include "rendering/Drawable.h"
#include "base/utils/LockGuard.h"

namespace bitcraft {
std::shared_ptr<CraftSurface> CraftSurface::MakeFrom(std::shared_ptr<Drawable> drawable) {
  if (drawable == nullptr) {
    return nullptr;
  }
  return std::shared_ptr<CraftSurface>(new CraftSurface(std::move(drawable)));
}

CraftSurface::CraftSurface(std::shared_ptr<Drawable> drawable)
    : drawable(std::move(drawable)) {
  rootLocker = std::shared_ptr<std::mutex>(new std::mutex);
}

bool CraftSurface::draw(std::shared_ptr<Graphic> graphic) {
  if (!drawable->prepareDevice()) {
    return false;
  }
  auto context = lockContext();
  if (!context) {
    return false;
  }
  if (surface == nullptr) {
    surface = drawable->createSurface(context);
  }
  if (surface == nullptr) {
    unlockContext();
    return false;
  }
  auto canvas = surface->getCanvas();
  graphic->draw(canvas);
  surface->flush();
  //drawable->setTimeStamp()
  drawable->present(context);
  unlockContext();
  return true;
}

int CraftSurface::width() {
  LockGuard autoLock(rootLocker);
  return drawable->width();
}

int CraftSurface::height() {
  LockGuard autoLock(rootLocker);
  return drawable->height();
}

void CraftSurface::updateSize() {
  LockGuard autoLock(rootLocker);
  surface = nullptr;
  drawable->freeDevice();
  drawable->updateSize();
}

void CraftSurface::freeCache() {
  LockGuard autoLock(rootLocker);
  surface = nullptr;
  auto context = drawable->lockContext();
  if (context) {
    context->purgeResourcesNotUsedIn(0);
    drawable->unlockContext();
  }
  drawable->freeDevice();
}

bool CraftSurface::clearAll() {
  LockGuard autoLock(rootLocker);
  if (!drawable->prepareDevice()) {
    return false;
  }
  auto context = lockContext();
  if (!context) {
    return false;
  }
  if (surface == nullptr) {
    surface = drawable->createSurface(context);
  }
  if (surface == nullptr) {
    unlockContext();
    return false;
  }
  auto canvas = surface->getCanvas();
  canvas->clear();
  canvas->flush();
  drawable->setTimeStamp(0);
  drawable->present(context);
  unlockContext();
  return true;
}

tgfx::Context *CraftSurface::lockContext() {
  auto context = drawable->lockContext();
  return context;
}

void CraftSurface::unlockContext() {
  drawable->unlockContext();
}
}