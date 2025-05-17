#include <iostream>
#include "base/protocol/BitcraftClient.h"
#include "minecraft/CraftAssets.h"
#include <GLFW/glfw3.h>
#include "rendering/GLFWDrawable.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void glfw_error_callback(int error, const char *description) {
  std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

int startFlushLoop(const std::shared_ptr<bitcraft::BitcraftClient> &client) {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  //create glfw window
  GLFWwindow *window = glfwCreateWindow(800, 600, "BitCraft", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  auto surface = bitcraft::CraftSurface::MakeFrom(GLFWDrawable::FromWindow(window));
  client->setSurface(surface);

  // start flush loop
  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
    client->flush();
  }
  return 0;
}

int main() {
  auto client = bitcraft::BitcraftClient::Make(769);
  client->connect("127.0.0.1", 25565);

  std::string path = "/Users/lijinxiang/AndroidProjects/private/bitcraft/assets/1.21.4";
  auto assets = bitcraft::CraftAssets::Load(path);

  int ret = startFlushLoop(client);
  return ret;
}
