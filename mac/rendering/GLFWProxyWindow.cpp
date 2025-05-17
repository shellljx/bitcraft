//
// Created by shell on 2025/5/17.
//

#include "GLFWProxyWindow.h"
#include "gpu/opengl/GLRenderTarget.h"

std::shared_ptr<GLFWProxyWindow> GLFWProxyWindow::Current() {
  auto device = GLFWDevice::Current();
  if (device == nullptr) {
    return nullptr;
  }
  return std::shared_ptr<GLFWProxyWindow>(new GLFWProxyWindow(device));
}

std::shared_ptr<GLFWProxyWindow> GLFWProxyWindow::MakeFrom(GLFWwindow *window) {
  auto device = GLFWDevice::MakeFrom(window);
  if (device == nullptr) {
    return nullptr;
  }
  return std::shared_ptr<GLFWProxyWindow>(new GLFWProxyWindow(device));
}

GLFWProxyWindow::GLFWProxyWindow(std::shared_ptr<tgfx::Device> device) : Window(std::move(device)) {
}

std::shared_ptr<tgfx::Surface> GLFWProxyWindow::onCreateSurface(tgfx::Context *context) {
  int width = 0;
  int height = 0;
  auto glfwDevice = static_cast<GLFWDevice *>(device.get());
  glfwGetWindowSize(glfwDevice->glContext(), &width, &height);
  if (width <= 0 || height <= 0) {
    return nullptr;
  }
  tgfx::GLFrameBuffer frameBuffer = {};
  frameBuffer.id = 0;
  frameBuffer.format = tgfx::PixelFormat::RGBA_8888;
  auto renderTarget =
      tgfx::GLRenderTarget::MakeFrom(context, frameBuffer, width, height, tgfx::ImageOrigin::BottomLeft);
  return tgfx::Surface::MakeFrom(renderTarget);
}

void GLFWProxyWindow::onPresent(tgfx::Context *context, int64_t presentationTime) {
  std::static_pointer_cast<GLFWDevice>(device)->swapBuffers(presentationTime);
}