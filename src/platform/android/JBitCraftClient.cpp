//
// Created by shell on 2025/3/19.
//

#include "JBitCraftClient.h"
#include "JCraftSurface.h"
#include "JNIHelper.h"

namespace bitcraft {
static jfieldID BitCraftClient_nativeContext;
}

using namespace bitcraft;

std::shared_ptr<BitcraftClient> getCraftClient(JNIEnv *env, jobject thiz) {
  auto jclient =
      reinterpret_cast<JBitCraftClient *>(env->GetLongField(thiz, BitCraftClient_nativeContext));
  if (jclient == nullptr) {
    return nullptr;
  }
  return jclient->get();
}

void setCraftClient(JNIEnv *env, jobject thiz, JBitCraftClient *client) {
  auto old =
      reinterpret_cast<JBitCraftClient *>(env->GetLongField(thiz, BitCraftClient_nativeContext));
  if (old != nullptr) {
    delete old;
  }
  env->SetLongField(thiz, BitCraftClient_nativeContext, (jlong) client);
}

extern "C" {
void Java_com_gmail_shellljx_bitcraft_BitCraftClient_nativeInit(JNIEnv *env, jclass clazz) {
  BitCraftClient_nativeContext = env->GetFieldID(clazz, "nativeContext", "J");
}

void Java_com_gmail_shellljx_bitcraft_BitCraftClient_nativeSetup(JNIEnv *env,
                                                                 jobject thiz,
                                                                 jint version) {
  auto client = BitcraftClient::Make(version);
  setCraftClient(env, thiz, new JBitCraftClient(client));
}

void Java_com_gmail_shellljx_bitcraft_BitCraftClient_nativeSetSurface(JNIEnv *env, jobject thiz,
                                                                      jlong surfaceObject) {
  auto client = getCraftClient(env, thiz);
  if (client == nullptr) {
    return;
  }
  auto surface = reinterpret_cast<JCraftSurface *>(surfaceObject);
  if (surface != nullptr) {
    client->setSurface(surface->get());
  } else {
    client->setSurface(nullptr);
  }
}

jboolean Java_com_gmail_shellljx_bitcraft_BitCraftClient_flushAndFenceSync(JNIEnv *env, jobject thiz) {
  auto client = getCraftClient(env, thiz);
  if (client == nullptr) {
    return 0;
  }
  return static_cast<jboolean>(client->flush());
}

void Java_com_gmail_shellljx_bitcraft_BitCraftClient_nativeRelease(JNIEnv *env, jobject thiz) {

}

void Java_com_gmail_shellljx_bitcraft_BitCraftClient_nativeFinalize(JNIEnv *env, jobject thiz) {

}
}