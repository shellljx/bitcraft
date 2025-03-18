//
// Created by shell on 2025/3/18.
//

#ifndef BITCRAFT_LOCAL_H
#define BITCRAFT_LOCAL_H

#include <jni.h>

template<typename T>
class Local {
public:
    Local() = default;

    Local(const Local<T> &that) = delete;

    Local<T> &operator=(const Local<T> &that) = delete;

    Local(JNIEnv *env, T ref) : env_(env), ref(ref) {
    }

    ~Local() {
        if (env_ != nullptr) {
            env_->DeleteLocalRef(ref);
        }
    }

    void reset(JNIEnv *env, T reference) {
        if (reference == ref) {
            return;
        }

        if (env_ != nullptr) {
            env_->DeleteLocalRef(ref);
        }
        env_ = env;
        ref = reference;
    }

    bool empty() const {
        return ref == nullptr;
    }

    T get() const {
        return ref;
    }

    JNIEnv *env() const {
        return env_;
    }

private:
    JNIEnv *env_ = nullptr;
    T ref = nullptr;
};

#endif //BITCRAFT_LOCAL_H
