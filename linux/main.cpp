#include <iostream>
#include "base/protocol/BitcraftClient.h"
#include "base/utils/Task.h"

int main() {
  auto client = bitcraft::BitcraftClient::Make(769);
  client->connect("127.0.0.1", 25565);
  std::this_thread::sleep_for(std::chrono::minutes(10));

  return 0;
}
