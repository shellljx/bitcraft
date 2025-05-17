//
// Created by shell on 2025/5/17.
//

#ifndef BITCRAFT_MAC__GLFWDRAWABLE_H_
#define BITCRAFT_MAC__GLFWDRAWABLE_H_

#include "rendering/Drawable.h"
#include "GLFWProxyWindow.h"

class GLFWDrawable : public bitcraft::Drawable {
 public:
  static std::shared_ptr<GLFWDrawable> FromWindow(GLFWwindow *window);
  ~GLFWDrawable() override;

  [[nodiscard]] int width() const override {
    return width_;
  }

  [[nodiscard]] int height() const override {
    return height_;
  }

  void updateSize() override;

  std::shared_ptr<tgfx::Surface> createSurface(tgfx::Context *context) override;

  void present(tgfx::Context *context) override;

  void setTimeStamp(int64_t) override;

 protected:
  std::shared_ptr<tgfx::Device> getDevice() override;

 private:
  int width_ = 0;
  int height_ = 0;
  GLFWwindow *nativeWindow = nullptr;
  std::shared_ptr<GLFWProxyWindow> window = nullptr;

  explicit GLFWDrawable(GLFWwindow *nativeWindow);
};

#endif //BITCRAFT_MAC__GLFWDRAWABLE_H_
