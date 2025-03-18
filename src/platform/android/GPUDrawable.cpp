//
// Created by shell on 2025/3/18.
//

#include "GPUDrawable.h"
#include "base/utils/Log.h"

namespace bitcraft {
std::shared_ptr<GPUDrawable> GPUDrawable::FromWindow(ANativeWindow *nativeWindow, EGLContext sharedContext) {
  if (nativeWindow == nullptr) {
    LOGE("GPUDrawable.FromWindow() The nativeWindow is invalid.");
    return nullptr;
  }
  return std::shared_ptr<GPUDrawable>(new GPUDrawable(nativeWindow, sharedContext));
}

GPUDrawable::GPUDrawable(ANativeWindow *nativeWindow, EGLContext eglContext)
    : nativeWindow(nativeWindow), sharedContext(eglContext) {
  updateSize();
}

GPUDrawable::~GPUDrawable() noexcept {
  ANativeWindow_release(nativeWindow);
}

void GPUDrawable::updateSize() {
  if (nativeWindow != nullptr) {
    width_ = ANativeWindow_getWidth(nativeWindow);
    height_ = ANativeWindow_getHeight(nativeWindow);
  }
}

std::shared_ptr<tgfx::Device> GPUDrawable::getDevice() {
  if (width_ <= 0 || height_ <= 0) {
    return nullptr;
  }
  if (window == nullptr) {
    window = tgfx::EGLWindow::MakeFrom(nativeWindow, sharedContext);
  }
  return window ? window->getDevice() : nullptr;
}

std::shared_ptr<tgfx::Surface> GPUDrawable::createSurface(tgfx::Context *context) {
  return window ? window->createSurface(context) : nullptr;
}

void GPUDrawable::present(tgfx::Context *context) {
  if (window == nullptr) {
    return;
  }
  return window->present(context, currentTimeStamp);
}

void GPUDrawable::setTimeStamp(int64_t timeStamp) {
  currentTimeStamp = timeStamp;
}
}