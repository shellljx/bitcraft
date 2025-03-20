//
// Created by shell on 2025/3/19.
//

#ifndef BITCRAFT_JBITCRAFTCLIENT_H
#define BITCRAFT_JBITCRAFTCLIENT_H

#include "base/protocol/BitcraftClient.h"

class JBitCraftClient {
public:
    explicit JBitCraftClient(std::shared_ptr<bitcraft::BitcraftClient> client) : craftClient(client) {
    }

    std::shared_ptr<bitcraft::BitcraftClient> get() {
        std::lock_guard<std::mutex> autoLock(locker);
        return craftClient;
    }

    void clear() {
        std::lock_guard<std::mutex> autoLock(locker);
        craftClient = nullptr;
    }

private:
    std::shared_ptr<bitcraft::BitcraftClient> craftClient;
    std::mutex locker;
};


#endif //BITCRAFT_JBITCRAFTCLIENT_H
