//
// Created by shell on 2025/5/17.
//

#ifndef BITCRAFT_MAC__GLFWPROXYWINDOW_H_
#define BITCRAFT_MAC__GLFWPROXYWINDOW_H_

#include "GLFWDevice.h"
#include "gpu/Window.h"

class GLFWProxyWindow : public tgfx::Window {
 public:
  static std::shared_ptr<GLFWProxyWindow> Current();

  static std::shared_ptr<GLFWProxyWindow> MakeFrom(GLFWwindow *window);

 protected:
  std::shared_ptr<tgfx::Surface> onCreateSurface(tgfx::Context *context) override;
  void onPresent(tgfx::Context *context, int64_t presentationTime) override;

 private:
  explicit GLFWProxyWindow(std::shared_ptr<tgfx::Device> device);
};

#endif //BITCRAFT_MAC__GLFWPROXYWINDOW_H_
