//
// Created by shell on 2025/3/18.
//

#ifndef BITCRAFT_SRC_RENDERING_DRAWABLE_H_
#define BITCRAFT_SRC_RENDERING_DRAWABLE_H_
#include "gpu/Surface.h"

namespace bitcraft {
class Drawable {
 public:
  virtual ~Drawable() = default;

  virtual std::shared_ptr<tgfx::Surface> createSurface(tgfx::Context *context) = 0;

  virtual int width() const = 0;

  virtual int height() const = 0;

  virtual void updateSize() = 0;

  virtual void present(tgfx::Context* context) = 0;

  virtual void setTimeStamp(int64_t) {
  }

  virtual tgfx::Context *lockContext();

  virtual void unlockContext();

  virtual bool prepareDevice();

  virtual bool freeDevice();

 protected:
  virtual std::shared_ptr<tgfx::Device> getDevice() = 0;

 private:
  std::shared_ptr<tgfx::Device> currentDevice;
};
}

#endif //BITCRAFT_SRC_RENDERING_DRAWABLE_H_
