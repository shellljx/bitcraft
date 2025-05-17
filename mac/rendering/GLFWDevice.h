//
// Created by shell on 2025/5/17.
//

#ifndef BITCRAFT_MAC__GLFWDEVICE_H_
#define BITCRAFT_MAC__GLFWDEVICE_H_

#include "gpu/opengl/GLDevice.h"
#include <GLFW/glfw3.h>

class GLFWDevice : public tgfx::GLDevice {
 public:
  static std::shared_ptr<GLFWDevice> MakeFrom(GLFWwindow *context);

  ~GLFWDevice() override;

  bool sharableWith(void *nativeHandle) const override;

  [[nodiscard]] GLFWwindow *glContext() const {
    return context;
  }

 protected:
  bool onMakeCurrent() override;
  void onClearCurrent() override;

 private:
  GLFWwindow *context = nullptr;

  static std::shared_ptr<GLFWDevice> Wrap(GLFWwindow *context);
  explicit GLFWDevice(GLFWwindow *context);
  void swapBuffers(int64_t timestamp = INT64_MIN);

  friend class GLDevice;
  friend class GLFWProxyWindow;
};

#endif //BITCRAFT_MAC__GLFWDEVICE_H_
