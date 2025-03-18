//
// Created by shell on 2025/3/18.
//

#include "JNIEnvironment.h"
#include <pthread.h>
#include "base/utils/Log.h"

static JavaVM *globalJavaVM = nullptr;
static pthread_key_t threadKey = 0;

static void JNI_Thread_Destroy(void *value) {
    auto *jniEnv = (JNIEnv *) value;
    if (jniEnv != nullptr && globalJavaVM != nullptr) {
        globalJavaVM->DetachCurrentThread();
        pthread_setspecific(threadKey, nullptr);
    }
}

extern "C" jint JNI_OnLoad(JavaVM *vm, void *) {
    globalJavaVM = vm;
    JNIEnv *env = nullptr;
    if ((vm)->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return JNI_ERR;
    }
    pthread_key_create(&threadKey, JNI_Thread_Destroy);
    return JNI_VERSION_1_4;
}

extern "C" void JNI_OnUnload(JavaVM *, void *) {
    pthread_key_delete(threadKey);
}

JNIEnv *JNIEnvironment::Current() {
    if (globalJavaVM == nullptr) {
        return nullptr;
    }
    JNIEnv *jniEnv = nullptr;
    auto result = globalJavaVM->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_4);
    if (result == JNI_EDETACHED || jniEnv == nullptr) {
        JavaVMAttachArgs args = {JNI_VERSION_1_4, "BITCRAFT_JNIEnvironment", nullptr};
        if (globalJavaVM->AttachCurrentThread(&jniEnv, &args) != JNI_OK) {
            return jniEnv;
        }
        pthread_setspecific(threadKey, (void *) jniEnv);
        return jniEnv;
    } else if (result == JNI_OK) {
        return jniEnv;
    }
    return jniEnv;
}