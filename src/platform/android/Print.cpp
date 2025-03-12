//
// Created by shell on 2025/3/11.
//
#include "platform/Print.h"
#include <android/log.h>

namespace bitcraft {
#define LOG_TAG "bitcraft"

void PrintLog(const char format[], ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, format, args);
  va_end(args);
}

void PrintError(const char format[], ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, format, args);
  va_end(args);
}
}