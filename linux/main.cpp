#include <iostream>
#include "base/protocol/MinecraftProtocol.h"
int main() {
  auto client = bitcraft::MinecraftProtocol::Make("127.0.0.1", 25565, "1");
  client->connect();
  std::this_thread::sleep_for(std::chrono::minutes(10));
  return 0;
}
