//
// Created by shell on 2025/3/18.
//

#ifndef BITCRAFT_SRC_PLATFORM_ANDROID_JNIENVIRONMENT_H_
#define BITCRAFT_SRC_PLATFORM_ANDROID_JNIENVIRONMENT_H_

#include <jni.h>
#include "Local.h"

class JNIEnvironment {
public:
    static JNIEnv *Current();
};

#endif //BITCRAFT_SRC_PLATFORM_ANDROID_JNIENVIRONMENT_H_
