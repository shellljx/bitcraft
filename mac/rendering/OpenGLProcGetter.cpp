//
// Created by shell on 2025/5/17.
//

#include "OpenGLProcGetter.h"
#include <dlfcn.h>

OpenGLProcGetter::OpenGLProcGetter() {
  fLibrary = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib",
                    RTLD_LAZY);
}

OpenGLProcGetter::~OpenGLProcGetter() {
  if (fLibrary) {
    dlclose(fLibrary);
  }
}

void *OpenGLProcGetter::getProcAddress(const char *name) const {
  auto handle = fLibrary ? fLibrary : RTLD_DEFAULT;
  return dlsym(handle, name);
}

std::unique_ptr<tgfx::GLProcGetter> tgfx::GLProcGetter::Make() {
  return std::make_unique<OpenGLProcGetter>();
}