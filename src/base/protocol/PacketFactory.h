//
// Created by 李金祥 on 2022/5/29.
//

#pragma once
#include "Packet.h"

namespace bitcraft {
enum class ProtocolStatus : int;
std::shared_ptr<Packet> createClientBoundPacket(int id, ProtocolStatus status);
}
