/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Tencent is pleased to support the open source community by making libpag available.
//
//  Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
//  except in compliance with the License. You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  unless required by applicable law or agreed to in writing, software distributed under the
//  license is distributed on an "as is" basis, without warranties or conditions of any kind,
//  either express or implied. see the license for the specific language governing permissions
//  and limitations under the license.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "gpu/Canvas.h"
#include <atomic>
#include "gpu/Surface.h"

namespace tgfx {
static uint32_t NextClipID() {
  static const uint32_t kFirstUnreservedClipID = 1;
  static std::atomic_uint32_t nextID{kFirstUnreservedClipID};
  uint32_t id;
  do {
    id = nextID++;
  } while (id < kFirstUnreservedClipID);
  return id;
}

Canvas::Canvas(Surface* surface) : surface(surface) {
}

Context* Canvas::getContext() const {
  return surface->getContext();
}

Surface* Canvas::getSurface() const {
  return surface;
}

const SurfaceOptions* Canvas::surfaceOptions() const {
  return surface->options();
}
}  // namespace tgfx
