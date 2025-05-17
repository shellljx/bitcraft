//
// Created by shell on 2025/5/17.
//

#ifndef BITCRAFT_MAC__OPENGLPROCGETTER_H_
#define BITCRAFT_MAC__OPENGLPROCGETTER_H_

#include "gpu/opengl/GLProcGetter.h"

class OpenGLProcGetter : public tgfx::GLProcGetter {
 public:
  OpenGLProcGetter();
  ~OpenGLProcGetter();
  void *getProcAddress(const char name[]) const override;

 private:
  void *fLibrary;
};

#endif //BITCRAFT_MAC__OPENGLPROCGETTER_H_
