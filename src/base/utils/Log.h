//
// Created by shell on 2025/3/11.
//

#ifndef BITCRAFT_LINUX_SRC_BASE_UTILS_LOG_H_
#define BITCRAFT_LINUX_SRC_BASE_UTILS_LOG_H_
#include "platform/Print.h"

namespace bitcraft {
#define ABORT(msg)                                                                  \
  do {                                                                              \
    bitcraft::PrintError("%s:%d: fatal error: \"%s\"\n", __FILE__, __LINE__, #msg); \
    ::abort();                                                                      \
  } while (false)

#define LOGI(...) bitcraft::PrintLog(__VA_ARGS__)

#define LOGE(...) bitcraft::PrintError(__VA_ARGS__)

#define ASSERT(assertion) \
  if (!(assertion)) {     \
    ABORT(#assertion);    \
  }

}
#endif //BITCRAFT_LINUX_SRC_BASE_UTILS_LOG_H_
