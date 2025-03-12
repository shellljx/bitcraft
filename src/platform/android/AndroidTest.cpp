//
// Created by shell on 2025/2/14.
//

#include "base/utils/Log.h"
#include "AndroidTest.h"
#include <jni.h>

extern "C"
JNIEXPORT jint JNICALL
Java_com_gmail_shellljx_bitcraft_AndroidTest_getText(JNIEnv *env, jobject thiz) {
  LOGE("test log %d", 1234);
  return 12344;
}