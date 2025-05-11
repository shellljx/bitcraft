//
// Created by shell on 2025/3/31.
//

#ifndef BITCRAFT_LINUX_SRC_MINECRAFT_CRAFTASSETS_H_
#define BITCRAFT_LINUX_SRC_MINECRAFT_CRAFTASSETS_H_
#include <string>

namespace bitcraft {
class CraftAssets {
 public:
  static std::shared_ptr<CraftAssets> Load(const std::string &path);
};
}

#endif //BITCRAFT_LINUX_SRC_MINECRAFT_CRAFTASSETS_H_
