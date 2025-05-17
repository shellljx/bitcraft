//
// Created by shell on 2025/5/17.
//

#include "GLFWDrawable.h"

std::shared_ptr<GLFWDrawable> GLFWDrawable::FromWindow(GLFWwindow *window) {
  if (window == nullptr) {
    return nullptr;
  }

  return std::shared_ptr<GLFWDrawable>(new GLFWDrawable(window));
}

GLFWDrawable::GLFWDrawable(GLFWwindow *nativeWindow) : nativeWindow(nativeWindow) {
  updateSize();
}

GLFWDrawable::~GLFWDrawable() {
  glfwDestroyWindow(nativeWindow);
  glfwTerminate();
}

void GLFWDrawable::updateSize() {
  if (nativeWindow != nullptr) {
    glfwGetWindowSize(nativeWindow, &width_, &height_);
  }
}

std::shared_ptr<tgfx::Device> GLFWDrawable::getDevice() {
  if (width_ <= 0 || height_ <= 0) {
    return nullptr;
  }
  if (window == nullptr) {
    window = GLFWProxyWindow::MakeFrom(nativeWindow);
  }
  return window ? window->getDevice() : nullptr;
}

std::shared_ptr<tgfx::Surface> GLFWDrawable::createSurface(tgfx::Context *context) {
  return window ? window->createSurface(context) : nullptr;
}

void GLFWDrawable::present(tgfx::Context *context) {
  if (window == nullptr) {
    return;
  }
  return window->present(context, 0);
}

void GLFWDrawable::setTimeStamp(int64_t) {
}