//
// Created by shell on 2025/3/10.
//
#if !defined(__ANDROID__) && !defined(ANDROID)
#include "Print.h"
#include <cstdarg>
#include <cstdio>

namespace bitcraft {
void PrintLog(const char format[], ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  fprintf(stdout, "\n");
}

void PrintError(const char format[], ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fprintf(stderr, "\n");
}
}
#endif
