//
// Created by shell on 2025/5/11.
//

#ifndef BITCRAFT_LINUX_SRC_MINECRAFT_REGISTRY_BLOCKREGISTRY_H_
#define BITCRAFT_LINUX_SRC_MINECRAFT_REGISTRY_BLOCKREGISTRY_H_
#include <string>

namespace bitcraft {

class Block {
 public:
  Block(std::string name, int id) : name(name), id(id) {}
  virtual ~Block() = default;

  const std::string &getName() const {
    return name;
  }

  int getId() const {
    return id;
  }

 private:
  std::string name;
  int id;
};

class BlockRegistry {
  
};
}

#endif //BITCRAFT_LINUX_SRC_MINECRAFT_REGISTRY_BLOCKREGISTRY_H_
