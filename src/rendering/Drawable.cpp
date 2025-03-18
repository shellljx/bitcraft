//
// Created by shell on 2025/3/18.
//

#include "Drawable.h"

namespace bitcraft {
tgfx::Context *Drawable::lockContext() {
  if (currentDevice == nullptr) {
    return nullptr;
  }
  return currentDevice->lockContext();
}

void Drawable::unlockContext() {
  if (currentDevice == nullptr) {
    return;
  }
  currentDevice->unlock();
}

bool Drawable::prepareDevice() {
  if (currentDevice == nullptr) {
    currentDevice = getDevice();
  }
  return currentDevice != nullptr;
}

bool Drawable::freeDevice() {
  currentDevice = nullptr;
}
}