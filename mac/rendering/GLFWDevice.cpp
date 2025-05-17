//
// Created by shell on 2025/5/17.
//

#include "GLFWDevice.h"

std::shared_ptr<tgfx::GLDevice> tgfx::GLDevice::Current() {
  auto context = glfwGetCurrentContext();
  auto glDevice = GLDevice::Get(reinterpret_cast<void *>(context));
  if (glDevice) {
    return std::static_pointer_cast<GLFWDevice>(glDevice);
  }
  return GLFWDevice::Wrap(context);
}

std::shared_ptr<tgfx::GLDevice> tgfx::GLDevice::Make(void *sharedContext) {
  return nullptr;
}

std::shared_ptr<GLFWDevice> GLFWDevice::MakeFrom(GLFWwindow *context) {
  if (context == nullptr) {
    return nullptr;
  }
  return GLFWDevice::Wrap(context);
}

std::shared_ptr<GLFWDevice> GLFWDevice::Wrap(GLFWwindow *context) {
  if (context == nullptr)return nullptr;
  GLFWwindow *oldContext = glfwGetCurrentContext();
  if (oldContext != context) {
    glfwMakeContextCurrent(context);
  }
  auto device = std::shared_ptr<GLFWDevice>(new GLFWDevice(context));
  device->context = context;
  device->weakThis = device;
  if (oldContext != context) {
    glfwMakeContextCurrent(nullptr);
    if (oldContext) {
      glfwMakeContextCurrent(oldContext);
    }
  }
  return device;
}

GLFWDevice::GLFWDevice(GLFWwindow *context) : GLDevice(reinterpret_cast<void *>(context)) {
}

GLFWDevice::~GLFWDevice() {
  releaseAll();
}

bool GLFWDevice::onMakeCurrent() {
  auto oldContext = glfwGetCurrentContext();
  if (oldContext == context) {
    // 如果外部已经设定好了当前的 Context，以外部设定的为准，不再切换。
    return true;
  }
  glfwMakeContextCurrent(context);
  return true;
}

void GLFWDevice::onClearCurrent() {
  glfwMakeContextCurrent(nullptr);
}

void GLFWDevice::swapBuffers(int64_t timestamp) {
  glfwSwapBuffers(context);
  glfwPollEvents();
}

bool GLFWDevice::sharableWith(void *nativeContext) const {
  return nativeHandle == nativeContext;
}
