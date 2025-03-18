//
// Created by shell on 2025/3/18.
//

#ifndef BITCRAFT_SRC_PLATFORM_ANDROID_GPUDRAWABLE_H_
#define BITCRAFT_SRC_PLATFORM_ANDROID_GPUDRAWABLE_H_

#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "rendering/Drawable.h"
#include "gpu/opengl/egl/EGLWindow.h"

namespace bitcraft {
class GPUDrawable : public Drawable {
 public:
  static std::shared_ptr<GPUDrawable> FromWindow(ANativeWindow *nativeWindow, EGLContext sharedContext = EGL_NO_CONTEXT);

  ~GPUDrawable() override;

  int width() const override {
    return width_;
  }

  int height() const override {
    return height_;
  }

  void updateSize() override;

  std::shared_ptr<tgfx::Surface> createSurface(tgfx::Context *context) override;

  void present(tgfx::Context *context) override;

  void setTimeStamp(int64_t timeStamp) override;

 protected:
  std::shared_ptr<tgfx::Device> getDevice() override;

 private:
  int width_ = 0;
  int height_ = 0;
  ANativeWindow *nativeWindow = nullptr;
  EGLContext sharedContext = nullptr;
  int64_t currentTimeStamp = 0;
  std::shared_ptr<tgfx::EGLWindow> window = nullptr;

  explicit GPUDrawable(ANativeWindow *nativeWindow, EGLContext eglContext = EGL_NO_CONTEXT);
};
}

#endif //BITCRAFT_SRC_PLATFORM_ANDROID_GPUDRAWABLE_H_
