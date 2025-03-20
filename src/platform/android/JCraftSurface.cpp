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

void setCraftSurface(JNIEnv *env, jobject thiz, JCraftSurface *surface) {
  auto old = reinterpret_cast<JCraftSurface *>(env->GetLongField(thiz, CraftSurface_nativeSurface));
  if (old != nullptr) {
    delete old;
  }
  env->SetLongField(thiz, CraftSurface_nativeSurface, (jlong) surface);
}

std::shared_ptr<CraftSurface> getCraftSurface(JNIEnv *env, jobject thiz) {
  auto craftSurface =
      reinterpret_cast<JCraftSurface *>(env->GetLongField(thiz, CraftSurface_nativeSurface));
  if (craftSurface == nullptr) {
    return nullptr;
  }
  return craftSurface->get();
}

extern "C" {

void Java_com_gmail_shellljx_bitcraft_CraftSurface_nativeInit(JNIEnv *env, jclass clazz) {
  CraftSurface_nativeSurface = env->GetFieldID(clazz, "nativeSurface", "J");
}

void Java_com_gmail_shellljx_bitcraft_CraftSurface_nativeRelease(JNIEnv *env, jobject thiz) {
  auto jSurface = reinterpret_cast<JCraftSurface *>(env->GetLongField(thiz, CraftSurface_nativeSurface));
  if (jSurface != nullptr) {
    jSurface->clear();
  }
}

void Java_com_gmail_shellljx_bitcraft_CraftSurface_nativeFinalize(JNIEnv *env, jobject thiz) {
  setCraftSurface(env, thiz, nullptr);
}

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

void Java_com_gmail_shellljx_bitcraft_CraftSurface_updateSize(JNIEnv *env, jobject thiz) {
  auto surface = getCraftSurface(env, thiz);
  if (surface == nullptr) {
    return;
  }
  surface->updateSize();
}

jboolean Java_com_gmail_shellljx_bitcraft_CraftSurface_clearAll(JNIEnv *env, jobject thiz) {
  auto surface = getCraftSurface(env, thiz);
  if (surface == nullptr) {
    return static_cast<jboolean>(false);
  }
  auto changed = static_cast<jboolean>(surface->clearAll());
  return changed;
}

void Java_com_gmail_shellljx_bitcraft_CraftSurface_freeCache(JNIEnv *env, jobject thiz) {
  auto surface = getCraftSurface(env, thiz);
  if (surface == nullptr) {
    return;
  }
  surface->freeCache();
}
}