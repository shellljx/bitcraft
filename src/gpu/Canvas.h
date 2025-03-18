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

#pragma once

#include "core/BlendMode.h"
#include "gpu/Texture.h"

namespace tgfx {
class Surface;

class SurfaceOptions;

/**
 * Canvas provides an interface for drawing, and how the drawing is clipped and transformed. Canvas
 * contains a stack of opacity, blend mode, matrix and clip values. Each Canvas draw call transforms
 * the geometry of the object by the concatenation of all matrix values in the stack. The
 * transformed geometry is clipped by the intersection of all of clip values in the stack.
 */
class Canvas {
 public:
  explicit Canvas(Surface* surface);

  virtual ~Canvas() = default;

  /**
   * Retrieves the context associated with this Surface.
   */
  Context* getContext() const;

  /**
   * Returns the Surface this canvas draws into.
   */
  Surface* getSurface() const;

  /**
   * Returns SurfaceOptions associated with this canvas.
   */
  const SurfaceOptions* surfaceOptions() const;
  /**
   * Sets Matrix to the identity matrix. Any prior matrix state is overwritten.
   */
  void resetMatrix();

  /**
   * Returns the current global alpha.
   */
  float getAlpha() const;

  /**
   * Replaces the global alpha with specified newAlpha.
   */
  void setAlpha(float newAlpha);

  /**
   * Returns the current global blend mode.
   */
  BlendMode getBlendMode() const;

  /**
   * Replaces the global blend mode with specified new blend mode.
   */
  void setBlendMode(BlendMode blendMode);

  /**
   * Replacing all pixels with transparent color.
   */
  virtual void clear() = 0;

  /**
   *  Draws a Texture, with its top-left corner at (0, 0), using current alpha, blend mode, clip and
   *  Matrix.
   */
  void drawTexture(const Texture* texture);

  /**
   * Triggers the immediate execution of all pending draw operations.
   */
  virtual void flush() {
  }

 protected:
  Surface* surface = nullptr;
  virtual void onSave() = 0;
  virtual void onRestore() = 0;
};
}  // namespace tgfx
