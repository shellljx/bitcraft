//
// Created by 李金祥 on 2022/6/17.
//

#pragma once
#include <array>
#include <vector>
#include "file.h"
#include "model/FaceInfo.h"

namespace bitcraft {
class Face {
 public:
  ~Face();

  static const std::vector<float> botoom_face;
  static Face Create(Point3D location, Point3DF from, Point3DF to, const FaceInfo *info);
 private:
  explicit Face(const float *matrix, const FaceInfo *info);
 private:
  //model matrix 16 floats
  std::array<float, 16> modelMatrix_;
  //(u1,v1,u2,v2)
  std::array<float, 4> textureCoords_;
};
}