//
// Created by shell on 2025/3/18.
//

#ifndef BITCRAFT_JCRAFTSURFACE_H
#define BITCRAFT_JCRAFTSURFACE_H

#include "rendering/CraftSurface.h"

class JCraftSurface {
public:
    explicit JCraftSurface(std::shared_ptr<bitcraft::CraftSurface> surface)
            : bitcraftSurface(surface) {
    }

    std::shared_ptr<bitcraft::CraftSurface> get() {
        std::lock_guard<std::mutex> autoLock(locker);
        return bitcraftSurface;
    }

    void clear() {
        std::lock_guard<std::mutex> autoLock(locker);
        bitcraftSurface = nullptr;
    }

private:
    std::shared_ptr<bitcraft::CraftSurface> bitcraftSurface;
    std::mutex locker;
};


#endif //BITCRAFT_JCRAFTSURFACE_H
