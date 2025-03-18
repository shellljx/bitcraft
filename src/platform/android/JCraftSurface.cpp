//
// Created by shell on 2025/3/18.
//

#include <android/native_window_jni.h>
#include "JCraftSurface.h"
#include "JNIHelper.h"
#include "platform/android/GPUDrawable.h"

namespace bitcraft {
    static jfieldID CraftSurface_nativeSurface;
}

using namespace bitcraft;

extern "C" {

jlong Java_com_gmail_shellljx_bitcraft_CraftSurface_SetupFromSurfaceWithGLContext(JNIEnv *env, jclass,
                                                                                  jobject surface,
                                                                                  jlong shareContext) {
    if (surface == nullptr) {
        return 0;
    }
    auto nativeWindow = ANativeWindow_fromSurface(env, surface);
    auto drawable = GPUDrawable::FromWindow(nativeWindow, reinterpret_cast<EGLContext>(shareContext));
    if (drawable == nullptr) {
        return 0;
    }
    auto craftSurface = CraftSurface::MakeFrom(drawable);
    return reinterpret_cast<jlong>(new JCraftSurface(craftSurface));
}
}