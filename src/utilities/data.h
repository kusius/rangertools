#pragma once
#include "imgui/imgui.h"

struct Vec4 {
  float x, y, z, w;
  // To / From ImVec4
  operator ImVec4() const { return ImVec4(x, y, z, w); }
  Vec4(const ImVec4 imvec4) {
    x = imvec4.x;
    y = imvec4.y;
    z = imvec4.z;
    w = imvec4.w;
  }

  Vec4() { x = y = z = w = 0.0f; }
  Vec4(float _x, float _y, float _z, float _w) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
  }
};